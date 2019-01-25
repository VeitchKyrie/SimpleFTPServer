#include <stdio.h>
#include <stdlib.h>

#include "client.h"

int main(int argc, char **argv)
{
    char host[255];
    char username[255];

    printf("Simple FTP Client! \n");
    printf("Writing \"help\" at any moment will show you all the possible commands \n");
    printf("Address : ");
    scanf("%s", &host);
    printf("Username : ");
    scanf("%s", &username);

    SOCKET sock = init(host);

    start(sock, username);
    stop(sock);

    finish();

    return EXIT_SUCCESS;
}
