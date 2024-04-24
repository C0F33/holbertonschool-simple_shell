#include "shell.h"

void handle_builtin(char *command) {
    if (strcmp(command, "cd") == 0) {

        char *directory = strtok(NULL, " ");

        if (directory == NULL) {
            fprintf(stderr, "cd: missing directory\n");
            return;
        }


        if (chdir(directory) != 0) {
            perror("cd");
        }
    } else if (strcmp(command, "exit") == 0) {

        exit(EXIT_SUCCESS);
    }
}

void token_handler(char *buffer, char *delim)
{
    char *token;

    token = strtok(buffer, delim);

    if (token != NULL)
        handle_builtin(token);

}