#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * build_path - Concatenate dir and cmd with '/' in between.
 * @dir: directory string.
 * @cmd: command string.
 * Return: allocated string with full path or NULL on failure.
 */
static char *build_path(char *dir, char *cmd)
{
	int len;
	char *full_path;

	len = strlen(dir) + strlen(cmd) + 2;
	full_path = malloc(sizeof(char) * len);
	if (!full_path)
		return (NULL);

	snprintf(full_path, len, "%s/%s", dir, cmd);
	return (full_path);
}

/**
 * check_access - checks if a command exists and is executable.
 * @path: full path to check.
 * Return: 1 if executable, 0 otherwise.
 */
static int check_access(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * check_direct_path - checks if command contains '/' and is executable.
 * @command: command string.
 * Return: duplicated string if executable, NULL otherwise.
 */
static char *check_direct_path(char *command)
{
	if (strchr(command, '/'))
	{
		if (check_access(command))
			return (strdup(command));
		return (NULL);
	}
	return (NULL);
}

/**
 * find_command - finds command full path in PATH or as direct path.
 * @command: command name.
 * Return: full path string or NULL if not found.
 */
char *find_command(char *command)
{
	char *path_env, *path_dup, *token, *full_path;

	if (!command)
		return (NULL);

	full_path = check_direct_path(command);
	if (full_path)
		return (full_path);

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
		if (!full_path)
		{
			free(path_dup);
			return (NULL);
		}

		if (check_access(full_path))
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
