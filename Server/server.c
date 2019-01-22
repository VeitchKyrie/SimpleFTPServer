//
// Created by simon on 21/01/19.
//
#include <stdio.h>
#include <string.h>

#include "server.h"

/**
 * Init libraries & variables on launch
 * @return
 */
SOCKET init(void){

    #ifdef WIN32

        WSADATA wsa;
        int err = WSAStartup(MAKEWORD(2, 2), &wsa);
        if(err < 0){
            printf("Load Dll fail\n");
            exit(EXIT_FAILURE);
        }

    #endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN serv_addr;

    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1337);
    serv_addr.sin_family = AF_INET;

    bind(sock,(SOCKADDR *) &serv_addr, sizeof(serv_addr));

    printf("Server init done!\n");

    return sock;
}

/**
 * Cleanup on quit
 */
void finish(void){
    #ifdef WIN32
        WSACleanup();
    #endif
}

SOCKET start(SOCKET sock) {

    printf("Opening server...\n");

    if(listen(sock, 100) < 0) { //Max clients 100
        printf("Could not open port! Quitting.\n");
        exit(-1);
    }

    char buffer[1024], tmpBuffer[1024];
    /* the index for the array */
    int nbClients = 0;//nb of client
    int set = 0;//select result
    int max = sock;
    int i;

    Client clients[100];

    fd_set fs;

    char current_folder[1024];
    getStartFolder(current_folder, sizeof(current_folder));

    while(1) {
        i = 0;

        FD_ZERO(&fs);
        FD_SET(sock, &fs);

        for(i = 0; i < nbClients; i++){
            FD_SET(clients[i].sock, &fs);
        }

        set = select(max + 1, &fs, NULL, NULL, NULL);

        if (set < 0)
        {
            printf("Error doing select() on socket.\n");
        }
        else if(FD_ISSET(sock, &fs)) // Client Connection
        {

            SOCKADDR_IN cli_addr;
            int sinsize = sizeof(cli_addr);
            SOCKET cli = accept(sock, (SOCKADDR *) &cli_addr, &sinsize);

            Client c;
            c.sock = cli;
            if(client_recv(cli, c.user) < 0){
                /* disconnected */
            }
            printf("User connected: %s\n", c.user);

            max = cli > max ? cli : max;

            FD_SET(cli, &fs);

            clients[nbClients] = c;

            strncpy(tmpBuffer, "Bienvenue sur le serveur FTP\nServer ", sizeof(tmpBuffer));
            strncat(tmpBuffer, current_folder, sizeof(current_folder)-strlen(current_folder)-1);
            strncat(tmpBuffer, " > ", sizeof(current_folder)-strlen(current_folder)-1);

            client_send(c.sock, tmpBuffer);

            nbClients++;
            printf("%d clients connected\n",nbClients);
        }
        else
        {
            /*
             * Testing data from each client
             */
            for(i = 0; i < nbClients; i++)
            {
                if(FD_ISSET(clients[i].sock, &fs))
                {
                    if(client_recv(clients[i].sock, buffer) < 1) // Client disconnection
                    {

                        printf("Disconnected: %s \n",clients[i].user);
                        client_close(clients, i, &nbClients);

                        if(nbClients == 0) {
                            return 1;
                        }

                    }
                    else // Client sending message
                    {

                        char command[1024] = {0};
                        int commandSize = 0;
                        int space = 0;
                        char arguments[1024] = {0};

                        for (int x = 0; x < strlen(buffer); x++) {


                            if (buffer[x] == ' ' && space < 1) {

                                space++;

                            } else {

                                if (space < 1) {

                                    strncat(command, &buffer[x], 1);

                                } else {

                                    strncat(arguments, &buffer[x], 1);

                                }

                            }

                        }

                        /*
                        printf("Command asked by %s : %s\n", clients[i].user, command);
                        printf("Arguments : %s\n", arguments);
                        */

                        if (strncmp(command, "status", sizeof(command)) == 0) {

                            printf("Client > Status request\n");
                            char response[1024] = {0};
                            command_status(clients, i, response, sizeof(response));
                            client_send(clients[i].sock, response);

                        } else if (strncmp(command, "delete", sizeof(command)) == 0) {

                            strncpy(tmpBuffer, current_folder, sizeof(tmpBuffer));
                            strncat(tmpBuffer, arguments, sizeof(tmpBuffer) - strlen(tmpBuffer) - 1);

                            printf("Client > delete request : %s\n", tmpBuffer);
                            char response[1024] = {0};
                            command_delete(tmpBuffer, response, sizeof(response));
                            client_send(clients[i].sock, response);

                        } else if (strncmp(command, "help", sizeof(command)) == 0) {

                            printf("Client > Help request\n");
                            char response[1024] = {0};
                            command_help(response, sizeof(response));
                            client_send(clients[i].sock, response);

                        } else {

                            printf("Client > Undefined request\n");
                            char response[1024] = {0};
                            command_undef(response, sizeof(response));
                            client_send(clients[i].sock, response);

                        }
                    }
                    break;
                }
            }
        }
    }

    close_all(clients, &nbClients);
    return sock;

}

/**
 * Close the socket
 * @param sock
 */
void stop(SOCKET sock) {
    closesocket(sock);
}

/**
 * Close all client connections
 * @param clients
 * @param nbClients
 */
void close_all(Client *clients, int *nbClients){
    int i = 0;
    for(i = 0; i < *nbClients; i++)
    {
        client_close(clients,i, nbClients);
    }
}

/**
 * Close a specific client connection
 * @param clients
 * @param i
 * @param nbClients
 */
void client_close(Client *clients, int i, int *nbClients){
    closesocket(clients[i].sock);
    memmove(clients + i, clients + i + 1, (*nbClients - i - 1) * sizeof(Client));
    (*nbClients)--;
    printf("%d clients already connected\n", *nbClients);

}

/**
 * Receive data from client
 * @param sock
 * @param msg
 * @return
 */
int client_recv(SOCKET sock, char *msg) {
    int n = 0;

    if((n = recv(sock, msg, 1024 - 1, 0)) < 0)
    {

        n = 0;
    }

    msg[n] = 0;

    return n;
}

/**
 * Send data to client
 * @param sock
 * @param msg
 * @return
 */
int client_send(SOCKET sock, const char *msg) {

    return send(sock, msg, strlen(msg), 0);

}
