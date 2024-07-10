#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "mytypes.h"

// gcc -o exp2 lab11_exp2.c
// The ./child is the executable name, created from the file lab11_child.c

char * child_argv[] = {"./child", 0};
//char * xterm_argv[] = {"xterm",  "-T title", "-e /usr/bin/cb_console_runner child", 0};

void main() { 
    int pid; 
  
    /* Create a child process */
    if ((pid = fork()) < 0) { 
        perror("fork"); 
        exit(1); 
    } 
  
    if (pid == 0) { /* child */
    
        execv("./child", child_argv);    
        printf("Child: This is never printed\n");
    } 
  
    else /* parent */
    { /* pid has the child's pid */
        printf("\nParent: Sending SIGHUP to the child %d\n\n", pid);
        sleep(2); // This is required for the child to get a chance to run
        kill(pid, SIGHUP); // Not killing only sending a signal using kill()
  
        sleep(3); /* pause for 3 secs */
        
        printf("\nParent: Sending SIGINT to the child\n\n"); 
        kill(pid, SIGINT); 
  
        sleep(3); /* pause for 3 secs */
        
        printf("\nParent: Sending SIGQUIT to the child\n\n"); 
        kill(pid, SIGQUIT); 
        
        sleep(3); 
        exit (0);  // Parent ends here
    } 
    
} // end of main()
  

