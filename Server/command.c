//
// Created by simon on 22/01/19.
//

#include "command.h"

char *command_status(Client *clients, int i, char *buffer, int buffer_size)
{

    strncpy(buffer, "Server > Connected as ", buffer_size);
    strncat(buffer, clients[i].user, buffer_size - strlen(buffer) - 1);

}

char *command_help(char *buffer, int buffer_size)
{

    /*
     * TODO: Implement help command
     */
    strncpy(buffer, "Server > Help not implemented yet.", buffer_size);


}

char *command_undef(char *buffer, int buffer_size)
{

    strncpy(buffer, "Server > Command undefined. Please refer to the help.", buffer_size);

}

