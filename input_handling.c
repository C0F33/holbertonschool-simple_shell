#include "shell.h"


void token_handler(char *buffer, char *delim)
{
	char *token;

	token = strtok(buffer, delim);

	if (token != NULL)
		handle_builtin(token);

}


void handle_builtin(char *command)
{
	if (strcmp(command, "cd") == 0)
	{
		char *directory = strtok(NULL, " ");
		if (directory == NULL)
		{
			directory = getenv("HOME");
			if (directory == NULL)
			{
				fprintf(stderr, "cd: HOME environment variable not set\n");
				return;
			}
		}

		if (chdir(directory) != 0)
		{
			perror("cd");
		}
	}
		else if (strcmp(command, "exit") == 0)
				{
		exit(EXIT_SUCCESS);
	}
		else
		{

		int ret = system(command);
		if (ret == -1)
		{
			perror("system");
		}
		else if (ret != 0)
		{
			fprintf(stderr, "Shell: Command failed with exit status %d\n", ret);
		}
	}
}

void execute_command(char *full_path, char *buffer)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
		else if (pid == 0)
		{
		char *args[MAX_ARGS];
		int argc = 0;
		char *token = strtok(buffer, " ");
		while (token != NULL && argc < MAX_ARGS - 1)
		{
			args[argc++] = token;
			token = strtok(NULL, " ");
		}
		args[argc] = NULL;
		execve(full_path, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}


int process_handler(char *buffer)
{
	char full_path[PATH_MAX];

	if (buffer == NULL)
	{
		fprintf(stderr, "Shell: Null buffer\n");
		return (-1);
	}

	if (strcmp(buffer, "cd") == 0)
	{
		char *arg = strtok(NULL, " ");
		if (arg == NULL)
		{
			char *home_directory = getenv("HOME");
			if (home_directory == NULL)

			{
				fprintf(stderr, "cd: HOME environment variable not set\n");
				return (-1);
			}
			if (chdir(home_directory) == -1)
			{
				perror("chdir");
				return (-1);
			}
			return (0);
		}
			else
			{
			if (chdir(arg) == -1)
			{
				perror("chdir");
				return (-1);
			}
			return (0);
		}
	}

	if (access(buffer, X_OK) == 0)
	{
		snprintf(full_path, PATH_MAX, "%s", buffer);
	}
	else
		{
		char *bin_path = "/bin/";
		snprintf(full_path, PATH_MAX, "%s%s", bin_path, buffer);

		if (access(full_path, X_OK) != 0)
		{
			printf("Shell: Command not found: %s\n", buffer);
			return (-1);
		}
	}

	execute_command(full_path, buffer);

	return (0);
}
