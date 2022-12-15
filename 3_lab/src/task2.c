#include "task2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int execute_task2(int argc, char const *argv[])
{
    // Parse arguments
    // <input_filepath> <output_filepath> <key>

    if (argc != 4)
    {
        fprintf(stderr, "Invalid number of arguments. Expected 3, got %d\n", argc - 1);
        // Print usage instructions
        fprintf(stderr, "Usage: %s <input_filepath> <output_filepath> <key>\n", argv[0]);
        return 1;
    }

    // Parse input filepath

    // Get input filepath length
    size_t input_filepath_len = strlen(argv[1]);

    // Allocate memory for input filepath
    char *input_filepath = malloc(input_filepath_len + 1);

    // Copy input filepath to allocated memory
    strcpy(input_filepath, argv[1]);

    // Parse output filepath
    
    // Get output filepath length
    size_t output_filepath_len = strlen(argv[2]);

    // Allocate memory for output filepath
    char *output_filepath = malloc(output_filepath_len + 1);

    // Copy output filepath to allocated memory
    strcpy(output_filepath, argv[2]);

    // Parse key
    char *endptr;
    int key = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0')
    {
        fprintf(stderr, "Invalid key. Expected integer, got %s\n", argv[3]);
        return 1;
    }

    // Check if key is in range [1, 25]
    if (key < 1 || key > 25)
    {
        fprintf(stderr, "Invalid key. Expected integer in range [1, 25], got %d\n", key);
        return 1;
    }

    // Open input file
    FILE *fp_in = fopen(input_filepath, "r");

    // Open output file
    FILE *fp_out = fopen(output_filepath, "w");

    // Read input file with fseek
    fseek(fp_in, 0, SEEK_END);

    // Get file size
    long file_size = ftell(fp_in);

    // Reset file pointer
    fseek(fp_in, 0, SEEK_SET);

    // Allocate memory for file contents
    char *file_contents = malloc(file_size + 1);

    // Read file contents
    fread(file_contents, file_size, 1, fp_in);

    // Print file contents
    // fprintf(stderr, "%s\n", file_contents);

    // Add null terminator
    file_contents[file_size] = '\0';

    // Close input file
    fclose(fp_in);

    // Encrypt file contents
    char *buf = malloc(file_size + 1);

    encrypt_content(file_contents, file_size, buf, file_size + 1, key);

    // Add null terminator
    buf[file_size] = '\0';

    // Write encrypted file contents to output file
    fwrite(buf, file_size, 1, fp_out);

    // Close output file
    fclose(fp_out);

    // Free memory
    free(input_filepath);
    free(output_filepath);
    free(file_contents);
    free(buf);

    return 0;
}

int encrypt_content(char *content, size_t content_size, char *buf, size_t buf_size, int key)
{
    // Check if buffer is large enough
    if (buf_size < content_size)
    {
        fprintf(stderr, "Buffer is too small. Expected at least %ld bytes, got %ld bytes\n", content_size, buf_size);
        return 1;
    }

    // Encrypt content
    for (size_t i = 0; i < content_size; i++)
    {
        char c = content[i];

        c = toupper(c);

        // Check if character is a letter
        if (isalpha(c))
        {
            // Encrypt letter
            c = (c - 'A' + key) % 26 + 'A';
        }

        // Write encrypted character to buffer
        buf[i] = c;
    }

    return 0;
}