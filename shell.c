#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
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

        char *trimmed_buffer = buffer;
        while (*trimmed_buffer && isspace(*trimmed_buffer)) {
            trimmed_buffer++;
        }

        if (*trimmed_buffer == '\0') {

            continue;
        }

        if (buffer[read - 1] == '\n') {
            buffer[read - 1] = '\0';
        }

        token_handler(trimmed_buffer, " ");
        process_handler(trimmed_buffer);

        if (interactive) {
            printf("simple_shell$ ");
        }
    }

    free(buffer);
    return 0;
}