#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

// Segun getaddrinfo tienes que redefinirlo? Al final se cambia en las flags de GCC. Ver mas
#define _POSIX_C_SOURCE 200112L
// Peticiones pendientes de aceptar que se pueden almacenar en la cola.
#define BACKLOG 10
#define MAXCLIENTLENGTH 1500

struct Server{
    int socket_fd;
    char *port;
};

struct Server *Start_server(char *port);
