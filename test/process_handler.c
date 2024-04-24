/*/#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int process_handler(char *buffer) {
    char full_path[PATH_MAX];
    if (buffer == NULL) {
        fprintf(stderr, "Shell: Null buffer\n");
        return -1;
    }

    if (strcmp(buffer, "cd") == 0) {
        char *arg = strtok(NULL, " ");
        if (arg == NULL) {
            fprintf(stderr, "Shell: Expected argument to 'cd' command\n");
            return -1;
        } else {
            if (chdir(arg) == -1) {
                perror("chdir");
                return -1;
            }
            return 0;
        }
    }

    sprintf(full_path, "%s", buffer);

    if (access(full_path, X_OK) == 0) {
        execute_command(full_path, buffer);
    } else {
        char *bin_path = "/bin/";
        snprintf(full_path, PATH_MAX, "%s%s", bin_path, buffer);

        if (access(full_path, X_OK) == 0) {
            execute_command(full_path, buffer);
        } else {
            printf("Shell: Command not found: %s\n", buffer);
        }
    }
    return 0;
}
*/