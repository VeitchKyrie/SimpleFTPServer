#include "client.h"

SOCKET init(char *address)
{

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
    int server_recv(SOCKET sock, char *command_buffer)
    {
    int n = 0;

    if((n = recv(sock, command_buffer, 1024 - 1, 0)) < 0) // If error(s)
    {
        n = 0;
    }

    command_buffer[n] = 0;

    return n;
}

void server_send(SOCKET sock, char *buffer)
{
    send(sock, buffer, strlen(buffer), 0);
}

    // Infinite loop
    while(1)
    {
        FD_ZERO(&fs); // Clear set
        FD_SET(STDIN_FILENO, &fs); // If sending smthg to the sock
        FD_SET(sock, &fs); // If receiving smthg  form the sock

        if(select(sock + 1, &fs, NULL, NULL, NULL) < 0) // If error(s)
        {
            printf("Select error\n");
        }
        else if(FD_ISSET(STDIN_FILENO, &fs)) // If something happened in the set (received or sent)
        {
            fgets(command_buffer, 1024 - 1, stdin) ;
            stop = strstr(command_buffer, "\n"); // If return, send the written command

            if(stop != NULL)
            {
                *stop = 0;
            }

            if(strncmp(command_buffer, "put", 3) == 0) // If user enter "put"
            {
                command_put(command_buffer);
            }
            else if((command_buffer, "get", 3) == 0) // If user enter "get"
            {
                command_get(command_buffer);
            }
            else // If he enter another command
            {
                server_send(sock, command_buffer); // Send entered text to server
            }
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


int server_recv(SOCKET sock, char *command_buffer){
    int n = 0;

    if((n = recv(sock, command_buffer, 1024 - 1, 0)) < 0)
    {
        n = 0;
    }

    command_buffer[n] = 0;
    return n;
}


void server_send(SOCKET sock, char *command_buffer){
    send(sock, command_buffer, strlen(command_buffer), 0);
}


void command_put(char *command_buffer)
{
    char command[1024] = {0};
    int commandSize = 0;
    int space = 0;
    char file_path[1024] = {0};

    for (int x = 0; x < strlen(command_buffer); x++)
    {
        if (command_buffer[x] == ' ' && space < 1)
        {
            space++;
        }
        else
        {
            if (space < 1)
            {
                strncat(command, &command_buffer[x], 1);
            }
            else
            {
                strncat(file_path, &command_buffer[x], 1);
            }
        }
    }

    printf("Command : %s \n", command);
    printf("File path : %s \n", file_path);
    printf("%s sent to server. \n", file_path);
}

void command_get(char *command_buffer)
{
    char command[1024] = {0};
    int commandSize = 0;
    int space = 0;
    char file_path[1024] = {0};
    char *data_buffer = "default data";


    for (int x = 0; x < strlen(command_buffer); x++)
    {
        if (command_buffer[x] == ' ' && space < 1)
        {
            space++;
        }
        else
        {
            if (space < 1)
            {
                strncat(command, &command_buffer[x], 1);
            }
            else
            {
                strncat(file_path, &command_buffer[x], 1);
            }
        }
    }

    if(writeFile(file_path, data_buffer) >= 0) 
    {
        printf("%s received from server.\n", file_path);
    } else {
        printf("Error");
    }
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
