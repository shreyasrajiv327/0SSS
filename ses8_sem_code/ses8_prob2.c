#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // sleep() is declared here
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define THREAD1 1
#define THREAD2 2
#define THREAD3 3
#define THREAD4 4


// Command line options to build the executable using this source file is below:
// gcc -D_REENTRANT -o hw2 ses8_prob2.c -lpthread

// Ref: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_join.html
// Signature of pthread_join() is given below
// If successful, the pthread_join() returns zero; otherwise, 
// an error number shall be returned to indicate the error.
int pthread_join(pthread_t thread, void **status_ptr);

void *thread_function(void *);

// Lab 10: Homework 2: Implement Critical Section (CS) that is changed by four threads
// simultaneously. Each thread modifying the global variable counter as given below.

// The counter, global process varaible is accessible to all the four threads of this process 
// Each thread needs to acquire the binary simaphore (bin_sem) before incrementing its own byte
// Four threads each changing the relevant byte of the 32 bit value in counter
// counter (lower 32-bits) = byte3 Byte2 Byte1 Byte0
// Thread0: byte0 (bits 0 to 7), Thread1: byte1 (bits 8 to 15) and so on ...


int counter = 0; // Global counter incremented by all four threads, a shared variable
sem_t bin_sem;

int main()
{
   int res, res_sem;
   char *t0_stat, *t1_stat, *t2_stat, *t3_stat;
   pthread_t thread0, thread1, thread2, thread3;

  // Initialize semaphore
  // Pointer to Semaphore handle, pshared = 0, value = 1 (free)  
  res_sem = sem_init(&bin_sem, 0, 1); 
  
  if(res_sem != 0) {
    printf("Semaphore1 creation failure: %d\n", res_sem);
    exit(1);
  }  

    
   /* Create four independent threads all of them will execute the same threead function */
   if( (res = pthread_create( &thread0, NULL, &thread_function, "Thread0")) )  {
      printf("Thread0 creation failed: %d\n", res);
      exit(1);
   }

   if( (res = pthread_create( &thread1, NULL, &thread_function, "Thread1")) )  {
      printf("Thread1 creation failed: %d\n", res);
      exit(1);
   }

   if( (res = pthread_create( &thread2, NULL, &thread_function, "Thread2")) )  {
      printf("Thread2 creation failed: %d\n", res);
      exit(1);
   }

   if( (res = pthread_create( &thread3, NULL, &thread_function, "Thread3")) )  {
      printf("Thread3 creation failed: %d\n", res);
      exit(1);
   }

  sleep(1); // To allow all the threads created, get a chance to run
  
  // Parent process or main thread waits till both the threads complete their execution.
  // If the main thread continues without waiting for its threads to terminate, 
  // and exits or terminates it will cause all its child threads to be tereminated 
  // forceibly before they exit themselves.

  while(1){
  printf("Main: counter = 0x%X\n", counter);
  sleep(1);
 }
 
  exit(0);   // Control never reaches here
}

void *thread_function(void *pThreadName)
{
  int ret;
  unsigned int val;
  
  printf("%s is entered\n", (char *) pThreadName);
  
  while(1){
	sem_wait(&bin_sem);

	if(strcmp(pThreadName, "Thread0") == 0){
		//printf("0");
		val = counter & 0x000000FF;
		val++;
		if(val >= 0x100)
			val = 0;
			
		counter = (counter & 0xFFFFFF00) | val;
	}
	else if(strcmp(pThreadName, "Thread1") == 0){
		//printf("1");	
		val = counter & 0x0000FF00;
		val >>= 8;
		val++;
		if(val >= 0x100)
			val = 0;
		
		val <<= 8;
		counter = (counter & 0xFFFF00FF) | val;
	}
	else if(strcmp(pThreadName, "Thread2") == 0){
		//printf("2");	
		val = counter & 0x00FF0000;
		val >>= 16;
		val++;
		if(val >= 0x100)
			val = 0;
		
		val <<= 16;
		counter = (counter & 0xFF00FFFF) | val;
	}
	else if(strcmp(pThreadName, "Thread3") == 0){
		//printf("3");	
		val = counter & 0xFF000000;
		val >>= 24;
		val++;
		if(val >= 0x100)
			val = 0;
		
		val <<= 24;
		counter = (counter & 0x00FFFFFF) | val;
	}

	sem_post(&bin_sem);
	sleep(1);
  } // end of while(1)

} // end of thread_function()


