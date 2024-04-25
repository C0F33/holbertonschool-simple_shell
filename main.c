#include "shell.h"

int main(void)
{
	char *line;

	while (1)
	{
	prompt();
	line = _getline();

	if (strcmp(line, "env\n") == 0)
	{
	print_env();
	}
	else if (strcmp(line, "exit\n") == 0)
	{
	break;
	}
	else
	{
	/* Implement other commands */
	}

	free(line);
	}

	return (0);
}

