#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD1 1
#define THREAD2 2

#define MAX_COUNT 10   

// Function declarations
void *thread1_function(void *pThreadName);
void *thread2_function(void *pThreadName);

// Global variables
int run_now = THREAD1; 
int counter = 0;
sem_t *bin_sem1, *bin_sem2;
int main()
{
    int res1, res2;
    char *t1_stat, *t2_stat;
    pthread_t thread1, thread2;

    // Initialize semaphores
    bin_sem1 = sem_open("/bin_sem1", O_CREAT, S_IRUSR | S_IWUSR, 0);
    bin_sem2 = sem_open("/bin_sem2", O_CREAT, S_IRUSR | S_IWUSR, 0);

    if (bin_sem1 == SEM_FAILED || bin_sem2 == SEM_FAILED) {
        perror("Semaphore creation failed");
        exit(1);
    }

    /* Create independent threads each of which will execute different thread functions */
    if ((res1 = pthread_create(&thread1, NULL, &thread1_function, "Thread1"))) {
        printf("Thread1 creation failed: %d\n", res1);
        exit(1);
    }

    if ((res2 = pthread_create(&thread2, NULL, &thread2_function, "Thread2"))) {
        printf("Thread2 creation failed: %d\n", res2);
        exit(1);
    }

    sleep(1); // To allow threads created get a chance to run

    // Parent process or main thread waits till both the threads complete their execution.
    // If the main thread continues without waiting for its threads to terminate, 
    // and exits or terminates it will cause all its child threads to be terminated 
    // forcibly before they exit themselves.

    pthread_join(thread1, (void **)&t1_stat);
    printf("\nThread1 status: %s\n", t1_stat);  

    pthread_join(thread2, (void **)&t2_stat);
    printf("Thread2 status: %s\n", t2_stat);

    printf("Main: counter = %d\n", counter);

    // Close and unlink semaphores
    sem_close(bin_sem1);
    sem_close(bin_sem2);
    sem_unlink("/bin_sem1");
    sem_unlink("/bin_sem2");

    exit(0);
}

void *thread1_function(void *pThreadName) {
    printf("%s is entered\n", (char *)pThreadName);

    while (counter < MAX_COUNT) {
        if (run_now != THREAD1)
            sem_wait(bin_sem1); // Thread1 gets blocked if bin_sem1 is not free

        if (counter >= MAX_COUNT)
            break;

        sem_post(bin_sem1); // make bin_sem1 not free      
        putchar('1');
        counter++;
        run_now = THREAD2;
        sem_post(bin_sem2);
    } // end of while()

    pthread_exit("Thread1 is exiting");
} // end of thread1_function()

void *thread2_function(void *pThreadName) {
    printf("%s is entered\n", (char *)pThreadName);

    while (counter < MAX_COUNT) {
        if (run_now != THREAD2)
            sem_wait(bin_sem2); // Thread2 gets blocked if bin_sem2 is not free

        if (counter >= MAX_COUNT)
            break;

        sem_post(bin_sem2); // make bin_sem2 not free
        putchar('2');
        counter++;
        run_now = THREAD1;
        sem_post(bin_sem1);
    } // end of while()

    pthread_exit("Thread2 is exiting");
} // end of thread2_function()
