#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Building the executable with the command: 
// gcc -o exp0 -D_REENTRANT lab7_exit_exp0.c -lpthread 
// Run ps -all to know the PID of exp0, then use that 
// PID in the below command to know PIDs of threads. 
// In Linux, same PCB structure is used for 
// holding information about threads too.

// Use ps -T -p PID to view thread ids: here 
// PID is of parent who created the threads
// SPID alias lwp (light weight process) alias tid (thread id) 
// gives the unique ID of each thread

// Create the exp0.asm file to analyze what happens underneath
// gcc -o exp0.asm -c -S lab7_exit_exp0.c -lpthread -D_REENTRANT


void *thread1_fn(void *arg);

// This buffer is over written by both the Threads 1 and 2
char msg[] = "Hello, OS_SS Lab7 class ... lab7_exit_exp0";

int main(){

  int stat;
  pthread_t thread_id1;
  void *thread1_result;


  printf("Main: %s\n", msg);  
  printf("Main: PID of the main process is %d\n", getpid());
  
  // No param passed to the thread
  stat = pthread_create(&thread_id1, NULL, thread1_fn, NULL);
  
  if(stat != 0){ //thread creation failure
    perror("Main: Error: Thread 1 creation failed\n");
    exit(EXIT_FAILURE);
  }
  
  printf("Main: Thread 1 created successfully\n");
  printf("Main: I am going to sleep for 10 seconds ...\n");
  printf("Main: Allowing my Thread 1 to run for a while.\n");
  sleep(10);
  
  // Step0: When no return or exit is given in the main() function, what happens?
  
  // Either keep or comment off all the below three printf() messages together
  printf("Main: No return or exit from the main after this msg ...\n");
  printf("Main: I am going to terminate without calling pthread_exit()\n");
  printf("Main: If I terminate this way, all my child threads will be killed\n");
  
  // Step1: Now, comment off the above three messages and 
  // uncomment the below two instructions
  
  // Give ps -T -p <PID of main> ... 
  // then give Control+C on the terminal and observe through another terminal 
  // printf("Main: I am going to run forever\n");
  // while(1);   

  // Step2: Now, comment off the above two instructions and 
  // uncomment the below two instructions
  
  // When the parent exits through exit() call, the child thread also gets killed
  //printf("Main: I am going to call exit(), observe what happens to my thread\n");
  //exit(EXIT_SUCCESS);

  // Step3: Now, comment off the above two instructions and 
  // uncomment below two instructions
  
  // Observe whether the threads are alive with ps -T -p PID of this parent process
  // With pthread_exit() the parent process is kept it in Zombie state (Stat Z) 
  // and the child threads continue to run until they exit themselves or get killed
  
  // Give Control+C and observe that the child and parent process get killed 
  // You can also use the command: kill -9 <PID of the parent process>
  printf("Main: I am going to call pthread_exit(), now, observe what happens to my thread\n");
  pthread_exit(EXIT_SUCCESS);
  
} // end of main()


void * thread1_fn(void *arg){
  int cnt = 1;

  printf("Thread1: I am created.\n");
  printf("Thread1: I am going to sleep for 2 seconds now...\n");
  sleep(2);
  
  printf("Thread1: I plan to run forever\n");
  while(1) {
    sleep(2);
    printf("Thread1: %d: I am still alive\n", cnt);
    cnt++;
  }
  
} // end of thread1_function()



