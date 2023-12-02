#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Ref: https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus
// Lab10: execvp() and system() calls explained
// Build command: gcc -o ex1 lab10_execvp_ex1.c
// Run it: ./ex1

#define SUCCESS 0
#define ERROR  -1

// Let us define an array of arguments for ps
char *const ls_argv[] = {"ls", "-l", 0}; // Need to be terminated by NULL
char *const ps_argv[] = {"ps", "-all", 0};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Give more numbers");
        exit(0);
    }

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        sum += num;
    }

    pid_t new_pid;   // to store PID of the created process

    new_pid = fork();

    switch (new_pid) {
        case -1:  // Error
            printf("There is an error while calling fork()\n");
            return ERROR;

        case 0:  // Child process which will execute the ./mul program that is a different program
            printf("Child: my PID = %d PPID = %d\n", (int)getpid(), (int)getppid());
            // int execvp(const char* command, char* argv[]);
            printf("Child: I am going to overlay and execute the ./mul program\n");
            execvp("./mul", argv);
            printf("This message will never get printed.\n");
            break;

        default : // Parent process this will execute the ./sum program that will be written in this block
            printf("Parent: my PID = %d, my PPID = %d and my child's PID = %d\n",
                   (int)getpid(), (int)getppid(), (int)new_pid);
            printf("Parent: I am going to execute the sum of the given numbers\n");
            printf("The sum of the numbers passed is: %d\n", sum);
            printf("This is the end of the program\n");
            break;

    } // end of switch()

    printf("Parent: going to terminate.\n");

    return SUCCESS;
}
