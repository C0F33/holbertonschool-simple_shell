#include "shell.h"

int main(void)
{
    int read;
    char *buffer = NULL;
    size_t size = 0;
    char *delim = " \t";
    
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

    return (0);
}
