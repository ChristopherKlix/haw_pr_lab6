#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef char* FILE_PATH;

typedef enum FILE_STATUS
{
    FILE_ERROR_INVALID_FILE_PATH,
    FILE_ERROR_FILE_READ_FAILURE,
    FILE_ERROR_FILE_WRITE_FAILURE,
    FILE_ERROR_FILE_SIZE_ZERO,
    FILE_ERROR_FILE_SIZE_TOO_LARGE,
    FILE_ERROR_REALLOC_FAILURE,
    FILE_ERROR_UNKNOWN,
    FILE_SUCCESS
}
FILE_STATUS;

FILE_STATUS read_file(FILE_PATH file_path, char **buffer, size_t *reallocated_buffer_size);

FILE_STATUS write_file(FILE_PATH file_path, char *buffer, size_t buffer_size);

#endif