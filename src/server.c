#include "server.h"

struct Server* Start_server(char* port){
    struct addrinfo hints, *servL;
    int server_fd, get_st;
    int yes = 1;
    memset(&hints, 0,  sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    // Rellena la IP con la del host
    hints.ai_flags = AI_PASSIVE;

    //hints es un addrinfo con información previa para la conexión.
    //servL es un puntero a linked list con los resultados.
    get_st = getaddrinfo(NULL, port, &hints, &servL);
    if(get_st != 0){
        // gai_strerror convierte el error de getaddrifno a string
        fprintf(stderr, "gai error: %s\n", gai_strerror(get_st));
        exit(1);
    }
    server_fd = socket(servL->ai_family, servL->ai_socktype, servL->ai_protocol);
    if(server_fd == -1){
        perror("socket error");
    }
    // Esto hace que el puerto se pueda reutilizar cuando queda bloqueado entre reinicios
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if(bind(server_fd, servL->ai_addr, servL->ai_addrlen) != 0){
        perror("bind error");
    }
    // Cuando ya no se necesita servL se libera
    freeaddrinfo(servL);
    if(listen(server_fd, BACKLOG) != 0){
        perror("listen error");
    }
    printf("\nEstoy Escuchando en puerto %s\n", port);

    struct Server *server = malloc(sizeof(struct Server));
    server->port = port;
    server->socket_fd = server_fd;
    return server;
}


