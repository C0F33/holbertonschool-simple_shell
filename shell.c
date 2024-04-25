#include "simple_shell.h"

/**
 * _print_environment - Prints environment variables like printenv
 *
 * Return: Always returns 0
 */
int _print_environment(void)
{
    char *env_var = environ[0];
    int index = 0;

    while (env_var)
    {
        write(1, env_var, strlen(env_var));
        write(1, "\n", 1);
        env_var = environ[++index];
    }
    return (0);
}

/**
 * _strncmp - Compares not more than n characters of two strings
 * @s1: First string
 * @s2: Second string to compare to the first string
 * @n: Number of characters to compare
 * Return: <0 if s1 is less than s2, 0 for equal, >0 if s1 is greater than s2
 */
int _strncmp(char *s1, char *s2, int n)
{
    char c1, c2;

    while (n--)
    {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 == '\0' || c1 != c2)
            return (c1 > c2 ? 1 : (c1 < c2 ? -1 : 0));
    }
    return (0);
}

/**
 * _getenv - Gets the value of the environment variable 'var'
 * @var: Name of the environment variable
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(char *var)
{
    int index = 0;

    for (index = 0; environ[index]; index++)
    {

        if (_strncmp(environ[index], var, strlen(var)) == 0)
            return (&environ[index][strlen(var)]);
    }
    return (NULL);
}

/**
 * path_handler - Searches for the executable path of a command in the PATH variable
 * @cmd: Command passed from getline in main
 * Return: New path for use in cmd_read, or NULL if not found
 */
char *path_handler(char *cmd)
{
    char *path_env = strdup(_getenv("PATH"));
    int path_index = 0;
    int token_index = 0;
    char *path_tokens = strtok(path_env, ":");
    char *path_array[100];
    char *command = cmd;
    char *new_path = NULL;
    struct stat buf;

    new_path = malloc(sizeof(char) * 1000);

    if (_getenv("PATH")[0] == ':' && stat(cmd, &buf) == 0)
        return strdup(cmd);

    while (path_tokens != NULL)
    {
        path_array[path_index++] = path_tokens;
        path_tokens = strtok(NULL, ":");
    }
    path_array[path_index] = NULL;

    for (token_index = 0; path_array[token_index]; token_index++)
    {
        strcpy(new_path, path_array[token_index]);
        strcat(new_path, "/");
        strcat(new_path, command);

        if (stat(new_path, &buf) == 0)
        {
            free(path_env);
            return new_path;
        }
        else
        {
            new_path[0] = '\0';
        }
    }

    free(path_env);
    free(new_path);

    if (stat(cmd, &buf) == 0)
        return strdup(cmd);

    return NULL;
}

int main(int argc, char *argv[])
{
    char *input_line = NULL;
    size_t buffer_size = 0;
    ssize_t line_length = 0;
    char *program_name = argv[0];

    (void)argc;

    while (1)
    {

        if (is_terminal_input())
            print_prompt();

        line_length = read_input_line(&input_line, &buffer_size);

        if (line_length == -1)
        {
            if (is_terminal_input())
                write_newline();
            break;
        }

        process_command(input_line, line_length, program_name);
    }

    free(input_line);
    return 0;
}

int process_command(char *input_line, ssize_t line_length, char *program_name)
{
    char *token = NULL;
    char *command_array[100];
    int token_count = 0;
    int result = 0;

    if (input_line == NULL)
        return 0;

    if (is_exit_command(input_line))
        return 2;

    if (is_env_command(input_line))
        return _print_environment();

    token = tokenize_command(input_line, &token_count);
    while (token != NULL)
    {
        command_array[token_count++] = token;
        token = tokenize_command(NULL, &token_count);
    }

    if (token_count > 0)
    {
        command_array[token_count] = NULL;
        result = execute_command(command_array, program_name);
    }

    return result;
}

int execute_command(char *command_array[], char *program_name)
{
    char *command = command_array[0];
    struct stat command_info;
    char *executable_path = NULL;
    int execution_result;

    if (is_path_command(command) || is_relative_command(command) || is_path_unset())
    {
        if (stat(command, &command_info) == 0)
        {
            execution_result = execute_command_array(command_array, program_name);
            return execution_result;
        }
        else
        {
            print_command_not_found_error(command, program_name);
            return 3;
        }
    }

    executable_path = find_executable_path(command);
    if (executable_path == NULL)
    {
        print_command_not_found_error(command, program_name);
        return 3;
    }

    command_array[0] = executable_path;
    execution_result = execute_command_array(command_array, program_name);
    free(executable_path);
    return execution_result;
}

int execute_command_array(char *command_array[], char *program_name)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid < 0)
    {
        print_fork_error(program_name);
        return -1;
    }

    if (child_pid > 0)
    {
        wait(&status);
    }
    else
    {
        execve(command_array[0], command_array, environ);
        print_exec_error(program_name);
        exit(EXIT_FAILURE);
    }

    return 0;
}
