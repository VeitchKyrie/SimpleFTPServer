//
// Created by simon on 22/01/19.
//

#include "filesystem.h"

/**
 * Test if file exists
 * @param filepath
 * @return 1 if file exists, 0 if not.
 */
int doesFileExist(char *filepath)
{

    FILE *file = fopen(filepath, "r");

    if (file) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }

}

/**
 * Test if folder exists
 * @param filepath
 * @return
 */
int doesFolderExist(char *filepath)
{
    struct stat st = {0};

    if (stat(filepath, &st) == -1) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * Get server's start folder
 * @param folder
 * @param folder_size
 */
void getStartFolder(char *folder, int folder_size)
{

    #ifdef _WIN32

        // Default server folder for windows : C:/
        strncpy(folder, "C:/", folder_size);

    #else

        // Default server folder for unix based systems : /
        strncpy(folder, "/", folder_size);

    #endif

}

/**
 * Delete a file
 * @param filepath
 * @return int -1 if error, 0 if file does not exist, 1 if success
 */
int deleteFile(char *filepath)
{

    printf("%s", filepath);

    if (doesFileExist(filepath))
    {

        if (remove(filepath) == 0) {

            // Delete successful
            return 1;

        } else {

            // Error while deleting
            return -1;

        }

    } else {

        //File does not exist
        return 0;

    }

}

/**
 * Write file
 * @param filepath
 * @param data_buffer
 * @return
 */
int writeFile(char *filepath, char* data_buffer)
{

    FILE* file = NULL;
    file = fopen(filepath, "w");

    if (file != NULL) {

        fputs(data_buffer, file);
        fclose(file);
        return 1;

    }

    return 0;

}

/**
 * Create a directory
 * @param filepath
 * @param data_buffer
 * @param data_size
 * @return
 */
int writeDir(char *filepath)
{

    if (doesFolderExist(filepath) < 1) {

        mkdir(filepath, 0700);
        return 1;

    } else {

        return 0;

    }

}