#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "mytypes.h"

// gcc -o child lab11_child.c

// C program to implement handler for SIGHUP, SIGINT and  SIGQUIT signals

// Prototypes of signal handlers .. function declarations
void sighup_handler(int signum); 
void sigint_handler(int signum); 
void sigquit_handler(int signum); 

SIGHANDLER pDefaultSighup;

void main() { 
    
    pDefaultSighup = signal(SIGHUP, sighup_handler); 
    signal(SIGINT, sigint_handler); 
    signal(SIGQUIT, sigquit_handler); 

    while(1);  /* loop for ever */
       
} // end of main()
  

void sighup_handler(int signum) 
{ 
    signal(SIGHUP, pDefaultSighup); /* set it back to default signal handler */
    printf("Child %d: I have received a SIGHUP %d\n", getpid(), signum); 
} 
  

void sigint_handler(int signum) 
  
{ 
    printf("Child %d: I have received a SIGINT %d!!!\n", getpid(), signum); 
} 
  

void sigquit_handler(int signum) 
{ 
    printf("Child %d: I received SIGQUIT from my parent %d!!!\n",getpid(), signum); 
    printf("Child %d: I am exiting now!!!\n", getpid());
    exit(0); 
} 
