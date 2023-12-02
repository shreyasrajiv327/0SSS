#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t parent_pid = getpid();
    pid_t child_pid;

    printf("Main parent process (PID: %d) is running.\n", parent_pid);

    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (child_pid == 0) {
        // This code is executed by the first child process
        printf("Child process 1 (PID: %d) is running.\n", getpid());
        sleep(10);
        printf("Child process 1 (PID: %d) woke up.\n", getpid());
        child_pid = fork();

        if (child_pid < 0) {
            fprintf(stderr, "Fork failed in the first child process.\n");
            return 1;
        } else if (child_pid == 0) {
            // This code is executed by the second child process
            printf("Child process 2 (PID: %d) is running.\n", getpid());
            // Add more code here if needed.
            return 0;
        } else {
            // Code for the first child process (parent of the second child)
            // Add more code here if needed.
            wait(NULL);
            printf("Child process 2 has completed.\n");
            return 0;
        }
    } else {
        // Code for the main parent process
        printf("Main parent process is returning.\n");
        return 0;
    }
}
