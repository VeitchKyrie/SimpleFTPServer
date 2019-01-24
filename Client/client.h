#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <stdio.h>
#include <string.h>

#ifdef WIN32 // if windows
    #include <winsock2.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netdb.h>
#define closesocket(s) close(s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef struct in_addr IN_ADDR;

#endif


SOCKET init(char *address);
void finish(void);

void start(SOCKET sock, char *name);
void stop(SOCKET sock);

int server_recv(SOCKET sock, char *buffer);
void server_send(SOCKET sock, char *buffer);

void command_put(char *command_buffer);

#endif
