// include all necessary libraries
#include <stdio.h>
#include <stdlib.h>

// declare all functions
int *primes(int n);

int main(int argc, char const *argv[])
{
    // get the number n from the command line
    int n = atoi(argv[1]);

    // compute all primes up to n
    int *primes_array = primes(n);

    return 0;
}

// write a function that computes all primes up to a given number n
// and returns them as an array of integers
int *primes(int n)
{
    int *primes = malloc(n * sizeof(int));
    int i, j, k = 0;
    for (i = 2; i <= n; i++)
    {
        for (j = 2; j <= i; j++)
        {
            if (i % j == 0)
            {
                break;
            }
        }
        if (i == j)
        {
            primes[k] = i;
            k++;
        }
    }

    return primes;
}

