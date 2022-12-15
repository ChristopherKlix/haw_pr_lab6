// possible executions
// 1, 2, 3
#define TASK 2

#include "task1.h"
#include "task2.h"
#include "task3.h"

int main(int argc, char const *argv[])
{
    #if TASK == 1
        execute_task1(argc, argv);
    #elif TASK == 2 
        execute_task2(argc, argv);
    #elif TASK == 3
        execute_task3(argc, argv);
    #endif

    return 0;
}
