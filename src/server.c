#include "server.h"
#include <string.h>

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
    // Cuando ya no se necesita servL se libera
    freeaddrinfo(servL);
    if(listen(server_fd, BACKLOG) != 0){
        perror("listen error");
    }

    printf("Estoy Escuchando en puerto %s\n", PORT);
    return server_fd;
}

int Accept_connections(int server_fd){
    int client_fd;
    char client_msg[MAXCLIENTLENGTH];
    int rec_status;
    char *token = malloc(4096);
    while(1){
        client_fd = accept(server_fd, NULL, NULL);
        rec_status = recv(client_fd, client_msg, MAXCLIENTLENGTH-1, 0);
        if(rec_status == 0){
            close(client_fd);
            printf("El usuario ha cerrado la conexión.\n");
            break;
        }else if(rec_status == -1){
            perror("Recv error");
        }
        printf("%s", client_msg);
        token = strtok(client_msg, " ");
        if(!strcmp(token, "GET")){
            token = strtok(NULL, " ");
            routing(client_fd, token);
        }else{
            routing(client_fd, "notfound");
        }
        
        close(client_fd);
    }
    free(token);
    printf("Fuera del loop\n");
    return 0;
}

void routing(int client_fd, char *token){
    char *path = malloc(4096);
    char *server_msg = "HTTP/1.1 200 OK\n"
        "Connection: close\r\n\n"
        "<html><h1>Hello World!<!h1><!html>\n";
    char *notfound_msg = "HTTP/1.1 404 NOT FOUND\n"
        "Connection: close\r\n\n"
        "<html><h1>No se ha encontrado la pagina!<!h1><!html>\n";
    char *server_index = "HTTP/1.1 200 OK\n"
        "Connection: close\r\n\n"
        "<html><h1>Esto es el indice!<!h1><!html>\n";
    path = strtok(token, "/");
    if(path != NULL){
        if(!strcmp("hola", path)){
            send(client_fd, server_msg, strlen(server_msg), 0);
        }else{
            send(client_fd, notfound_msg, strlen(notfound_msg), 0);
        }
    }else{
        send(client_fd, server_index, strlen(server_index), 0);
    }
    return;
}

