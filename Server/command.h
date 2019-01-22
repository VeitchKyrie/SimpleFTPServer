//
// Created by simon on 22/01/19.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

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

#include <libnet.h>
#include "client.h"

char *command_status(Client *client, int i, char *buffer, int buffer_size);
char *command_help(char *buffer, int buffer_size);
char *command_undef(char *buffer, int buffer_size);

#endif //SERVER_COMMAND_H
