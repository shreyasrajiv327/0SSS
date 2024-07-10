#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h> // Include for GCD

#define MAX_COUNT 10

dispatch_semaphore_t bin_sem1, bin_sem2;

void *thread1_function(void *arg);
void *thread2_function(void *arg);

int main() {
    pthread_t thread1, thread2;
    
    // Initialize semaphores
    bin_sem1 = dispatch_semaphore_create(1);
    bin_sem2 = dispatch_semaphore_create(0);

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Cleanup semaphores
    dispatch_release(bin_sem1);
    dispatch_release(bin_sem2);

    return 0;
}

void *thread1_function(void *arg) {
    for (int i = 0; i < MAX_COUNT; ++i) {
        dispatch_semaphore_wait(bin_sem1, DISPATCH_TIME_FOREVER);
        
        putchar('1');
        fflush(stdout);

        dispatch_semaphore_signal(bin_sem2);
    }

    pthread_exit(NULL);
}

void *thread2_function(void *arg) {
    for (int i = 0; i < MAX_COUNT; ++i) {
        dispatch_semaphore_wait(bin_sem2, DISPATCH_TIME_FOREVER);
        
        putchar('2');
        fflush(stdout);

        dispatch_semaphore_signal(bin_sem1);
    }

    pthread_exit(NULL);
}
