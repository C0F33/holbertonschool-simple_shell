#include "shell.h"

void main()
{
    size_t read;
    char *buffer = NULL;
    size_t size = 0;
    char *token;
    char *delim = " ";
    bool running = true;

    while (running == true)
    {
        printf("$ ");
        read = getline(&buffer, &size, stdin);
        // printf("%s", buffer);

        if (read == -1)
        {
            printf("Error\n");
            running = false;
        }
        else
        {
            token = strtok(buffer, delim); 
            while (token != NULL)
            {
                
                printf("token: %s\n", token);

                token = strtok(NULL, delim);

            }

        }
        
    }

}
