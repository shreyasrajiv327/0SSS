#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define SUCCESS 0
#define ERROR  -1

int main() {
    pid_t p;   // To store the PID of the created child process

    printf("Parent: I am going to call fork() to create a child process.\n");
    p = fork();

    if(p == ERROR) {
        printf("There was an error while calling fork()\n");
        return ERROR;
    }
    
    if(p == 0) { // fork() returns zero to the child process
        printf("Child: My parent id is %d\n", (int)getppid());            
        printf("Child: My pid is %d\n", (int)getpid());
        while(1);
    }
    else { // fork returns the PID of the child process created to the Parent 
        printf("Parent: My parent id is %d\n", (int)getppid()); 
        printf("Parent: My pid is %d\n", (int)getpid());         
        printf("Parent: PID of my child is %d\n", (int) p);              
        while(1);
    }
    
    // Control never comes here because of both parent
    // and the child processes run forever
    
    return SUCCESS;
}
