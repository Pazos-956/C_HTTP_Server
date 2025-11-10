#include "server.h"

int main(){
    int server_fd = Start_server();
    Accept_connections(server_fd);
    return 0;
}
