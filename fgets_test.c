#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell.h"

int main() {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;
    char *token;

    printf("$ ");

    while ((bytes_read = getline(&buffer, &bufsize, stdin)) != -1) {

        if (buffer[bytes_read - 1] == '\n')
		{
        	buffer[bytes_read - 1] = '\0';
        }


        token = strtok(buffer, " ");

        while (token != NULL) {

            printf("Token: %s\n", token);


            token = strtok(NULL, " ");
        }

        printf("$ ");
    }


    free(buffer);

    return 0;
}
