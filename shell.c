#include "shell.h"

void execute_command(char *full_path, char *buffer)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
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

