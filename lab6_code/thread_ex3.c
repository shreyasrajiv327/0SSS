#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Building the executable with the command: gcc -o threadEx3 -D_REENTRANT thread_ex3.c -lpthread
// Run ps -all to know the PID of prob1, then use that PID in the below command to know

// PIDs of threads. In Linux, same PCB entry is used for holding information about threads too
// Use ps -T -p PID to view thread id: here PID is of parent who created the thread
// SPID alias lwp (light weight process) alias tid (thread id) gives the unique ID of the thread

typedef struct ThreadArgs
{
    int intValue;
    float floatValue;
    char message[50];
} ThreadArgs;

void *thread_function1(void *arg);
void *thread_function2(void *arg);
void *thread_function3(void *arg);

static int procData = 100;

int main()
{

    int stat;
    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;

    int localData = 0;

    printf("PID of the main process is %d\n", getpid());
    printf("Going to use pthread_create() POSIX call.\n");

    ThreadArgs args1 = {42, 3.14, "1. Introduction to threads !!!"};
    stat = pthread_create(&thread_id1, NULL, thread_function1, (void*)&args1);

    if (stat != 0)
    { // Thread creation failure
        perror("Error: Thread 1 creation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Main: Thread 1 created successfully\n");

    ThreadArgs args2 = {39, 3.75, "2. Introduction to threads !!!"};
    stat = pthread_create(&thread_id2, NULL, thread_function2, (void*)&args2);

    if (stat != 0)
    { // Thread creation failure
        perror("Error: Thread 2 creation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Main: Thread 2 created successfully\n");

    ThreadArgs args3 = {40, 3.39, "3. Introduction to threads !!!"};
    stat = pthread_create(&thread_id3, NULL, thread_function3, (void*)&args3);

    if (stat != 0)
    { // Thread creation failure
        perror("Error: Thread 3 creation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Main: Thread 3 created successfully\n");

    while (1)
    {
        sleep(1);
        printf("Main: My PID %d\n", (int)getpid());
        printf("Main: My procData = %d and localData = %d\n", procData, localData);
        procData++;
        localData++;
    }

    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg)
{
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    int localData = 1000;

    printf("Inside thread: Argument passed to it was %s\n", threadArgs->message);
    printf("Received int value: %d\n", threadArgs->intValue);
    printf("Received float value: %f\n", threadArgs->floatValue);
    printf("PID of the thread is %d\n", getpid());

    sleep(1);
    while (1)
    {
        sleep(1);
        printf("Thread: My PID %d\n", (int)getpid());
        printf("Thread: My procData = %d and localData = %d\n", procData, localData);
        procData++;
        localData++;
    }
}

void *thread_function2(void *arg)
{
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    int localData = 2000;

    printf("Inside thread: Argument passed to it was %s\n", threadArgs->message);
    printf("Received int value: %d\n", threadArgs->intValue);
    printf("Received float value: %f\n", threadArgs->floatValue);
    printf("PID of the thread is %d\n", getpid());

    sleep(1);
    while (1)
    {
        sleep(1);
        printf("Thread: My PID %d\n", (int)getpid());
        printf("Thread: My procData = %d and localData = %d\n", procData, localData);
        procData++;
        localData++;
    }
}

void *thread_function3(void *arg)
{
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    int localData = 3000;

    printf("Inside thread: Argument passed to it was %s\n", threadArgs->message);
    printf("Received int value: %d\n", threadArgs->intValue);
    printf("Received float value: %f\n", threadArgs->floatValue);
    printf("PID of the thread is %d\n", getpid());

    sleep(1);
    while (1)
    {
        sleep(1);
        printf("Thread: My PID %d\n", (int)getpid());
        printf("Thread: My procData = %d and localData = %d\n", procData, localData);
        procData++;
        localData++;
    }
}
