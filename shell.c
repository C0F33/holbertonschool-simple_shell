#include "shell.h"

/**
 * main - starting point of the shell where it reads the line
 *
 * Return: 0
 */

int main(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t read;
	char *delim = "  \t\n";
	char *buff_characters;

	int interactive = isatty(STDIN_FILENO);

	if (interactive)
	{
		printf("simpsle_shell$ ");
	}

	while ((read = getline(&buffer, &size, stdin)) != -1)
	{
		if (buffer[read - 1] == '\n')
		{
			buffer[read - 1] = '\0';
		}

		buff_characters = buffer;

		while (*buff_characters == ' ')
		{
			buff_characters++;
		}

		token_handler(buff_characters, delim);
		process_handler(buff_characters);

		if (interactive)
		{
			printf("simple_shell$ ");
		}
	}

	free(buffer);
	return (0);
}
