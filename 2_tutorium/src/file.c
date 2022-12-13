#include "file.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This function reads a file into a buffer
// and returns a FILE_STATUS indicating
// whether the file could be read successfully.
// The buffer is provided as a pointer by the caller
// and is reallocated to the size of the file.
FILE_STATUS read_file(FILE_PATH file_path, char **buffer, size_t *reallocated_buffer_size)
{
    // Open the file in read mode
    FILE *fp = fopen(file_path, "r");

    // Check if the file could be opened
    if (fp == NULL)
    {
        return FILE_ERROR_INVALID_FILE_PATH;
    }

    // Get the file size
    fseek(fp, 0, SEEK_END);

    // Store the file size
    size_t file_size = ftell(fp);

    if (file_size == 0)
    {
        return FILE_ERROR_FILE_SIZE_ZERO;
    }

    // Temporary check to prevent memory exhaustion
    if (file_size > 1000000)
    {
        return FILE_ERROR_FILE_SIZE_TOO_LARGE;
    }

    // Temporarily store the pointer to the buffer
    char *tmp_buffer = *buffer;

    // Reallocate memory for the buffer
    *buffer = realloc(*buffer, sizeof(**buffer) * (file_size + 1));

    // Check if the memory could be reallocated
    if (*buffer == NULL)
    {
        // Restore the pointer to the buffer
        *buffer = tmp_buffer;

        return FILE_ERROR_REALLOC_FAILURE;
    }

    // Store the size of the reallocated buffer
    *reallocated_buffer_size = file_size + 1;


    // From this point on, the memory of the buffer
    // has enough space to store the file

    // Reset the file pointer to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    // Read the file into the buffer
    size_t bytes_read = fread(*buffer, sizeof(**buffer), file_size, fp);

    // Check if the file could be read
    if (bytes_read != file_size)
    {
        return FILE_ERROR_UNKNOWN;
    }

    // Close the file
    fclose(fp);

    return FILE_SUCCESS;
}

// This function writes a buffer to a file
// and returns a FILE_STATUS indicating
// whether the file could be written successfully.
FILE_STATUS write_file(FILE_PATH file_path, char *buffer, size_t buffer_size)
{
    // Open the file in write mode
    FILE *fp = fopen(file_path, "w");

    // Check if the file could be opened
    if (fp == NULL)
    {
        return FILE_ERROR_INVALID_FILE_PATH;
    }

    // Write string buffer to file
    fprintf(fp, "%s", buffer);

    // Write the buffer to the file
    // size_t bytes_written = fwrite(buffer, sizeof(*buffer), buffer_size, fp);

    // // Check if the file could be written
    // if (bytes_written != buffer_size)
    // {
    //     return FILE_ERROR_UNKNOWN;
    // }

    // Close the file
    fclose(fp);

    return FILE_SUCCESS;
}