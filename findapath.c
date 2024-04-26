#include "simple_shell.h"
/**
 * search_path - Finds the full path of a command.
 * @cmd: The command to find.
 * Return: A pointer to a string containing the full path of the command,
 * or NULL if the command is not found in the PATH.
 */
char *search_path(char *cmd)
{
	int index_i = 0, index_j = 0;
	char *path_arr[100];
	char *s = cmd;
	char *full_path = NULL;
	struct stat st;
	char *path_tokens;

	char *path_env = strdup(_getenv("PATH"));
    if (path_env == NULL)
	{
        return NULL;
    }
	path_env = strdup(_getenv("PATH"));
	path_tokens = strtok(path_env, ":");

	full_path = malloc(sizeof(char) * 1000);
	if (_getenv("PATH")[0] == ':')
	{
		if (stat(cmd, &st) == 0)
		{
			return (strdup(cmd));
		}
	}
	while (path_tokens != NULL)
	{
		path_arr[index_i++] = path_tokens;
		path_tokens = strtok(NULL, ":");
	}
	path_arr[index_i] = NULL;
	for (index_j = 0; path_arr[index_j]; index_j++)
	{
		strcpy(full_path, path_arr[index_j]);
		strcat(full_path, "/");
		strcat(full_path, s);

		if (stat(full_path, &st) == 0)
		{
			free(path_env);
			return (full_path);
		}
		else
		{
			full_path[0] = 0;
		}
	}
	free(path_env);
	free(full_path);

	if (stat(cmd, &st) == 0)
	{
		return (strdup(cmd));
	}
	return (NULL);
}
