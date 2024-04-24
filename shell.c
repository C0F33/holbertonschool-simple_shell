#include "shell.h"

void main()
{
    size_t read;
    char *buffer = NULL;
    size_t size = 0;
    char *token;
    char *delim = " ";

printf("simple_shell$ ");

    while (1)
	{
		read = getline(&buffer, &size, stdin);
		if (read == -1)
        {
            printf("\n");
            break;
		}

        if (buffer[read - 1] == '\n')
        {
            buffer[read - 1] = '\0';
        }

        token_handler(buffer, delim);
        process_handler(buffer);

        printf("simple_shell$ ");
    }

    free(buffer);

}
