#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
#define MAX_INPUT_SIZE 1024
#define MAX_CMD_SIZE 1024
#define DELIM " \t\r\n\a"
#define PROMPT "simple_shell "

void print_env(void);
int str_cmp(char *string1, const char *string2, int num_chars);
char *_getenv(const char *env_var);
int main(int argc, char *argv[]);
int read_command(char *input, size_t __attribute__((unused)) file_stream, char *program_name);
void print_not_found(char *cmd, char *program_name);
int call_command(char *cmd_arr[], char *program_name);
int execute_command(char *cmd_arr[], char *program_name);
char *search_path(char *command);

#endif /* SIMPLE_SHELL_H */