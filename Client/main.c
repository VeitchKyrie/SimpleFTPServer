#include <stdio.h>
#include <stdlib.h>

#include "client.h"

int main(int argc, char **argv)
{
    printf("Simple FTP Server : \n");
    char host[255];
    printf("Address : "); // 127.0.0.1 = localhost
    scanf("%s", &host);
    printf("Your name : ");
    char name[255];
    scanf("%s", &name);

    SOCKET sock = init(host);

    start(sock, name);
    stop(sock);

    finish();

    return EXIT_SUCCESS;
}
