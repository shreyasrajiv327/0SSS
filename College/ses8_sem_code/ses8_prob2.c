#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define THREAD_COUNT 4
#define MAX_VALUE 0xFF

int counter = 0;
sem_t *bin_sems[THREAD_COUNT];

void *thread_function(void *thread_name);

int main() {
    pthread_t threads[THREAD_COUNT];

    // Create named binary semaphores
    for (int i = 0; i < THREAD_COUNT; ++i) {
        char sem_name[20];
        sprintf(sem_name, "/bin_sem%d", i);
        bin_sems[i] = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR, 1);

        if (bin_sems[i] == SEM_FAILED) {
            perror("Semaphore creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Print semaphore names for verification
    for (int i = 0; i < THREAD_COUNT; ++i) {
        char sem_name[20];
        sprintf(sem_name, "/bin_sem%d", i);
        printf("Semaphore name %d: %s\n", i, sem_name);
    }

    // Create threads
    for (int i = 0; i < THREAD_COUNT; ++i) {
        char thread_name[20];
        sprintf(thread_name, "Thread%d", i);

        if (pthread_create(&threads[i], NULL, thread_function, (void *)thread_name) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Main thread prints the value of the counter every one second
    while (1) {
        sleep(1);
        printf("Main: counter = 0x%08X\n", counter);
    }

    // Clean up threads and named semaphores
    for (int i = 0; i < THREAD_COUNT; ++i) {
        sem_close(bin_sems[i]);
        char sem_name[20];
        sprintf(sem_name, "/bin_sem%d", i);
        sem_unlink(sem_name);  // Use the semaphore name, not bin_sems[i]
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void *thread_function(void *thread_name) {
    int thread_index = atoi(&((char *)thread_name)[6]);

    while (1) {
        // Acquire binary semaphore
        sem_wait(bin_sems[thread_index]);

        // Increment the relevant byte of the counter based on the thread index
        counter += (1 << (thread_index * 8));
        if ((counter & 0xFF) == 0) counter = 0;  // Reset to 0 when reaching 0xFF

        // Release binary semaphore
        sem_post(bin_sems[thread_index]);

        // Sleep for one second
        sleep(1);
    }

    // The function won't reach here
    return NULL;
}

