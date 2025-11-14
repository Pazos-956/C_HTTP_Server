#include "server.h"
#include "routing.h"
#include "render.h"

void routing(int client_fd, char *token);
char *normalize(char *path);

int main(){
    int client_fd, rec_status;
    char client_msg[MAXCLIENTLENGTH], path[1024], response[4096];
    char *render, *token;
    struct Server *server = Start_server("42069");
    struct Route *node;
    struct Route *route = Init_route("/", "index.html");
    memset(response, 0, 4096);

    route = Insert_route(route, "/hola", "hola.html");
    while(1){
        client_fd = accept(server->socket_fd, NULL, NULL);
        rec_status = recv(client_fd, client_msg, MAXCLIENTLENGTH-1, 0);
        if(rec_status == 0){
            close(client_fd);
            printf("El usuario ha cerrado la conexión.\n");
            break;
        }else if(rec_status == -1){
            perror("Recv error");
        }

        token = strtok(client_msg, " ");
        if(!strcmp(token, "GET")){
            token = strtok(NULL, " ");
            node = Search_route(route, normalize(token));
            if(node == NULL){
                render = Render("template/notfound.html");
                strcpy(response, "HTTP/1.1 404 NOT_FOUND\r\n\r\n");
            }else{
                strcpy(path, "template/");
                strcat(path, node->value);
                strcpy(response, "HTTP/1.1 200 OK\r\n\r\n");
                render = Render(path);
            }
        }else{
            strcpy(response, "HTTP/1.1 404 NOT_FOUND\r\n\r\n");
            render = Render("template/notfound.html");
        }
        
        strcat(response, render);
        strcat(response, "\r\n\r\n");
        send(client_fd, response, strlen(response), 0);
        
        memset(response, 0, 4096);
        close(client_fd);
        free(render);
    }
    free(server);
    Free_routes(route);
    return 0;
}

char *normalize(char *path){
    char *dest = malloc(512);
    char *token;
    memset(dest, 0, 512);
    if(strlen(path) >= 512){
        strcpy(dest, "toobig");
        return dest;
    }
    if((token = strtok(path,"/")) == NULL){
        strcpy(dest, "/");
        return dest;
    }
    strcat(dest, "/");
    strcat(dest, token);
    while((token = strtok(NULL, "/")) != NULL){
        strcat(dest, "/");
        strcat(dest, token);
    };
    return dest;
}
