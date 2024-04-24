#include "shell.h"

void handle_builtin(char *command) {
    if (strcmp(command, "cd") == 0) {

        char *directory = strtok(NULL, " ");

        if (directory == NULL) 
        {
            fprintf(stderr, "cd: No such file or directory\n");
            return;
        }


        if (chdir(directory) != 0) {
            perror("cd");
        }
    } else if (strcmp(command, "exit") == 0) {

        exit(EXIT_SUCCESS);
    }
}

void token_handler(char *buffer, char *delim) {
    char *token = strtok(buffer, delim);
    while (token != NULL) {
        if (strcmp(token, "") != 0) {
            handle_builtin(token);
        }
        token = strtok(NULL, delim);
    }
}