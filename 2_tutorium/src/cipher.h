#ifndef CIPHER_H
#define CIPHER_H

#include "file.h"

#include <stdbool.h>

typedef enum CIPHER_MODE
{
    CIPHER_MODE_ENCRYPT,
    CIPHER_MODE_DECRYPT
}
CIPHER_MODE;

typedef enum CASE_MODE
{
    CASE_MODE_NONE,
    CASE_MODE_LOWER,
    CASE_MODE_UPPER
}
CASE_MODE;

typedef enum CIPHER_STATUS
{
    CIPHER_SUCCESS,
    CIPHER_ERROR_MALLOC_FAILURE,
    CIPHER_ERROR_INVALID_KEY,
    CIPHER_ERROR_INVALID_MODE,
    CIPHER_ERROR_INVALID_CASE_MODE,
    CIPHER_ERROR_INVALID_FILE_PATH,
    CIPHER_ERROR_FILE_READ_FAILURE,
    CIPHER_ERROR_FILE_WRITE_FAILURE
}
CIPHER_STATUS;

typedef const long ENCRYPTION_KEY;

CIPHER_STATUS cipher(
    CIPHER_MODE cipher_mode,
    FILE_PATH input_file_path,
    FILE_PATH output_file_path,
    ENCRYPTION_KEY key,
    CASE_MODE case_mode
);

CIPHER_STATUS encrypt_content(
    const char *content,
    size_t content_length,
    char *buffer,
    size_t buffer_length,
    ENCRYPTION_KEY key
);

CIPHER_STATUS decrypt_content(
    const char *content,
    size_t content_length,
    char *buffer,
    size_t buffer_length,
    ENCRYPTION_KEY key
);

char encrypt_character(char character, ENCRYPTION_KEY key);

bool is_alpha(char character);

#endif