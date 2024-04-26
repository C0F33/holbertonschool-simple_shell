#include "simple_shell.h"

/**
 * print_env - Prints the environment variables.
 * This function does not take any parameters and does not return a value.
 */
void print_env(void)
{
    char *env_ptr = environ[0];
    int index = 0;

    while (env_ptr)
    {
        write(1, env_ptr, strlen(env_ptr));
        write(1, "\n", 1);
        env_ptr = environ[++index];
    }
}

/**
 * str_cmp - Compares up to n characters of two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * @num_chars: The maximum number of characters to compare.
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
int str_cmp(char *str1, const char *str2, int num_chars)
{
    char char1, char2;

    while (num_chars--)
    {
        char1 = *str1++;
        char2 = *str2++;
        if (char1 == '\0' || char1 != char2)
            return (char1 > char2 ? 1 : (char1 < char2 ? -1 : 0));
    }
    return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @var_name: The name of the environment variable to retrieve.
 * Return: A pointer to a string containing the value of the
 * environment variable,
 * or NULL if the environment variable does not exist.
 */
char *_getenv(const char *var_name)
{
    int index = 0;

    for (index = 0; environ[index]; index++)
    {
        if (str_cmp(environ[index], var_name, strlen(var_name)) == 0)
            return (&environ[index][strlen(var_name)]);
    }
    return (NULL);
}
