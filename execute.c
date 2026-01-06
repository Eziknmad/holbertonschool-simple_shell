#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * is_path_command - Checks if command contains '/'
 * @command: Command string
 *
 * Return: 1 if path command, 0 otherwise
 */
int is_path_command(char *command)
{
	int i;

	if (!command)
		return (0);

	for (i = 0; command[i]; i++)
	{
		if (command[i] == '/')
			return (1);
	}
	return (0);
}

/**
 * execute_path_command - Execute command with absolute or relative path
 * @args: Argument vector
 */
void execute_path_command(char **args)
{
	pid_t pid;

	if (access(args[0], X_OK) != 0)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}

/**
 * execute_path_search_command - Execute command found via PATH search
 * @args: Argument vector
 */
void execute_path_search_command(char **args)
{
	pid_t pid;
	char *path = find_command(args[0]);

	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(path, args, environ);
		free(path);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	free(path);
}

/**
 * execute_command - Executes a command
 * @args: Argument vector
 */
void execute_command(char **args)
{
	if (!args || !args[0])
		return;

	if (is_path_command(args[0]))
		execute_path_command(args);
	else
		execute_path_search_command(args);
}
