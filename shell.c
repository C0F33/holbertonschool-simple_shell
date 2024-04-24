#include <unistd.h>
#include "shell.h"

int main() {
    char *buffer = NULL;
    size_t size = 0;
    ssize_t read;


    int interactive = isatty(STDIN_FILENO);

    if (interactive) {
        printf("simple_shell$ ");
    }

    while ((read = getline(&buffer, &size, stdin)) != -1) {
        if (buffer[read - 1] == '\n') {
            buffer[read - 1] = '\0';
        }

        token_handler(buffer, " ");
        process_handler(buffer);

        if (interactive) {
            printf("simple_shell$ ");
        }
    }

    free(buffer);
    return 0;
}
