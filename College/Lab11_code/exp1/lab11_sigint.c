#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "mytypes.h"

// SIGINT is a signal from keyboard, its handler is defined here

// This variable is defined in the lab11_exp1.c
extern SIGHANDLER pDefaultHandler;

extern int sigCount;

void sigint_handler(int sig){

  //Note: It is always preferable not to print inside a signal handlers
  printf("Caught the signal %d and sigCount = %d\n", sig, sigCount);  
 
  sigCount++;
  
  if(sigCount >= 3) {
    // Reinstall the previous default signal handler back
    // This allows the OS to handle the signal and terminate the process
    signal(sig, pDefaultHandler);
  }
  
} // end of sigint_handler()
