//
// Created by simon on 21/01/19.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#ifdef WIN32

#include <winsock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#include <string.h>

#include "client.h"

SOCKET init(void);
void finish(void);

SOCKET start(SOCKET sock);
void stop(SOCKET sock);

void close_all(Client *clients, int *nbClients);
void client_close(Client *clients, int i, int *nbClients);

int client_recv(SOCKET sock, char *msg);
int client_send(SOCKET sock, const char *msg);


#endif //SERVER_SERVER_H
