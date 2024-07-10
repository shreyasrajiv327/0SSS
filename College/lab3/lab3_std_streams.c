
#include <stdio.h>
#include <stdlib.h>

// build this file with the below command on WSL
// gcc -o std_streams lab3_std_streams.c
// Invoke it by feeding this source file as input
// This program reads it and prints out on the stdout
// invoke the executable using the below command sequence
// ./std_streams < lab3_std_streams.c 
// When you invoke the executable as shown above, it prints the
// contents of this file on the screen
// You can redirect the stderr stream to another file as shown below
// ./std_streams < lab3_std_streams.c 2> error.txt
// look at the content of error.txt using the command
// cat error.txt

int main(void)
{
  // Give the below command to read the manual of getline() function
  // man getline 
  // signature of getline() is:
  // ssize_t getline(char **lineptr, size_t *len, FILE *stream);

  int nread = 0; // number of chars read using getline()
  char *lineBuf; // buffer for holding the null terminated line read
  ssize_t len = 0;
  
  //use malloc to create space for the line being read
  lineBuf = (char *) malloc(256); 
  if (lineBuf == NULL){ // if malloc fails, exit the program
     fprintf(stderr, "Error: malloc() returned NULL\n");
     return -1;
  }

  // Both the below contents come out through stdout stream
  printf ("Lab3: Demo of standard streams ...\n");
  fprintf(stdout, "Printing a message using stdout ...\n");

  // Read the input coming in through stdin using getline()
  // Read the input line by line and print them out
  fprintf(stdout, "Print the contents of the input file\n");
  while((nread = getline(&lineBuf, &len, stdin)) != -1) {
     printf("%s", lineBuf);
  }

  fprintf (stderr, "Hi Im Shreyas.\n");
  
  // Remember to free the dynamic memory allocated
  free(lineBuf);
  return 0;
}