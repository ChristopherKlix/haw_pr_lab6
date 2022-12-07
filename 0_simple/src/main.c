#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cypher.h"
#include "vector.h"

#define TASK 2;

void read_command_line_args(int, char const*[]);
int caesar_cypher(void);
void vector(void);

int main(int argc, char const *argv[])
{
    int task = TASK;

    if (task == 0)
    {
        read_command_line_args(argc, argv);
    }
    else if (task == 1)
    {
        caesar_cypher();
    }
    else if (task == 2)
    {
        vector();
    }

    return 0;
}

void read_command_line_args(int argc, char const *argv[])
{
    printf("%d\n", argc);

    for (size_t i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return;
}

int caesar_cypher(void)
{
    char buf[1024];
    FILE *fp;
    size_t nread;

    fp = fopen("in.txt", "r");

    if (fp)
    {
        while ((nread = fread(buf, 1, sizeof(buf), fp)) > 0)
        {
            // DEBUG read
            // fwrite(buf, 1, nread, stdout);
        }

        if (ferror(fp))
        {
            /* deal with error */
        }

        fclose(fp);
    }

    printf("buf: %s\n", buf);

    char unencrypted[1024] = "";
    char encrypted[1024] = "";
    strcpy(unencrypted, buf);

    printf("unencrypted: %s\n", unencrypted);
    int key = 3;

    // Set cypher mode
    cypher_set_mode(CYPHER_MODE_CAESAR);

    int status = cypher_encrypt(unencrypted, encrypted, key);
    if (status != 0) return (-1);

    printf("encrypted: %s\n", encrypted);

    fp = fopen("out.txt", "w");

    if (fp)
    {
        fputs(encrypted, fp);

        if (ferror(fp))
        {
            /* deal with error */
        }

        fclose(fp);
    }

    return 0;
}

void vector(void)
{
    srand(time(NULL));

    size_t vector_dimensions = 3;

    VECTOR vector = malloc(vector_dimensions * sizeof(*vector));

    for (size_t i = 0; i < vector_dimensions; i++)
    {
        vector[i] = rand() % 100;
    }

    int n = 5;
    int *first_address = find_int(n, vector, vector_dimensions);

    printf("Address of %d: %p\n", n, first_address);

    free(vector);

    return;
}
