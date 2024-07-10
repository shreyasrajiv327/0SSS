#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t p1, p2;
    
    printf("Parent: I am going to call fork() to create a child process.\n");    
    
    // It creates one child process which runs the same
    // instructions written below after this fork() system call
    p1 = fork();

    // Both the parent and child process going to execute the rest of the code
    
    // Function: pid_t getpid (void) -- returns the PID of the running process
    printf("My PID is %d and my PPID = %d\n", 
            (int)getpid(), (int)getppid());
            
    if(p1 != 0)
    	printf("Parent of p1: My PID = %d and my child PID p1 = %d\n", 
    	        (int)getpid(), (int) p1);

    printf("One more fork() is going to be called now.\n");
    // Function: pid_t getppid (void) -- returns the PID of the parent of the
    // process executing this command
    p2 = fork();

    if(p2 != 0)
    	printf("Parent of p2: My PID = %d and my child PID p2 = %d\n", 
    	        (int)getpid(), (int) p1);

    printf("After the second fork() my PID is %d and my PPID is %d\n", 
            (int)getpid(), (int)getppid());

    while(1);  // All the processes created are going to run forever

    return 0;
}
