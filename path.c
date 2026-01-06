#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * build_path - Builds the full path to a command.
 * @dir: Directory path.
 * @cmd: Command name.
 *
 * Return: Allocated string with full path or NULL.
 */
static char *build_path(char *dir, char *cmd)
{
	char *full_path;
	int len;

	len = strlen(dir) + strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
}

/**
 * find_command - Finds the full path of a command by searching PATH.
 * @command: The command name.
 *
 * Return: Allocated string with full path or NULL if not found.
 */
char *find_command(char *command)
{
	char *path_env, *path_dup, *token, *full_path;

	if (!command)
		return (NULL);

	/* If command is an executable file itself */
	if (access(command, X_OK) == 0)
		return (strdup(command));

	/* Get PATH environment variable */
	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_dup = strdup(path_env);
	if (!path_dup)
		return (NULL);

	token = strtok(path_dup, ":");
	while (token)
	{
		full_path = build_path(token, command);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}
