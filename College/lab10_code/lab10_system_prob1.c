#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Demonstrating system() system call.
// To build this file: gcc -o prob1 lab10_system_prob1.c
// Run it with any one of the below parameters:
// ./prob1 once
// ./prob1 twice
// But, never invoke problnew with once or twice as parameter 
// after it has been built by this prob1 program.

int main(int argc, char *argv[]){

  printf("Let us try using system() call to execute a command or a program\n");

  system("ls -l");

  printf("Let us try compiling this source code itself\n");

  system("gcc -o prob1new lab10_system_prob1.c");

  printf("Is it possible to call the executable of this program just built?\n");

  // This check is required otherwise it will go into an infinite loop
  // if prob1new is called either with once or twice as parameter
  if( (argc >= 2) && (strcmp(argv[1], "once") == 0 )){
    printf("prob1new is going to be called once.\n");
    system("./prob1new"); // never call prob1new with a parameter "once" 
  }
  else if((argc >= 2) && (strcmp(argv[1], "twice") == 0)){
    printf("prob1new is going to be called twice.\n");
    system("./prob1new"); // never call prob1new with a parameter "twice"
    system("./prob1new"); // never call prob1new with a parameter "twice"
  }

  printf("Going to exit now.\n");
  return 0;

}
