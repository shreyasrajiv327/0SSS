#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Building the executable with the command: 
// gcc -o exp1 -D_REENTRANT lab7_join_exp1.c -lpthread 
// Run ps -all to know the PID of exp1, then use that 
// PID in the below command to know PIDs of threads. 
// In Linux, same PCB structure is used for holding information about threads too
// Use ps -T -p PID to view thread ids: here PID is of parent who created the threads
// SPID alias lwp (light weight process) 
// alias tid (thread id) gives the unique ID of each thread

void *thread1_fn(void *arg);
void *thread2_fn(void *arg);

// This buffer is over written by both the Threads 1 and 2
char msg[] = "Hello, OS_SS Lab7 class ... lab7_join_exp1";

// Messages passed to the threads on its creation
char msg1[] = "Hi Thread1 !!!";
char msg2[] = "Hi Thread2 !!!";

int main(){

  int stat;
  pthread_t thread_id1, thread_id2;
  void *thread1_result;
  void *thread2_result;

  printf("Main: %s\n", msg);  
  printf("Main: PID of the main process is %d\n", getpid());
  
  stat = pthread_create(&thread_id1, NULL, thread1_fn, (void *)msg1);
  
  if(stat != 0){ //thread creation failure
    perror("Main: Error: Thread 1 creation failed\n");
    exit(EXIT_FAILURE);
  }
  
  printf("Main: Thread 1 created successfully\n");

  stat = pthread_create(&thread_id2, NULL, thread2_fn, (void *)msg2);
  
  if(stat != 0){ //thread creation failure
    perror("Main: Error: Thread 2 creation failed\n");
    exit(EXIT_FAILURE);
  }
  
  printf("Main: Thread 2 created successfully\n");
  
  // After trying out main thread waiting on pthread_join() for both thread 1 and 2
  // uncomment the sleep(15) below so that main sleeps longer than threads 1 and 2 
  // even if the main thread is calling the pthread_join() after both the threads have 
  // executed pthread_exit(), this main thread is notified about the exit of threads as well as
  // it gets the messages passed by the threads through their pthread_exit() calls
  printf("Main: I am going to sleep for 5 seconds ...\n");
  sleep(5);
  printf("Main: I woke up after 5 seconds ...\n");
  
  printf("Main: Going to wait for the Thread1 to finish ...\n");
  stat = pthread_join(thread_id1, &thread1_result);
  
  if(stat != 0){ // thread join has failed
    perror("Main: Thread1 join failed\n");
    exit(EXIT_FAILURE);    
  }

  printf("Main: Thread1 joined. It returned: \"%s\"\n", (char*)thread1_result);
  printf("Main: Message after thread 1 writes into it, is \"%s\"\n", msg);
  
  printf("Main: Going to wait for the Thread2 to finish ...\n");
  stat = pthread_join(thread_id2, &thread2_result);
  
  if(stat != 0){ // thread join has failed
    perror("Thread2 join failed\n");
    exit(EXIT_FAILURE);    
  }

  printf("Main: Thread2 joined. It returned: \"%s\"\n", (char*)thread2_result);
  printf("Main: Message after the Thread2 writes into it, is \"%s\"\n", msg);  
  
  printf("Main process is going to execute while(1)\n");
  while(1);  // Forever running
  
} // end of main()


void * thread1_fn(void *arg){

  printf("Thread1: Argument passed to me was \"%s\"\n", (char *)arg);
  printf("Thread1: I am going to sleep now for 5 seconds ...\n");
  sleep(5);
  printf("Thread1: I woke up afer 5 seconds.\n");
  
  // Step0a: Uncomment the three instruction below
  // Step0b: Make Thread1 to sleep longer than Thread2 in the above sleep()
  
  // Comment off the below exit(EXIT_SUCCESS) and see the behaviour
  // printf("Thread1: I am going to call exit() now.\n");
  // printf("Thread1: When I call exit() the entire process and its threads get killed\n");
  //  exit(EXIT_SUCCESS);
  
  // Step1: Comment off above three instructions on both Threads 1 and 2
  
  strcpy(msg, "Thread1: Bye bye ...");  
  printf("Thread1: I am going to call pthread_exit() with a msg to main thread\n");  
  pthread_exit("Thread1: Thank you for the CPU time!!!");
  
} // end of thread1_function()


void * thread2_fn(void *arg){

  printf("Thread2: Argument passed to me was \"%s\"\n", (char *)arg);
  printf("Thread2: I am going to sleep now for 10 seconds ...\n");
  sleep(10);
  printf("Thread2: I woke up afer 10 seconds.\n");
    
  // Step0: Uncomment the three instruction below
  
  // Comment off the below exit(EXIT_SUCCESS) and see the behaviour
  // printf("Thread2: I am going to call exit() now.\n");
  // printf("Thread2: When I call exit() the entire process and its threads get killed\n");
  // exit(EXIT_SUCCESS);
  
  // Step1: Comment off above three instructions on both Threads 1 and 2
  
  strcpy(msg, "Thread2: Bye bye ...");  
  printf("Thread2: I am going to call pthread_exit() with a msg to main thread\n");
  pthread_exit("Thread2: Thank you for the CPU time!!!");  
  
} // end of thread2_function()

