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

void getStartFolder(char *folder, int folder_size)
{

    #ifdef _WIN32

        strncpy(folder, "C:/", folder_size);

    #else

        strncpy(folder, "/home/", folder_size);

    #endif

}

void listFolder(char *list, char *folder, int folder_size)
{



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