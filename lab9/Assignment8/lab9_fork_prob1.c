#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number between 1 and 9>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 1 || n > 9) {
        fprintf(stderr, "Please provide a number between 1 and 9.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        } else if (child_pid == 0) {
            // This code is executed by the child process
            printf("Child process %d created.\n", i + 1);
            return 0;
        }
    }

    // Code for the parent process
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("All child processes have completed.\n");
    return 0;
}
