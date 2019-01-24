#include <stdio.h>
#include <stdlib.h>

#include "client.h"

int main(int argc, char **argv)
{
    printf("Simple FTP Server ! \n");
    printf("Writting \"help\" at any moment will show you all the possible commands \n");
    char host[255];
    printf("Address : "); // 127.0.0.1 = localhost
    scanf("%s", &host);
    printf("Username : ");
    char username[255];
    scanf("%s", &username);

    SOCKET sock = init(host);

    start(sock, username);
    stop(sock);

    finish();

    return EXIT_SUCCESS;
}
