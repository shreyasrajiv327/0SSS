#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // sleep() is declared here
#include <pthread.h>
#include <semaphore.h>

#define THREAD1 1
#define THREAD2 2

#define MAX_COUNT 10   

// Command line options to build the executable using this source file is below:
// gcc -D_REENTRANT -o withsem ses8_withSem.c -lpthread

// Ref: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_join.html
// Signature of pthread_join() is given below
// If successful, the pthread_join() returns zero; otherwise, 
// an error number shall be returned to indicate the error.
int pthread_join(pthread_t thread, void **status_ptr);

void *thread1_function(void *);
void *thread2_function(void *);

// Global process varaible accessible to all the threads of this process 
// Value here decides the process which is allowed to change variable Counter value.
// Thread 1 is allowed to run initially. run_now is a control variable.
int  run_now = THREAD1; 

int counter = 0; // Global counter incremented by both threads, a shared variable
sem_t bin_sem1, bin_sem2;

int main()
{
   int res1, res2, res_sem;
   char *t1_stat, *t2_stat;
   pthread_t thread1, thread2;

  // Initialize semaphore
  // Pointer to Semaphore handle, pshared = 0, value = 0 (not free or busy)  
  res_sem = sem_init(&bin_sem1, 0, 0);  
  
  if(res_sem != 0) {
    printf("Semaphore1 creation failure: %d\n", res_sem);
    exit(1);
  }  

  // Pointer to Semaphore handle, pshared = 0, value = 0 (not free or busy) 
  res_sem = sem_init(&bin_sem2, 0, 0);  
  
  if(res_sem != 0) {
    printf("Semaphore2 creation failure: %d\n", res_sem);
    exit(1);
  }  
    
   /* Create independent threads each of which will execute different threead functions */

   if( (res1 = pthread_create( &thread1, NULL, &thread1_function, "Thread1")) )  {
      printf("Thread1 creation failed: %d\n", res1);
      exit(1);
   }

   if( (res2 = pthread_create( &thread2, NULL, &thread2_function, "Thread2")) )  {
      printf("Thread2 creation failed: %d\n", res2);
      exit(1);
   }

  sleep(1); // To allow threads created get a chance to run
  
  // Parent process or main thread waits till both the threads complete their execution.
  // If the main thread continues without waiting for its threads to terminate, 
  // and exits or terminates it will cause all its child threads to be tereminated 
  // forceibly before they exit themselves.

  pthread_join( thread1, (void**) &t1_stat);
  printf("\nThread1 status: %s\n", t1_stat);  
  
  pthread_join( thread2, (void**) &t2_stat); 
  printf("Thread2 status: %s\n", t2_stat);

  printf("Main: counter = %d\n", counter);

  exit(0);
}

void *thread1_function(void *pThreadName) {

  printf("%s is entered\n", (char *) pThreadName);
  
  while(counter < MAX_COUNT){
    if(run_now != THREAD1) 
      sem_wait(&bin_sem1);  // Thread1 gets blocked if bin_sem1 is not free

  	if(counter >= MAX_COUNT)
  		break;

    sem_init(&bin_sem1, 0, 0); // make bin_sem1 not free      
    putchar('1');
    counter++;
    run_now = THREAD2;
    sem_post(&bin_sem2);
  } // end of while()

  pthread_exit("Thread1 is exiting");
} // end of thread1_function()

void *thread2_function(void *pThreadName){

  printf("%s is entered\n", (char *) pThreadName);

  while(counter < MAX_COUNT){
    if(run_now != THREAD2)
      sem_wait(&bin_sem2);  // Thread2 gets blocked if bin_sem2 is not free

  	if(counter >= MAX_COUNT)
  		break;
        
    sem_init(&bin_sem2, 0, 0); // make bin_sem2 not free
    putchar('2');
    counter++;
    run_now = THREAD1;
    sem_post(&bin_sem1);
  } // end of while()
    
  pthread_exit("Thread2 is exiting");
} // end of thread2_function()
