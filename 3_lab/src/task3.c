#include "task3.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int execute_task3(int argc, char const *argv[])
{
    // Seed rand
    srand(time(NULL));

    // Generate an n-dimensional vector of random integers
    const size_t n = 10;

    // Allocate memory for vector
    VECTOR vector = malloc(n * sizeof(int));

    // Fill vector with random integers
    for (size_t i = 0; i < n; i++)
    {
        vector[i] = rand() % 10;
    }

    // Print vector
    printf("Vector: ");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", vector[i]);
    }

    printf("\n");

    // Find a number in the vector
    int number = 0;

    // Get number from user
    printf("Please, enter a number [0-9]: ");
    scanf("%d", &number);

    // Keep track of number of found elements
    size_t found_elements = 0;

    // Store current index address
    VECTOR current_index = vector;

    bool end_of_vector = false;

    int dim = n;

    // Iterate over vector and call find_number for each element
    for (size_t i = 0; i < n; i++)
    {
        current_index = find_number(current_index, dim, number);

        // print current index
        // printf("Current index: %p\n", current_index);

        if (current_index != NULL)
        {
            printf("Found number %d at address %p\n", *current_index, current_index);
            current_index++;
            found_elements++;

            dim = n - (current_index - vector);
        }
        else
        {
            end_of_vector = true;
            break;
        }
    }

    // Print number of found elements
    printf("Found %zu elements\n", found_elements);

    // Free memory
    free(vector);

    return 0;
}

int *find_number(VECTOR vector, size_t vector_dimensions, int number)
{
    // printf("Looking from address %p\n", vector);

    for (size_t i = 0; i < vector_dimensions; i++)
    {
        if (vector[i] == number)
        {
            // Print address of found element
            //printf("Found number %d at address %p\n", vector[i], &vector[i]);
            return &vector[i];
        }
    }

    return NULL;
}
