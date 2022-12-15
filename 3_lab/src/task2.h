#ifndef TASK2_H
#define TASK2_H

#include <stdlib.h>

int execute_task2(int argc, char const *argv[]);

int encrypt_content(char *content, size_t content_size, char *buf, size_t buf_size, int key);

#endif