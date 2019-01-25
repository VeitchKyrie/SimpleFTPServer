#include "filesystem.h"

int writeFile(char *filepath, char *data_buffer)
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