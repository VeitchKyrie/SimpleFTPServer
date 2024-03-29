//
// Created by simon on 21/01/19.
//
#include "server.h"

/**
 * Init libraries & variables on launch
 * @return SOCKET
 */
SOCKET init(void)
{

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

    return sock;
}

/**
 * Cleanup on quit
 */
void finish(void)
{
    #ifdef WIN32
        WSACleanup();
    #endif
}

SOCKET start(SOCKET sock) {

    printf("Server > Server open \n");

    if(listen(sock, 100) < 0) //Max clients 100
    {
        printf("Could not open port! Quitting.\n");
        exit(-1);
    }

    char buffer[1024], tmp_buffer[1024], response_buffer[1024];
    /* the index for the array */
    int nbClients = 0;//nb of client
    int set = 0;//select result
    int max = sock;
    int i;
    int server_open = 1;

    Client clients[100];

    fd_set fs;

    char current_folder[1024];
    getStartFolder(current_folder, sizeof(current_folder));

    while(server_open > 0) {
        i = 0;

        FD_ZERO(&fs);
        FD_SET(sock, &fs);

        for(i = 0; i < nbClients; i++){
            FD_SET(clients[i].sock, &fs);
        }

        set = select(max + 1, &fs, NULL, NULL, NULL);

        if (set < 0) {
            printf("Error doing select() on socket.\n");
        }
        else if(FD_ISSET(sock, &fs)) // Client Connection
        {

            SOCKADDR_IN cli_addr;
            int sinsize = sizeof(cli_addr);
            SOCKET cli = accept(sock, (SOCKADDR *) &cli_addr, &sinsize);

            Client c;
            c.sock = cli;
            if(client_receive(cli, c.user) < 0){
                /* disconnected */
            }
            printf("Server > User %s connected\n", c.user);

            max = cli > max ? cli : max;

            FD_SET(cli, &fs);

            clients[nbClients] = c;

            strncpy(tmp_buffer, "Bienvenue sur le serveur FTP\nServer ", sizeof(tmp_buffer));
            strncat(tmp_buffer, current_folder, sizeof(current_folder)-strlen(current_folder)-1);
            strncat(tmp_buffer, " > ", sizeof(current_folder)-strlen(current_folder)-1);

            client_respond(c.sock, tmp_buffer);

            nbClients++;
            printf("Server > %d clients connected\n",nbClients);
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
                    if(client_receive(clients[i].sock, buffer) < 1) // Client disconnection
                    {

                        printf("Server > User %s disconnected.\n",clients[i].user);
                        client_close(clients, i, &nbClients);

                    }
                    else // Client sending message
                    {

                        char command[1024] = {0};
                        char arguments[1024] = {0};

                        command_decipher(buffer, command, arguments);
                        response_prefix(response_buffer, current_folder);

                        if (strncmp(command, "status", sizeof(command)) == 0) {

                            printf("User %s > Status request\n", clients[i].user);
                            command_status(clients, nbClients, response_buffer);

                        } else if (strncmp(command, "delete", sizeof(command)) == 0) {

                            strncpy(tmp_buffer, current_folder, sizeof(tmp_buffer));
                            strncat(tmp_buffer, arguments, sizeof(tmp_buffer) - strlen(tmp_buffer) - 1);

                            printf("User %s > delete request : %s\n", clients[i].user, tmp_buffer);
                            command_delete(tmp_buffer, response_buffer);

                            free(tmp_buffer);

                        } else if (strncmp(command, "ls", sizeof(command)) == 0) {

                            printf("User %s > ls request\n", clients[i].user);
                            command_ls(current_folder, response_buffer);

                        } else if (strncmp(command, "help", sizeof(command)) == 0) {

                            printf("User %s > Help request\n", clients[i].user);
                            command_help(response_buffer);

                        } else if (strncmp(command, "cd", sizeof(command)) == 0) {

                            printf("User %s > Put request: %s\n", clients[i].user, arguments);
                            command_cd(arguments, current_folder, sizeof(current_folder), response_buffer);

                        } else if (strncmp(command, "mkdir", sizeof(command)) == 0) {

                            strncpy(tmp_buffer, current_folder, sizeof(tmp_buffer));
                            strncat(tmp_buffer, arguments, sizeof(tmp_buffer) - strlen(tmp_buffer) - 1);

                            printf("User %s > mkdir request: %s\n", clients[i].user, tmp_buffer);
                            command_mkdir(tmp_buffer, response_buffer);

                            free(tmp_buffer);

                        } else if (strncmp(command, "put", sizeof(command)) == 0) {

                            strncpy(tmp_buffer, current_folder, sizeof(tmp_buffer));
                            strncat(tmp_buffer, arguments, sizeof(tmp_buffer) - strlen(tmp_buffer) - 1);

                            char *data_buffer = "default data";

                            printf("User %s > Put request: %s\n", clients[i].user, tmp_buffer);
                            command_put(tmp_buffer, data_buffer, response_buffer);
                            free(tmp_buffer);
                            free(data_buffer);

                        } else if (strncmp(command, "quit", sizeof(command)) == 0) {

                            printf("User %s > Quit server request\n", clients[i].user);
                            client_close(clients, i, &nbClients);
                            break;

                        } else if (strncmp(command, "shutdown", sizeof(command)) == 0) {

                            printf("User %s > Close server request\n", clients[i].user);
                            server_open = 0;
                            break;

                        } else {

                            printf("User %s > Undefined command \"%s\"\n", clients[i].user, command);
                            command_undef(response_buffer);
                        }

                        /*
                         * Send response
                         */
                        client_respond(clients[i].sock, response_buffer);
                    }
                    break;
                }
            }
        }
    }

    client_close_all(clients, &nbClients);
    return 1;

}

/**
 * Return command & arguments from buffer
 * @param buffer
 * @param command
 * @param arguments
 */
void command_decipher(char *buffer, char *command, char *arguments)
{

    int space = 0;

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

}

/**
 * Construct server's response prefix (current folder)
 * @param response_buffer
 * @param current_folder
 */
void response_prefix(char *response_buffer, char *current_folder)
{

    strncpy(response_buffer, "Server ", sizeof(response_buffer));
    strncat(response_buffer, current_folder, sizeof(response_buffer)-strlen(response_buffer)-strlen(current_folder)-1);
    strncat(response_buffer, " > ", sizeof(response_buffer)-strlen(response_buffer)-4);

}

/**
 * Close the socket
 * @param sock
 */
void server_stop(SOCKET sock)
{
    closesocket(sock);
}

/**
 * Close all client connections
 * @param clients
 * @param nbClients
 */
void client_close_all(Client *clients, int *nbClients)
{
    int i = 0;
    for(i = 0; i < *nbClients; i++)
    {
        client_respond(clients[i].sock, "Server > Closing client connection");
        client_close(clients,i, nbClients);
    }
}

/**
 * Close a specific client connection
 * @param clients
 * @param i
 * @param nbClients
 */
void client_close(Client *clients, int i, int *nbClients)
{
    closesocket(clients[i].sock);
    memmove(clients + i, clients + i + 1, (*nbClients - i - 1) * sizeof(Client));
    (*nbClients)--;
    printf("Server > %d clients connected\n", *nbClients);
}

/**
 * Receive data from client
 * @param sock
 * @param msg
 * @return
 */
int client_receive(SOCKET sock, char *msg)
{
    int n = recv(sock, msg, 1024 - 1, 0);

    if(n < 0)
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
int client_respond(SOCKET sock, const char *msg)
{
    return send(sock, msg, strlen(msg), 0);
}
