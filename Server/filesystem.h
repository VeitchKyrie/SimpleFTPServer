//
// Created by simon on 22/01/19.
//

#ifndef SERVER_FILESYSTEM_H
#define SERVER_FILESYSTEM_H

#include <libnet.h>
#include <stdio.h>

int doesFileExist(char *filepath);
void getStartFolder(char *folder, int folder_size);
void listFolder(char *list, char *folder, int folder_size);
int deleteFile(char *filepath);

#endif //SERVER_FILESYSTEM_H
