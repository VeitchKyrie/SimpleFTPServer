#include "client.h"

SOCKET init(char *address){

#ifdef WIN32 // If windows
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0){
        printf("fail to load dll\n");
        exit(-1);
    }
#endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // Socket declaration (IPv4 and protocol)
    SOCKADDR_IN serv_addr;
    struct hostent *host;

    // If given host address is not available
    host = gethostbyname(address);
    if (host == NULL)
    {
        printf("%s is a unknown host. Please try again.\n", address);
        exit(-1);
    }

    serv_addr.sin_addr = *(IN_ADDR *) host->h_addr;
    serv_addr.sin_port = htons(1337); // Port declaration
    serv_addr.sin_family = AF_INET; // IPv4 configuration

    if(connect(sock,(SOCKADDR *) &serv_addr, sizeof(SOCKADDR)) < 0)
    {
        printf("connect() fail\n");
        exit(-1);
    }
    return sock;
}


void start(SOCKET sock, char *name)
{

    char command_buffer[1024]; // Init buffer

    fd_set fs; // Init set of socket "fs"

    // Send name
    server_send(sock, name);
    char *stop = NULL;
    int server_recv(SOCKET sock, char *command_buffer){
    int n = 0;

    if((n = recv(sock, command_buffer, 1024 - 1, 0)) < 0) // If error(s)
    {
        n = 0;
    }

    command_buffer[n] = 0;

    return n;
}

void server_send(SOCKET sock, char *buffer){
    send(sock, buffer, strlen(buffer), 0);
}

    // Infinite loop
    while(1)
    {

        FD_ZERO(&fs); // Clear set
        FD_SET(STDIN_FILENO, &fs); // If sending smthg to the sock
        FD_SET(sock, &fs); // If receiving smthg  form the sock

        if(select(sock + 1, &fs, NULL, NULL, NULL) < 0)
        { // If error(s)
            printf("Select error\n");
        }


        if(FD_ISSET(STDIN_FILENO, &fs)) // If something happened in the set (received or sent)
        {
            fgets(command_buffer, 1024 - 1, stdin) ;
            stop = strstr(command_buffer, "\n"); // If return, send the written command

            if(stop != NULL)
            {
                *stop = 0;
            }

            server_send(sock, command_buffer); // Send entered text to server
        }
        else if(FD_ISSET(sock, &fs))
        {

            if(server_recv(sock, command_buffer) == 0)
            {
                printf("Server not connected.\n");
                break;
            }

            puts(command_buffer); // Display server response

        }
    }

}


int server_recv(SOCKET sock, char *buffer){
    int n = 0;

    if((n = recv(sock, buffer, 1024 - 1, 0)) < 0)
    {
        n = 0;
    }

    buffer[n] = 0;

    return n;
}


void server_send(SOCKET sock, char *buffer){
    send(sock, buffer, strlen(buffer), 0);
}
void stop(SOCKET sock){
    closesocket(sock);
}


void finish(void)
{
#ifdef WIN32
    WSACleanup();
#endif
}
