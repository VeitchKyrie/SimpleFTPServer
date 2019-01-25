#include <stdio.h>
#include <stdlib.h>

#include "server.h"


int main(int argc, char **argv)
{

    printf("==== Simple FTP Server! ====\n");

    SOCKET sock = init();
    start(sock);
    server_stop(sock);
    finish();

    return EXIT_SUCCESS;
}
