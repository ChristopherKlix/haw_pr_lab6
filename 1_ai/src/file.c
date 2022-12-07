// include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include the header file for this file
#include "file.h"

// write a function that reads a .txt file and returns the contents as a string
char *read_file(char *filename)
{
    // open the file
    FILE *file = fopen(filename, "r");
    // check if the file exists
    if (file == NULL)
    {
        printf("Error: File does not exist");
        return NULL;
    }
    // get the size of the file
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    // allocate memory for the string
    char *str = malloc(size * sizeof(char));
    // read the file
    fseek(file, 0, SEEK_SET);
    fread(str, sizeof(char), size, file);
    // close the file
    fclose(file);
    // return the string
    return str;
}
