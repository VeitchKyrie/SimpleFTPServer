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
    #include "filesystem.h"

    void command_status(Client *clients, int nbClients, char *response_buffer);
    void command_help(char *buffer);
    void command_undef(char *buffer, int buffer_size);
    void command_ls(char *folder, char *buffer, int buffer_size);
    void command_put(char *filepath, char *data_buffer, int data_size, char *response_buffer, int response_size);
    void command_mkdir(char *filepath, char *response_buffer);
    void command_delete(char *filepath, char *buffer, int buffer_size);
    void command_cd(char *newpath, char *current_path, int currpath_size, char *response_buffer);

#endif //SERVER_COMMAND_H
