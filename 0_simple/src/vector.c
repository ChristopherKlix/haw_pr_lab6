#include "vector.h"

int *find_int(int n, VECTOR vector, size_t vector_dimensions)
{
    int *first_address = NULL;

    for (size_t i = 0; i < vector_dimensions; i++)
    {
        if (vector[i] == n)
        {
            first_address = &vector[i];
        }
    }

    return first_address;
}