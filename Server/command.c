//
// Created by simon on 22/01/19.
//

#include "command.h"

/**
 * Response for the "status" command
 * @param clients
 * @param i
 * @param buffer
 * @param buffer_size
 * @return
 */
void *command_status(Client *clients, int i, char *buffer, int buffer_size)
{

    strncpy(buffer, "Server > Connected as ", buffer_size);
    strncat(buffer, clients[i].user, buffer_size - strlen(buffer) - 1);

}

/**
 * Response for the "help" command
 * @param buffer
 * @param buffer_size
 * @return
 */
void *command_help(char *buffer, int buffer_size)
{

    /*
     * TODO: Implement help command
     */
    strncpy(buffer, "Server > Help not implemented yet.", buffer_size);
    
}

/**
 * Response for an unknown command
 * @param buffer
 * @param buffer_size
 * @return
 */
void *command_undef(char *buffer, int buffer_size)
{

    strncpy(buffer, "Server > Command undefined. Please refer to the help.", buffer_size);

}

/**
 * Response for the ls command
 * List the files & folders inside a directory "folder"
 * @param folder
 * @param folder_size
 * @param buffer
 * @param buffer_size
 * @return
 */
void *command_ls(char *folder, char *buffer, int buffer_size)
{



}

/**
 * Response for the delete command
 * Deletes a file
 * @param folder
 * @param folder_size
 * @param buffer
 * @param buffer_size
 * @return
 */
void *command_delete(char *filepath, char *buffer, int buffer_size)
{

    int delete_status = deleteFile(filepath);

    if (delete_status > 0) {

        strncpy(buffer, "Server > Delete successful.", buffer_size);

    } else if (delete_status < 0) {

        strncpy(buffer, "Server > An error occurred while deleting desired file.", buffer_size);

    } else {

        strncpy(buffer, "Server > Desired file does not exist...", buffer_size);

    }

}

