#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h> // For chdir, execve
#include <sys/wait.h> // For wait

#define BUFFER_SIZE 1024
#define PATH_MAX 4096 // Maximum length of a file path

// Function to handle built-in commands
void handle_builtin(char *command) {
    if (strcmp(command, "cd") == 0) {
        // Get the next token which should be the directory
        char *directory = strtok(NULL, " ");
        if (directory == NULL) {
            fprintf(stderr, "cd: missing directory\n");
            return;
        }

        // Change directory
        if (chdir(directory) != 0) {
            perror("cd");
        }
    } else if (strcmp(command, "exit") == 0) {
        // Exit the shell
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
        // Remove trailing newline if present
        if (buffer[bytes_read - 1] == '\n') {
            buffer[bytes_read - 1] = '\0';
        }

        // Tokenize the input
        token = strtok(buffer, " ");

        if (token != NULL) {
            // Check if it's a built-in command
            handle_builtin(token);


        }

    // Attempt to execute the command from /bin

		 char full_path[PATH_MAX];
        sprintf(full_path, "%s", buffer);

        if (access(full_path, X_OK) == 0) {
            // Fork a child process to execute the command
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
            } else if (pid == 0) {
                // Child process
                char *args[] = {buffer, NULL};
                execve(full_path, args, NULL);
                // If execve fails, print error message
                perror("execve");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                // Wait for the child process to complete
                wait(NULL);
            }
		}
		else
			printf("Shell: Command not found: %s\n", buffer);

		printf("simple_shell$ ");
	}

    // Free dynamically allocated buffer

	free(buffer);

	return 0;
}
