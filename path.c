#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *find_command(char *command)
{
	char *path_env, *path_copy, *dir;
	char full_path[1024];

	if (!command)
		return (NULL);

	/* PATH search ONLY (no slashes allowed here) */
	path_env = _getenv("PATH");
	if (!path_env || *path_env == '\0')
		return (NULL);

	path_copy = strdup(path_env);
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
