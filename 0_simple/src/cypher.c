#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypher.h"

// Proxy caller function to start encryption
CYPHER_STATUS cypher_encrypt(CYPHER_MSG msg, CYPHER_MSG buf, CYPHER_KEY key)
{
    return cypher(msg, buf, key, CYPHER_ENCRYPT);
}

// Proxy caller function to start decryption
CYPHER_STATUS cypher_decrypt(CYPHER_MSG msg, CYPHER_MSG buf, CYPHER_KEY key)
{
    return cypher(msg, buf, key, CYPHER_DECRYPT);
}

// Core function that performs the encryption
// Accepts an input string in the format CYPHER_MSG
// and returns an encrypted or decrypted
CYPHER_STATUS cypher(CYPHER_MSG msg, CYPHER_MSG buf, CYPHER_KEY _key, CYPHER_DIRECTION cypher_direction)
{
    // Compute length of the message to
    // avoid segmantation fault in for-loop
    size_t msg_len = strlen(msg);

    // Utilize clever CYPHER_DIRECTION bit value to perform
    // key mapping that allows the use of the
    // same logic for encryption and decryption
    const CYPHER_KEY key = _key * cypher_direction;

    // Defining a few ASCII constants
    // for better readibility
    const int ASCII_UPP_A = 'A';
    const int ASCII_UPP_Z = 'Z';
    const int ASCII_LOW_A = 'a';
    const int ASCII_LOW_Z = 'z';

    // Defining ASCII ranges
    // for better readibility
    const size_t UPP_RANGE = ASCII_UPP_Z - ASCII_UPP_A + 1;
    const size_t LOW_RANGE = ASCII_LOW_Z - ASCII_LOW_A + 1;

    for (size_t i = 0; i < msg_len; i++)
    {
        // Store message letter in ASCII format
        const int ascii_val = msg[i];

        // Buffer for encrypted/decrypted letter
        char cypher_c = '\0';

        // Perform encryption/decryption
        if (ascii_val > ASCII_UPP_A-1 && ascii_val < ASCII_UPP_Z+1)
        {
            // Upper case letter
            cypher_c = (((ascii_val - ASCII_UPP_A) + key) % (UPP_RANGE)) + ASCII_UPP_A;
        }
        else if (ascii_val > ASCII_LOW_A-1 && ascii_val < ASCII_LOW_Z+1)
        {
            // Lower case letter
            cypher_c = (((ascii_val - ASCII_LOW_A) + key) % (LOW_RANGE)) + ASCII_LOW_A;
        }
        else
        {
            cypher_c = ascii_val;
        }

        // Assign encrypted/decrypted letter to buffer
        buf[i] = cypher_c;
    }

    return 0;
}