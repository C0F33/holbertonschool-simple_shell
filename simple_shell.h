#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int is_terminal_input(void);
void print_prompt(void);
ssize_t read_input_line(char **lineptr, size_t *n);
void write_newline(void);
int process_command(char *input_line, char *program_name);
int is_exit_command(char *input_line);
int is_env_command(char *input_line);
int print_environment_variables(void);
char *tokenize_command(char *input_line, int *token_count);
int is_path_command(char *command);
int is_relative_command(char *command);
int is_path_unset(void);
int execute_command_array(char *command_array[], char *program_name);
void print_command_not_found_error(char *command, char *program_name);
char *find_executable_path(char *command);
void print_fork_error(char *program_name);
void print_exec_error(char *program_name);
int execute_command(char *command_array[], char *program_name);

#endif /* SIMPLE_SHELL_H */
