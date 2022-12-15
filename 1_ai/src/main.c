// include all the header files
#include <stdio.h>
#include <stdlib.h>

// include file.h
#include "file.h"

// marco definition TASK
#define TASK 1

// typedef an integer array as VECTOR
typedef int* VECTOR;

// function declaration
void print_args(int argc, char const *argv[]);
VECTOR generate_vector(int n);
int *find_number(int *arr, int size, int number);
char *caesar_cipher(char *str, int key);

int main(int argc, char const *argv[])
{
    // store marco task in a variable
    int task = TASK;

    // if clause for task for 0 1 2
    if (task == 0)
    {
        // print all command line arguments
        print_args(argc, argv);
    }
    else if (task == 1)
    {
        // print the contents of the file
        char *str = read_file("./src/example.txt");
        printf("%s", str);

        // call caesar_cipher
        int key = 3;
        printf("Original string: %s", str);
        char *encrypted_str = caesar_cipher(str, key);
        printf("Encrypted string: %s", encrypted_str);

        // write the encrypted string into a file
        write_file("./src/encrypted.txt", encrypted_str);
    }
    else if (task == 2)
    {
        // generate a vector of size 10
        VECTOR vec = generate_vector(10);
        // find a number n in the vector
        int *number = find_number((vec), 10, 5);
    }

    return 0;
}

/* write a function that prints all command line arguments */
void print_args(int argc, char const *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s", argv[i]);
    }
}

// write a function that generates a VECTOR of size n
VECTOR generate_vector(int n)
{
    VECTOR vec = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        vec[i] = i;
    }
    return vec;
}

// write a function that finds a number in an array and returns its address
int *find_number(int *arr, int size, int number)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == number)
        {
            return &arr[i];
        }
    }
    return NULL;
}

char *caesar_cipher(char *str, int key)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = (str[i] - 'a' + key) % 26 + 'a';
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = (str[i] - 'A' + key) % 26 + 'A';
        }
        i++;
    }
    return str;
}
