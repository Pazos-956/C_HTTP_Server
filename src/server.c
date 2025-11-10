#include "server.h"

int Start_server(){
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
    get_st = getaddrinfo(NULL, PORT, &hints, &servL);
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
    if(listen(server_fd, BACKLOG) != 0){
        perror("listen error");
    }

    printf("Estoy Escuchando en puerto %s\n", PORT);
    int clientSocket;
    char clientMsg[10000] = "";
    char buf[2048] = "HTTP/1.1 200 OK\n"
        "Connection: close\r\n\n"
        "<html><h1>Hello World!<!h1><!html>\n";
    while(1){
        clientSocket = accept(server_fd, NULL, NULL);
        read(clientSocket, clientMsg, 9999);
        printf("%s\n", clientMsg);
        send(clientSocket, &buf, sizeof(buf)-1, 0);
        close(clientSocket);
    }
    printf("Fuera del loop\n");

    return 0;
}

