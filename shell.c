#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t read;
    long unsigned int read1 = -1;
    char *buffer = NULL;
    size_t size = 0;
    char *delim = " ";

    printf("simple_shell$ ");

    while (1) {
        read = getline(&buffer, &size, stdin);
        if (read == read1) {
            printf("\n");
            free(buffer);
            break;
        }

        if (buffer[read - 1] == '\n') {
            buffer[read - 1] = '\0';
        }

        token_handler(buffer, delim);
        process_handler(buffer);

        printf("simple_shell$ ");
    }

    return 0;
}
