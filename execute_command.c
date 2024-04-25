#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(char *full_path, char *buffer) {
    pid_t child = fork();

    if (child == -1) 
    {
        perror("fork");
    } 
    else if (child == 0) 
    {
        char *args[2];
        args[0] = buffer;
        args[1] = NULL;
        execve(full_path, args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    } 
    else 
    {
        wait(NULL);
    }
}
