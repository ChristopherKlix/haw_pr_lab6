#include "cipher.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// This function encrypts or decrypts the input file
// and writes the result to the output file.
// It returns CIPHER_SUCCESS on success
// and CIPHER_FAILURE on unknown failure
// or a specific error code on known failure.
CIPHER_STATUS cipher(
    CIPHER_MODE cipher_mode,
    FILE_PATH input_file_path,
    FILE_PATH output_file_path,
    ENCRYPTION_KEY key,
    CASE_MODE case_mode
    )
{
    // Check if the key is valid
    if (key < 0 || key > 'z' - 'a')
    {
        // Return an error code
        return CIPHER_ERROR_INVALID_KEY;
    }

    // Check if the cipher mode is valid
    if (cipher_mode != CIPHER_MODE_ENCRYPT && cipher_mode != CIPHER_MODE_DECRYPT)
    {
        // Return an error code
        return CIPHER_ERROR_INVALID_MODE;
    }

    // Check if the case mode is valid
    if (case_mode != CASE_MODE_LOWER
        && case_mode != CASE_MODE_UPPER
        && case_mode != CASE_MODE_NONE)
    {
        // Return an error code
        return CIPHER_ERROR_INVALID_CASE_MODE;
    }

    // Safely open the input file

    // Create a buffer to store the input file contents
    char *input_file_contents;

    // Allocate temporary memory for the input file contents
    // It will be reallocated by read_file()
    // based on the size of the input file
    input_file_contents = malloc(sizeof(*input_file_contents) * 1);

    // Check if the memory allocation was successful
    if (input_file_contents == NULL)
    {
        // Return an error code
        return CIPHER_ERROR_MALLOC_FAILURE;
    }

    // Read the input file
    size_t input_file_size = 0;
    FILE_STATUS read_status = read_file(input_file_path, &input_file_contents, &input_file_size);

    // Check if the file was read successfully
    if (read_status != FILE_SUCCESS)
    {
        // Print an error message
        fprintf(stderr, "Error: Could not read file \"%s\"", input_file_path);

        // Print an error message based on the error code
        switch (read_status)
        {
            case FILE_ERROR_FILE_SIZE_TOO_LARGE:
                fprintf(stderr, "This file may be too large to read.\n");
                break;
            case FILE_ERROR_FILE_SIZE_ZERO:
                fprintf(stderr, "This file may be empty.\n");
                break;
            case FILE_ERROR_INVALID_FILE_PATH:
                fprintf(stderr, "This file path may be invalid.\n");
                break;
            case FILE_ERROR_REALLOC_FAILURE:
                fprintf(stderr, "Memory allocation failed.\n");
                break;
            default:
                fprintf(stderr, "An unknown error occurred.\n");
        }

        return CIPHER_ERROR_FILE_READ_FAILURE;
    }

    // Convert the input file contents to uppercase or lowercase
    if (case_mode == CASE_MODE_UPPER)
    {
        // Convert the input file contents to uppercase
        // and store the result in the same buffer
        // by using the toupper() function
        for (size_t c = 0; c < input_file_size; c++)
        {
            input_file_contents[c] = toupper(input_file_contents[c]);
        }
    }
    else if (case_mode == CASE_MODE_LOWER)
    {
        // Convert the input file contents to lowercase
        // and store the result in the same buffer
        // by using the tolower() function
        for (size_t c = 0; c < input_file_size; c++)
        {
            input_file_contents[c] = tolower(input_file_contents[c]);
        }
    }

    // Encrypt or decrypt the input file
    // based on the cipher mode
    if (cipher_mode == CIPHER_MODE_ENCRYPT)
    {
        encrypt_content(input_file_contents, input_file_size, input_file_contents, input_file_size, key);
    }
    else if (cipher_mode == CIPHER_MODE_DECRYPT)
    {
        decrypt_content(input_file_contents, input_file_size, input_file_contents, input_file_size, key);
    }
    else
    {
        return CIPHER_ERROR_INVALID_MODE;
    }

    // Write the result to the output file
    FILE_STATUS write_status = write_file(output_file_path, input_file_contents, input_file_size);

    // Check if the file was written successfully
    if (write_status != FILE_SUCCESS)
    {
        // Print an error message
        fprintf(stderr, "Error: Could not write to file \"%s\"", output_file_path);

        // Print an error message based on the error code
        switch (write_status)
        {
            case FILE_ERROR_INVALID_FILE_PATH:
                fprintf(stderr, "This file path may be invalid.\n");
                break;
            case FILE_ERROR_REALLOC_FAILURE:
                fprintf(stderr, "Memory allocation failed.\n");
                break;
            default:
                fprintf(stderr, "An unknown error occurred.\n");
        }

        return CIPHER_ERROR_FILE_WRITE_FAILURE;
    }

    return CIPHER_SUCCESS;
}

// This function encrypts the content
// and stores the result in the buffer.
CIPHER_STATUS encrypt_content(
    const char *content,
    size_t content_length,
    char *buffer,
    size_t buffer_length,
    ENCRYPTION_KEY key
    )
{
    // Check if the buffer is large enough to store the encrypted content
    if (buffer_length < content_length)
    {
        // Reallocate memory for the buffer
        buffer = realloc(buffer, sizeof(*buffer) * content_length);

        // Check if the memory allocation was successful
        if (buffer == NULL)
        {
            // Return an error code
            return CIPHER_ERROR_MALLOC_FAILURE;
        }
    }

    // Encrypt the content
    // Iterate over the content
    // and encrypt each character if it is a letter
    for (size_t i = 0; i < content_length; i++)
    {
        // Check if the character is a letter
        if (is_alpha(content[i]))
        {
            // Encrypt the character
            buffer[i] = encrypt_character(content[i], key);
        }
        else
        {
            // Copy the character
            buffer[i] = content[i];
        }
    }

    return CIPHER_SUCCESS;
}

// This function decrypts the content
// and writes the result to the buffer.
// It is a proxy function for encrypt()
// that calls encrypt() with the decryption key.
// The decryption key is the negative of the encryption key.
CIPHER_STATUS decrypt_content(
    const char *content,
    size_t content_length,
    char *buffer,
    size_t buffer_length,
    ENCRYPTION_KEY key
    )
{
    // Decrypt the character by inverting the encryption key
    ENCRYPTION_KEY decryption_key = key * (-1);

    // Call the encrypt() function
    // with the decryption key
    return encrypt_content(content, content_length, buffer, buffer_length, decryption_key);
}

// This function encrypts the character
// and returns the encrypted character
// or the original character if it is not a letter.
// The encryption key is added to the character's ASCII value
// and the result is wrapped around if it is outside the ASCII range.
char encrypt_character(char character, ENCRYPTION_KEY key)
{
    // Check if the character is a lowercase letter
    if (character >= 'a' && character <= 'z')
    {
        // Encrypt the character
        character = (character - 'a' + key) % 26 + 'a';
    }
    // Check if the character is an uppercase letter
    else if (character >= 'A' && character <= 'Z')
    {
        // Encrypt the character
        character = (character - 'A' + key) % 26 + 'A';
    }

    return character;
}

// This function checks if the character is a letter
bool is_alpha(char character)
{
    // Check if the character is a letter
    if (character >= 'a' && character <= 'z')
    {
        return true;
    }
    else if (character >= 'A' && character <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}
