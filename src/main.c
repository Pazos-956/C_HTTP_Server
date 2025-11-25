#include "server.h"
#include "routing.h"
#include "render.h"

struct request{
    char *version;
    char method;
    char *route;
};

void routing(int client_fd, char *token);
char *normalize(char *path);
void tokenize_request(struct request *tok_req, char *request);
void process_request(struct request request, char *response, char *value);

int main(){
    int client_fd, rec_status;
    char client_msg[MAXCLIENTLENGTH];
    char *response = malloc(4096 * sizeof(char));
    struct Server *server = Start_server("42069");
    struct Route *node;
    struct request req;
    struct Route *route = Init_route("/", "index.html");
    route = Insert_route(route, "/hola", "hola.html");
    route = Insert_route(route, "/static/index.css", "index.css");

    while(1){
        client_fd = accept(server->socket_fd, NULL, NULL);
        rec_status = recv(client_fd, client_msg, MAXCLIENTLENGTH-1, 0);
        if(rec_status == 0){
            close(client_fd);
            printf("El usuario ha cerrado la conexión.\n");
            continue;
        }else if(rec_status == -1){
            perror("Recv error");
        }
        tokenize_request(&req, client_msg);

        node = Search_route(route, req.route);
        if(node == NULL){
            process_request(req, response, NULL);
        }else{
            process_request(req, response, node->value);
        }

        send(client_fd, response, strlen(response), 0);
        
        close(client_fd);
        free(req.route);
    }
    free(req.route);
    free(response);
    Free_routes(route);
    free(server);
    return 0;
}

void process_request(struct request request, char *response, char *value){
    char *render;
    char files_path[1024];
    memset(response, 0, 4096);

    if(value == NULL){
        goto notfound;
    }
    switch(request.method){
        case 'G':
            if(strstr(request.route, "static") != NULL){
                strcpy(files_path, "static/");
            }else{
                strcpy(files_path, "template/");
            }
            strcat(files_path, value);
            strcpy(response, "HTTP/1.1 200 OK\r\n\r\n");
            render = Render(files_path);
            if(render == NULL){
                goto notfound;
            }
            break;
        default:
        notfound:
            strcpy(response, "HTTP/1.1 404 NOT_FOUND\r\n\r\n");
            render = Render("template/notfound.html");
            if(render == NULL){
                printf("Error en el render\n");
                exit(1);
            }
            break;
    }
    strcat(response, render);
    strcat(response, "\r\n\r\n");
    free(render);
}

void tokenize_request(struct request *tok_req, char *request){
    char *lines = strtok(request, "\n");
    char *method = strtok(lines, " ");
    if(strcmp("GET", method) == 0){
        tok_req->method = 'G';
    }else{
        tok_req->method = 'U';
    }
    tok_req->route = normalize(strtok(NULL, " "));
    tok_req->version = strtok(NULL, " "); 
}

char *normalize(char *path){
    char *dest = malloc(512);
    char *token;
    memset(dest, 0, 512);
    if(strlen(path) >= 512){
        strcpy(dest, "toobig");
        return dest;
    }else if((token = strtok(path,"/")) == NULL){
        strcpy(dest, "/");
        return dest;
    }else{
        strcat(dest, "/");
        strcat(dest, token);
        while((token = strtok(NULL, "/")) != NULL){
            strcat(dest, "/");
            strcat(dest, token);
        };
    }
    return dest;
}
