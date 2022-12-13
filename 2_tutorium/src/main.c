#include "util.h"
#include "file.h"
#include "cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

void print_usage_instructions(const char*);

int main(int argc, char const *argv[])
{
    // Before executing any logic,
    // we parse the provided command line arguments
    // to determine the cipher mode,
    // the input file path,
    // and the encryption key.
    // We also check for optional flags
    // to determine the case mode
    // and whether the output file
    // should overwrite an existing file
    // or create a new file.
    //
    // For a correct implementation of argument parsing
    // for a command line program/interface, i.e., CLI,
    // a library like getopt() should be used.
    // For more complex CLI programs,
    // a library like argparse() should be used.
    //
    // See this StackOverflow answer for example implementations:
    // https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
    //
    // This is a simple implementation
    // that is sufficient for this program.
    // It is not a good example of how to implement argument parsing.
    // It is only used to demonstrate the use of command line arguments
    // and to show how to parse them.
    // To parse the flags, we use a simple getopt() implementation
    // that checks the flags [-ocC].


    // Check for argument count
    // The program needs at least 4 arguments
    // program_name <command> <input_file.txt> <key>
    if (argc < 4)
    {
        print_usage_instructions(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Variable to store the cipher mode
    CIPHER_MODE cipher_mode = CIPHER_MODE_ENCRYPT;

    // Switching on the command to determine the cipher mode
    // Utilizing the first character of the command
    // e.g., encrypt -> e
    //       decrypt -> d
    switch (argv[1][0])
    {
        case 'e':
            cipher_mode = CIPHER_MODE_ENCRYPT;
            break;
        case 'd':
            cipher_mode = CIPHER_MODE_DECRYPT;
            break;
        default:
            print_usage_instructions(argv[0]);
            exit(EXIT_FAILURE);
    }

    // Store the input file path
    FILE_PATH input_file_path = malloc(sizeof(*input_file_path) * (strlen(argv[2]) + 1));
    strcpy(input_file_path, argv[2]);

    // Get the length of the input file path
    size_t input_file_path_length = strlen(input_file_path);

    // TODO: Check if the provided string is a valid path

    // Store the key and "safely" convert it to an integer
    ENCRYPTION_KEY key = safe_strtol(argv[3], true);

    // Check if an [-ocC] flag(s) is/are provided
    // If so, store the output file path
    // and/or set the case mode
    // This requires at least 6 arguments
    // program_name <command> <input_file.txt> <key> [-o] <output_file.txt> [-cC]

    // write arg parse code to check for -o -C -c
    // if -o is provided, store the output file path
    // if -c is provided, set the case mode to lower
    // if -C is provided, set the case mode to upper
    // use getopt() to parse the arguments
    // https://www.gnu.org/software/libc/manual/html_node/Getopt.html









    // getopt() returns the next option character in argv
    // that matches a character in optstring
    // If getopt() finds another option character,
    // it returns that character, updating the external variable optind
    // and a static variable nextchar so that the next call to getopt()
    // can resume the scan with the following option character or argv-element.
    // If there are no more option characters,
    // getopt() returns -1.
    int opt;

    // Variable to store whether the -o flag is provided
    bool output_file_path_provided = false;

    // Variable to store the case mode
    CASE_MODE case_mode = CASE_MODE_NONE;

    if (argc > 4)
    {
        if (strcmp(argv[4], "-o") == 0)
        {
            output_file_path_provided = true;
        }
    }

    size_t index_of_case_flag = output_file_path_provided ? 6 : 4;

    if (argc > index_of_case_flag)
    {
        if (strcmp(argv[index_of_case_flag], "-c") == 0)
        {
            case_mode = CASE_MODE_LOWER;
        }
        else if (strcmp(argv[index_of_case_flag], "-C") == 0)
        {
            case_mode = CASE_MODE_UPPER;
        }
    }

    // Didn't use getopt() because it's not supported on Windows
    // and also it didn't work
    // dunno why

    // while ((opt = getopt(argc, (char *const *) argv, "ocC")) != -1)
    // {
    //     switch (opt) {
    //         case 'o':
    //             printf("option: -o provided\n");
    //             output_file_path_provided = true;
    //             break;
    //         case 'c':
    //             printf("option: -c provided\n");
    //             case_mode = CASE_MODE_LOWER;
    //             break;
    //         case 'C':
    //             printf("option: -C provided\n");
    //             case_mode = CASE_MODE_UPPER;
    //             break;
    //     default:
    //         print_usage_instructions(argv[0]);
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // Store the output file path if provided

    // Allocate memory for the output file path
    // This is necessary because the output file path
    // is only provided if the -o flag is set

    // Contains the output file path or the input file path
    // if the -o flag is not set
    FILE_PATH output_file_path = malloc(sizeof(*output_file_path) * input_file_path_length + 1);

    // Copy the input file path
    strcpy(output_file_path, input_file_path);
    size_t output_file_path_length = input_file_path_length;

    // If the -o flag is set, store the output file path
    if (output_file_path_provided)
    {
        // Get length of the output file path
        output_file_path_length = strlen(argv[5]);

        // TODO: Check if the provided string is a valid path
        // if so, continue with reallocating memory for the output file path
        // if not, print usage instructions and exit with EXIT_FAILURE

        // Reallocate memory for the output file path
        output_file_path = realloc(output_file_path, sizeof(*output_file_path) * (output_file_path_length + 1));

        // Copy the output file path
        strcpy(output_file_path, argv[5]);
    }


    // Finally, encrypt or decrypt the input file
    // and write the result to the output file
    CIPHER_STATUS cipher_error = cipher(cipher_mode, input_file_path, output_file_path, key, case_mode);

    // Check if the cipher function returned an error
    if (cipher_error != CIPHER_SUCCESS)
    {
        // Print the error message
        fprintf(stderr, "Error: text could not be %sed.\n", cipher_mode == CIPHER_MODE_ENCRYPT ? "encrypt" : "decrypt");

        // Free the output file path
        free(output_file_path);

        // Exit with EXIT_FAILURE
        exit(EXIT_FAILURE);
    }

    // Print the success message
    printf("Text was %sed successfully.\n", cipher_mode == CIPHER_MODE_ENCRYPT ? "encrypt" : "decrypt");
    printf("The %sed text is stored in %s.\n", cipher_mode == CIPHER_MODE_ENCRYPT ? "encrypt" : "decrypt", output_file_path);

    // Free the output file path
    free(input_file_path);
    free(output_file_path);

    return 0;
}

// This function prints usage instructions
void print_usage_instructions(const char *program_name)
{
    fprintf(stderr, "\033[1mUSAGE\033[0m\n");
    fprintf(stderr, "\t%s <command> <input_file.txt> <key> [-o] [output_file.txt] [-Cc]\n", program_name);
    fprintf(stderr, "\n");

    fprintf(stderr, "\033[1mCOMMANDS\033[0m\n");
    fprintf(stderr, "\tencrypt:\tEncrypt the input file with the key\n");
    fprintf(stderr, "\tdecrypt:\tDecrypt the input file with the key\n");
    fprintf(stderr, "\n");

    fprintf(stderr, "\033[1mOPTIONS\033[0m\n");
    fprintf(stderr, "\t-o\tWrite to a separate output file\n");
    fprintf(stderr, "\t-c\tConvert all to lowercase\n");
    fprintf(stderr, "\t-C\tConvert all to uppercase\n");
    fprintf(stderr, "\n");
}