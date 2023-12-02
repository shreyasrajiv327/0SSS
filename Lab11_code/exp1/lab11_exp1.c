#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "mytypes.h"

// gcc -o exp1 lab11_exp1.c lab11_sigint.c
// File lab12_sigint.c defines the signal handlder for SIGINT (Control+C)

// Prototype of the function sigint_handler() that handles SIGINT signal
void sigint_handler(int sig);

// SIGINT interrupt signal  isent to a  process when Ctrl+C is pressed
SIGHANDLER pSigintHandler;
// SIGINT already has a default handler installed by the OS
SIGHANDLER pDefaultHandler;

int sigCount;

int main(){
  
  // Install our own signal handler for SIGINT with sigint_handler
  // copy the earlier pointer to the signal installed into sigintDefault
  pSigintHandler = sigint_handler;
  
  // 1. Set it with my handler
  //pDefaultHandler = signal(SIGINT, pSigintHandler);

  // 2. Set it to ignore the Control+C signal, now you can stop it with Control+Z
  // Restart it with fg command. You can find the PID with ps -all and 
  // use kill -9 pid to kill this process because Control+C is ignored by it
  // pDefaultHandler = signal(SIGINT, SIG_IGN);

  // 3. Set it to the default handler associated with the SIGINT signal
  // The default action is to kill the process when Control+C is given
  // If you start this process in background ./exp1 & then you can kill it
  // by bringing it to foreground with fg and then with Control+C
  // pDefaultHandler = signal(SIGINT, SIG_DFL);  
  
  printf("Going to execute while(1) ...\n");

  while(1){
    printf("I am sleeping for 2 seconds...\n");
    sleep(2);
  }
  
  return 0; // Never reached.
  
} // end of main()
