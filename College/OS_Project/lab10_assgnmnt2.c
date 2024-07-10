#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define SUCCESS 0
#define ERROR  -1

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Give more numbers\n");
        exit(0);
    }

    int product = 1; // Initialize to 1 for multiplication
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        product *= num; // Multiply instead of add
    }

    pid_t new_pid;

    new_pid = fork();

    switch (new_pid) {
        case -1:  // Error
            printf("There is an error while calling fork()\n");
            return ERROR;

        case 0:  // Child process which will execute the ./mul program
            printf("Child: my PID = %d PPID = %d\n", (int)getpid(), (int)getppid());
            printf("Child: I am going to overlay and execute the ./mul program\n");
            execvp("./mul", argv);
            printf("This message will never get printed.\n");
            break;

        default : // Parent process executes ./sum
            printf("Parent: my PID = %d, my PPID = %d and my child's PID = %d\n",
                   (int)getpid(), (int)getppid(), (int)new_pid);
            printf("Parent: I am going to execute the product of the given numbers\n");
            printf("The product of the numbers passed is: %d\n", product);
            printf("This is the end of the program\n");
            break;
    }

    printf("Parent: going to terminate.\n");

    return SUCCESS;
}
