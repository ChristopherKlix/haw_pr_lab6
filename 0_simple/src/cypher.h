#ifndef CYPHER_H
#define CYPHER_H

#include <stdlib.h>

// Utility types that help
// with readibility

// Relevant for input and output string
typedef char* CYPHER_MSG;

// Determines the cypher offset
typedef int CYPHER_KEY;

// Return values of cypher functions
typedef int CYPHER_STATUS;

// ENUM to easily determine encryption/decryption
typedef enum CYPHER_DIRECTION {
    CYPHER_ENCRYPT = 1,
    CYPHER_DECRYPT = (-1)
} CYPHER_DIRECTION;

// ENUM to easily set cypher mode
typedef enum CYPHER_MODE {
    CYPHER_MODE_CAESAR
} CYPHER_MODE;

// Proxy caller function to set encryption/decryption mode
void cypher_set_mode(CYPHER_MODE);

// Proxy caller function to start encryption
CYPHER_STATUS cypher_encrypt(CYPHER_MSG, CYPHER_MSG, CYPHER_KEY);

// Proxy caller function to start decryption
CYPHER_STATUS cypher_decrypt(CYPHER_MSG, CYPHER_MSG, CYPHER_KEY);

// Core function that performs the de/encryption
CYPHER_STATUS cypher(CYPHER_MSG, CYPHER_MSG, CYPHER_KEY, CYPHER_DIRECTION);

#endif