#include "task1.h"

#include <stdio.h>

int execute_task1(int argc, char const *argv[])
{
    // Print all arguments
    for (int i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    
    // Print new line
    printf("\n");

    return 0;
}