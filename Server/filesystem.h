//
// Created by simon on 22/01/19.
//

#ifndef SERVER_FILESYSTEM_H
#define SERVER_FILESYSTEM_H

    #ifndef WIN32

        #include <libnet.h>

    #endif

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


int doesFileExist(char *filepath);
void getStartFolder(char *folder, int folder_size);
int deleteFile(char *filepath);
int writeFile(char *filepath, char* data_buffer);
int writeDir(char *filepath);

#endif //SERVER_FILESYSTEM_H
