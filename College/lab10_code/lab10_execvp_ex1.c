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

//Let us define an array of arguments for ps
char *const ls_argv[] = {"-l", 0}; // Need to be terminated by NULL
//char *const ps_argv[] = {"ps", "-all", 0};
char *const ps_argv[] = {"-all", 0};

int main() {
    pid_t new_pid;   // to store PID of the created process

    new_pid  = fork();

    switch(new_pid) {
    case -1:  // Error
        printf("There is an error while calling fork()\n");
        return ERROR;
    
    case 0:  // Child process, replace the copy of the parent with new image of ls program
        printf("Child: my PID = %d PPID = %d\n", (int)getpid(), (int)getppid());
        // int execvp(const char* command, char* argv[]);
        printf("Child: I am going to overlay with ps command.\n");
        //execvp("ls", ls_argv);
        execv("ls",ls_argv);
        printf("This message will never get printed.\n");
        break;
    default : // Parent process
        printf("Parent: my PID = %d, my PPID = %d and my child's PID = %d\n",
                (int) getpid(), (int) getppid(), (int)new_pid);
        printf("Parent: I am going to execute system(\"ls -l\") now.\n");
        system("ls -1");
        printf("Parent: This is printed after the ls command was executed.\n");
        break;

    } // end of switch()
    
    printf("Parent: going to terminate.\n");

    return SUCCESS;
}
