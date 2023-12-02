#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *env_var;
void print_env_val(char *env_var, char *envp[]);

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 2) {
        printf("Usage: %s <environment variable names>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        env_var = argv[i];
        printf("\nLab2: Printing the content of the env var %s", env_var);
        print_env_val(env_var, envp);
    }

    return 0;
}

void print_env_val(char *env_var, char *envp[]) {
    int i = 0;
    while (envp[i] != NULL) {
        if (strncmp(envp[i], env_var, strlen(env_var)) == 0 && (envp[i][strlen(env_var)] == '=')) {
            printf("\n%s", envp[i] + strlen(env_var) + 1); 
            return;
        }
        i++;
    }
    printf("\n%s not found", env_var);
}
