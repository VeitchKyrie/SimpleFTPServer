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
#include <stdio.h>

#include "client.h"
#include "command.h"
#include "filesystem.h"

SOCKET init(void);
void finish(void);

SOCKET start(SOCKET sock);
void server_stop(SOCKET sock);

void command_decipher(char *buffer, char *command, char *arguments);
void response_prefix(char *response_buffer, char *current_folder);
int client_receive(SOCKET sock, char *msg);
int client_respond(SOCKET sock, const char *msg);
void client_close_all(Client *clients, int *nbClients);
void client_close(Client *clients, int i, int *nbClients);

#endif //SERVER_SERVER_H
