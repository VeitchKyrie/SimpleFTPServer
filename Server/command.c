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
void command_status(Client *clients, int nbClients, char *response_buffer)
{

    strncat(response_buffer, "Current clients:\n", sizeof(response_buffer)-strlen(response_buffer)-1);

    for (int i = 0; i < nbClients; i++) {

        char userid[12];
        sprintf(userid, "%d", i);

        strncat(response_buffer, "#", sizeof(response_buffer)-strlen(response_buffer)-1);
        strncat(response_buffer, userid, sizeof(response_buffer)-strlen(response_buffer)-1);
        strncat(response_buffer, ": ", sizeof(response_buffer)-strlen(response_buffer)-1);
        strncat(response_buffer, clients->user, sizeof(response_buffer)-strlen(response_buffer)-1);
        strncat(response_buffer, "\n", sizeof(response_buffer)-strlen(response_buffer)-1);

    }

}

/**
 * Response for the "help" command
 * @param buffer
 * @param buffer_size
 * @return
 */
void command_help(char *response_buffer)
{

    char tmp[1024];

    strncpy(tmp, "Available Commands:\n", sizeof(tmp));
    strncat(tmp, "- cd [directory]: changes the active directory to \"directory\". Path is absolute.\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- get [file]: downloads the file \"file\" from the server to the client computer.\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- ls: displays all files and directories in the current directory.\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- mkdir [directory]: creates a directory \"directory\".\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- delete [file]: deletes the file or directory \"file\".\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- put [file]: uploads the file \"file\" from the client computer to the server (WIP)\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- status: lists all connected users\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- quit : closes server connection\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "- shutdown: gracefully shuts down the server.", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "(WIP: work in progress)\n", sizeof(tmp)-strlen(tmp)-1);
    strncat(tmp, "(All paths are relative to current path unless said otherwise)\n", sizeof(tmp)-strlen(tmp)-1);

    strncat(response_buffer, tmp, sizeof(response_buffer)-strlen(response_buffer)-1);

}

/**
 * Response for an unknown command
 * @param buffer
 * @param buffer_size
 * @return
 */
void command_undef(char *response_buffer, int buffer_size)
{

    strncat(response_buffer, "Command undefined. Please refer to the help.", sizeof(response_buffer)-strlen(response_buffer)-1);

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
void command_ls(char *folder, char *buffer, int buffer_size)
{



}

/**
 * Handling the put command
 * @param filepath
 * @param response_buffer
 * @param response_size
 */
void command_put(char *filepath, char *data_buffer, int data_size, char *response_buffer, int response_size)
{

    if (writeFile(filepath, data_buffer, data_size) >= 0) {

        strncat(response_buffer, "Create successful.", sizeof(response_buffer)-strlen(response_buffer)-1);

    } else {

        strncat(response_buffer, "Create file error.", sizeof(response_buffer)-strlen(response_buffer)-1);

    }

}

/**
 * Create folder
 * @param filepath
 * @param response_buffer
 */
void command_mkdir(char *filepath, char *response_buffer)
{

    if (writeDir(filepath) >= 0) {

        strncat(response_buffer, "Create successful.", sizeof(response_buffer)-strlen(response_buffer)-1);

    } else {

        strncat(response_buffer, "Create folder error.", sizeof(response_buffer)-strlen(response_buffer)-1);

    }

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
void command_delete(char *filepath, char *buffer, int buffer_size)
{

    int delete_status = deleteFile(filepath);

    if (delete_status > 0) {

        strncat(buffer, "Delete successful.", sizeof(buffer)-strlen(buffer)-1);

    } else if (delete_status < 0) {

        strncat(buffer, "An error occurred while deleting desired file.", sizeof(buffer)-strlen(buffer)-1);

    } else {

        strncat(buffer, "Desired file does not exist...", sizeof(buffer)-strlen(buffer)-1);

    }

}

/**
 * Moves the currentpath to newpath
 * newpath is not relative to currentpath!
 * @param newpath
 * @param current_path
 * @param currpath_size
 * @param response_buffer
 */
void command_cd(char *newpath, char *current_path, int currpath_size, char *response_buffer)
{

    if (doesFileExist(newpath) > 0) {

        strncpy(current_path, newpath, currpath_size);
        if (strncmp(&newpath[strlen(newpath)-1], "/", 1) != 0) //The address has to end with "/"
        {
            strncat(current_path, "/", 1);
        }

        strncat(response_buffer, "New directory: ", sizeof(response_buffer)-strlen(response_buffer)-1);
        strncat(response_buffer, current_path, sizeof(response_buffer)-strlen(response_buffer)-1);


    } else {

        strncat(response_buffer, "Can't cd: directory does not exist.", sizeof(response_buffer)-strlen(response_buffer)-1);

    }

}