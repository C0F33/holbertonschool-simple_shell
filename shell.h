#ifndef SHELL_H
#define SHELL_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PATH_MAX 4096

typedef enum Bool
{
    false = 1,
    true
} bool;

void token_handler(char *buffer, char *delim);
void handle_builtin(char *command);
int process_handler(char *buffer);
void execute_command(char *full_path, char *buffer);
void print_env(void);
void execute_command(char *full_path, char *buffer);

#endif

