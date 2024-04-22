#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PATH_MAX 4096

void handle_builtin(char *command) {
    if (strcmp(command, "cd") == 0) {

        char *directory = strtok(NULL, " ");
        if (directory == NULL) {
            fprintf(stderr, "cd: missing directory\n");
            return;
        }


        if (chdir(directory) != 0) {
            perror("cd");
        }
    } else if (strcmp(command, "exit") == 0) {

        exit(EXIT_SUCCESS);
    }
}

int main() {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;
    char *token;

    printf("simple_shell$ ");

    while (1)
	{
		bytes_read = getline(&buffer, &bufsize, stdin);
		if (bytes_read == -1)
        {
            printf("\n");
            break;
		}

        if (buffer[bytes_read - 1] == '\n') {
            buffer[bytes_read - 1] = '\0';
        }


        token = strtok(buffer, " ");

        if (token != NULL) {

            handle_builtin(token);


        }



		 char full_path[PATH_MAX];
        sprintf(full_path, "%s", buffer);

        if (access(full_path, X_OK) == 0) {

            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
            } else if (pid == 0) {

                char *args[] = {buffer, NULL};
                execve(full_path, args, NULL);

                perror("execve");
                exit(EXIT_FAILURE);
            } else {

                wait(NULL);
            }
		}
		else
			printf("Shell: Command not found: %s\n", buffer);

		printf("simple_shell$ ");
	}


	free(buffer);

	return 0;
}
