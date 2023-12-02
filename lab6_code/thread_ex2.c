#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/syscall.h>


// Building the executable with the command: gcc -o threadEx2 -D_REENTRANT thread_ex2.c -lpthread 
// Run ps -all to know the PID of prob1, then use that PID in the below command to know

// PIDs of threads. In Linux, same PCB entry is used for holding information about threads too
// Use ps -T -p PID to view thread id: here PID is of parent who created the thread
// SPID alias lwp (light weight process) alias tid (thread id) gives the unique ID of the thread

void *thread_function(void *arg);

char message[] = "Introduction to threads !!!";

static int procData = 100;

int main(){

	int stat;
	pthread_t thread_id;
	
	int localData = 0;	

	printf("PID of the main process is %d and my PPID %d\n", getpid(), getppid()); 
	
	printf("Going to use pthread_create() POSIX call.\n");

	stat = pthread_create(&thread_id, NULL, thread_function, (void *)message);

	if(stat != 0){ //thread creation failure
	 perror("Error: Thread creation failed\n");
	 exit(EXIT_FAILURE);
	}
  
	printf("Main: Thread created successfully\n");
	while(1){
	 sleep(1);
    	 printf("Main: My PID %d\n", (int) getpid());
    	 printf("Main: My TID %d\n", (int) syscall(SYS_gettid));
    	 printf("Main: My procData = %d and localData = %d\n",  procData, localData); 
	 procData++;
	 localData++;		
	}


	exit(EXIT_SUCCESS);
  
} // end of main()


void * thread_function(void *arg){

	int localData = 1000;	

	printf("Inside thread: Argument passed to it was %s\n", (char *)arg);
	printf("PID of the thread is %d and my PPID %d\n", getpid(), getppid()); 

    sleep(1);
    while(1){
    	sleep(1);
    	printf("Thread: My PID %d\n", (int) getpid());
    	printf("Thread: My TID %d\n", (int) syscall(SYS_gettid));
    	printf("Thread: My procData = %d and localData = %d\n",  procData, localData);
    	procData++;
	localData++;		    	
    }
  
} // end of thread_function()
