#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
/* Cabecera de respuesta de ejemplo
"200 OK\n"
"Access-Control-Allow-Origin: *\n"
"Content-Encoding: gzip\n"
"Content-Type: text/html; charset=utf-8\n"
"Date: Mon, 18 Jul 2016 16:06:00 GMT\n"
"Etag: \"c561c68d0ba92bbeb8b0f612a9199f722e3a621a\"\n"
"Keep-Alive: timeout=5, max=997\n"
"Last-Modified: Mon, 18 Jul 2016 02:36:04 GMT\n"
"Server: Apache\n"
"Set-Cookie: mykey=myvalue; expires=Mon, 17-Jul-2017 16:06:00 GMT; Max-Age=31449600; Path=/; secure\n"
"Transfer-Encoding: chunked\n"
"Vary: Cookie, Accept-Encoding\n"
"X-Backend-Server: developer2.webapp.scl3.mozilla.com\n"
"X-Cache-Info: not cacheable; meta data too large\n"
"X-kuma-revision: 1085259\n"
"x-frame-options: DENY\n";
*/

int main(){
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(6969),
        .sin_addr.s_addr = INADDR_ANY
    };
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    bind(serverSocket, (struct sockaddr *) &server_addr, sizeof(server_addr));

    listen(serverSocket, 5);

    printf("Estoy Escuchando en puerto 6969\n");
    int clientSocket;
    char clientMsg[10000] = "";
    char buf[2048] = "HTTP/1.1 200 OK\n"
        "Connection: close\r\n\n"
        "<html><h1>Hello World!<!h1><!html>\n";
    while(1){
        clientSocket = accept(serverSocket, NULL, NULL);
        read(clientSocket, clientMsg, 9999);
        printf("%s\n", clientMsg);
        printf("%lu", sizeof(buf));
        send(clientSocket, &buf, sizeof(buf)-1, 0);
        close(clientSocket);
    }
    printf("Fuera del loop\n");

    return 0;
}
