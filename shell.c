#include "simple_shell.h"

/**
 * main - prints the prompt, handles EOF, reads file_stream
 * @argc: argument count (not necessary)
 * @argv: argv for the command
 * Return: Always returns 0.
 */

int main(int argc, char *argv[])
{
	char *user_input = NULL;
	size_t size_of_buffer = 0;
	ssize_t stream_status = 0;
	char *name_of_program = argv[0];

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "simple_shell$ ", 14);
		stream_status = getline(&user_input, &size_of_buffer, stdin);
		if (stream_status == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}

		if (user_input[stream_status - 1] == '\n')
			user_input[stream_status - 1] = '\0';
		if (*user_input == '\0')
			continue;
		if (read_command(user_input, stream_status, name_of_program) == 2)
		{
			free(user_input);
			exit(EXIT_SUCCESS);
		}
	}
	free(user_input);
	user_input = NULL;
	return (0);
}

/**
 * read_command - handles the command line and tokenizes it
 * @input: string
 * @stream_status: getline input
 * @name_of_program: program name
 * Return: 0
 */
int read_command(char *input, size_t __attribute__((unused)) stream_status,
		char *name_of_program)
{
	char *token = NULL;
	char *cmd_arr[100];
	int index_i;

	if (input == NULL)
		return (0);

	if (strcmp(input, "exit") == 0)
		return (2);

	if (strcmp(input, "env") == 0)
		print_env();

	token = strtok(input, " "), index_i = 0;
	while (token)
	{
		cmd_arr[index_i++] = token;
		token = strtok(NULL, " ");
	}
	if (index_i == 0)
		return (0);

	cmd_arr[index_i] = NULL;
	return (call_command(cmd_arr, name_of_program));
}

/**
 * print_not_found - prints when the command is not found in the PATH
 * @cmd: a string provided by stdin
 * @name_of_program: program name
 */
void print_not_found(char *cmd, char *name_of_program)
{
	fprintf(stderr, "%s: %s: command not found\n", name_of_program, cmd);
}

/**
 * call_command - calls the command, forks, execve
 * @cmd_arr: a string provided by stdin
 * @name_of_program: program name
 * Return: 0
 */
int call_command(char *cmd_arr[], char *name_of_program)
{
	char *cmd = cmd_arr[0];
	struct stat st;
	char *exe_path_str = NULL;
	int result;

	if (cmd == NULL)
		return (0);

	if (cmd[0] == '/' || strncmp(cmd, "./", 2) == 0)
	{
		if (stat(cmd, &st) == 0)
		{
			result = execute_command(cmd_arr, name_of_program);
			return (result);
		}
		else
		{
			print_not_found(cmd, name_of_program);
			return (3);
		}
	}

	exe_path_str = search_path(cmd);
	if (exe_path_str == NULL)
	{
		print_not_found(cmd, name_of_program);
		return (3);
	}

	cmd_arr[0] = exe_path_str;
	result = execute_command(cmd_arr, name_of_program);
	free(exe_path_str);
	return (result);
}

/**
 * execute_command - executes the command
 * @cmd_arr: a string provided by stdin
 * @name_of_program: program name
 * Return: 0
 */
int execute_command(char *cmd_arr[], char *name_of_program)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Error:");
		return (-1);
	}
	if (child_pid > 0)
	{
		wait(&status);
	}
	else if (child_pid == 0)
	{
		execve(cmd_arr[0], cmd_arr, environ);
		perror(name_of_program);
		exit(1);
	}
	return (0);
}
