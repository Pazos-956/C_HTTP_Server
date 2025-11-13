#include "server.h"
#include "routing.h"
#include "render.h"

void routing(int client_fd, char *token);

int main(){
    int client_fd;
    char client_msg[MAXCLIENTLENGTH];
    int rec_status;
    char *token;
    struct Server *server = Start_server("42069");
    struct Route *route = Init_route("/", "index.html");
    struct Route *node;

    while(1){
        client_fd = accept(server->socket_fd, NULL, NULL);
        rec_status = recv(client_fd, client_msg, MAXCLIENTLENGTH-1, 0);
        if(rec_status != 0){
            close(client_fd);
            printf("El usuario ha cerrado la conexión.\n");
            break;
        }else if(rec_status == -1){
            perror("Recv error");
        }
        //printf("%s", client_msg);
        token = strtok(client_msg, " ");
        if(!strcmp(token, "GET")){
            token = strtok(NULL, " ");
            node = Search_route(route, token);
            if(node == NULL){
                Render("notfound.html");
            }else{
                Render(node->value);
            }
        }else{
            Render("notfound.html");
        }
        
        close(client_fd);
    }
    printf("Fuera del loop\n");
    return 0;
    free(server);
    return 0;
}

char *normalize(char *path){
    char *dest = malloc(1024);
    char *token;
    memset(dest, 0, 1024);
    if(strlen(path) >= 1024){
        strcpy(dest, "toobig");
        return dest;
    }
    if((token = strtok(path,"/")) == NULL){
        strcpy(dest, "index");
        return dest;
    }
    strcat(dest, token);
    while((token = strtok(NULL, "/")) != NULL){
        strcat(dest, "/");
        strcat(dest, token);
    };
    return dest;
}

void routing(int client_fd, char *token){
    char *path;
    char *server_msg = "HTTP/1.1 200 OK\n"
        "Connection: close\r\n\n"
        "<html><h1>Hello World!<!h1><!html>\n";
    char *notfound_msg = "HTTP/1.1 404 NOT FOUND\n"
        "Connection: close\r\n\n"
        "<html><h1>No se ha encontrado la pagina!<!h1><!html>\n";
    char *server_index = "HTTP/1.1 200 OK\n"
        "Connection: close\r\n\n"
        "<html><h1>Esto es el indice!<!h1><!html>\n";
    path = normalize(strtok(token, "?"));
    printf("\n%d\n", strcmp("/", path));
    if(!strcmp("hola", path)){
        send(client_fd, server_msg, strlen(server_msg), 0);
    }else if(!strcmp("index", path)){
        send(client_fd, server_index, strlen(server_index), 0);
    }else{
        send(client_fd, notfound_msg, strlen(notfound_msg), 0);
    }
    free(path);
    return;
}
