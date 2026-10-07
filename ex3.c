#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main() {
    char line[MAX_LINE];
    char *args[2];

    while (1) {
        printf("myshell> ");

        if (fgets(line, MAX_LINE, stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) continue;

        if (strcmp(line, "exit") == 0) break;

        args[0] = line;
        args[1] = NULL;

        pid_t pid = fork();

        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
            }
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}