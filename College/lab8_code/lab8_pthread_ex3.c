#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Building the executable with the command: gcc -o threadEx2 -D_REENTRANT lab8_pthread_ex2.c -lpthread

typedef struct ThreadArgs
{
    char name[20];
    char branchName[20];
    char USN[20];
    char message[50];
} ThreadArgs;

void *thread_function(void *arg);

char message1[] = "1. Introduction to threads !!!";

static int procData = 100;

int main()
{

	int stat;
	pthread_t thread_id1;

	int localData = 0;

	printf("PID of the main process is %d\n", getpid());
	printf("Going to use pthread_create() POSIX call.\n");

    ThreadArgs args1 = {"Reethu Thota", "B.Tech CSE","1RVU22CSE128", "1. Introduction to threads !!!"};
	stat = pthread_create(&thread_id1, NULL, thread_function, (void *)&args1);

	if (stat != 0)
	{ // thread creation failure
		perror("Error: Thread 1 creation failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Main: Thread 1 created successfully\n");
	while (1)
	{
		sleep(10);
		printf("Main: My PID %d\n", (int)getpid());
		printf("Main: My procData = %d and localData = %d\n", procData, localData);
		procData++;
		localData++;
	}
	exit(EXIT_SUCCESS);

} // end of main()

void *thread_function(void *arg)
{
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    int localData = 1000;

    printf("Inside thread: Argument passed to it was %s\n", threadArgs->message);

    sleep(5);
    while (1)
    {
        sleep(5);
        printf("Thread: Received Name: %s\n", threadArgs->name);
        printf("Thread: Received Brach Name: %s\n", threadArgs->branchName);
        printf("Thread: Received USN: %s\n", threadArgs->USN);
        printf("Thread: My PID %d\n", (int)getpid());
        printf("Thread: My procData = %d and localData = %d\n", procData, localData);
        procData++;
        localData++;
    }
}
