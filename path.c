#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: variable name
 *
 * Return: pointer to value or NULL
 */
char *_getenv(const char *name)
{
	int i, j;

	if (!name || !environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; name[j] && environ[i][j] && name[j] == environ[i][j]; j++)
			;

		if (name[j] == '\0' && environ[i][j] == '=')
			return (&environ[i][j + 1]);
	}
	return (NULL);
}

/**
 * find_command - finds command in PATH or returns NULL if not found
 * @command: command name
 *
 * Return: full path string (malloc'd) or NULL if not found
 */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char full_path[1024];

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
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
