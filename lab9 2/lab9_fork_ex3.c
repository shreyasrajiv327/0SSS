#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("Using fork() system call.\n");

    fork();
    fork();
    fork();
    fork();
    printf("Predict how many times this message will be printed\n");
    return 0;
}
