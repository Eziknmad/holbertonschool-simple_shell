#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * find_command - finds command full path in PATH env or returns NULL
 * @command: command name
 *
 * Return: full path string or NULL if not found
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *dir;
	char full_path[1024];

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
