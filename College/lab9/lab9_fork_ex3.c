#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("Using fork() system call.\n");

    fork();
    printf("\nfirst child");
    fork();
    printf("\nSecond child");
    fork();
    printf("\nThird child");
    return 0;
}
