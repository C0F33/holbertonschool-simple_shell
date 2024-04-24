#include "shell.h"

void process_handler(char *buffer)
{

    char full_path[PATH_MAX];
    sprintf(full_path, "%s", buffer);

    if (access(full_path, X_OK) == 0) 
    {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
        } 
        else if (pid == 0) 
        {
            char *args[] = {buffer, NULL};
                
            execve(full_path, args, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            wait(NULL);
        }
	}
	else
		printf("Shell: Command not found: %s\n", buffer);
}