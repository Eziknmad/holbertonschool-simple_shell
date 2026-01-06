#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/**
 * execute_direct_path - executes a command given with a direct path
 * @args: argument array (args[0] is command path)
 */
void execute_direct_path(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}
}

/**
 * execute_path_command - executes a command by searching in PATH
 * @args: argument array (args[0] is command)
 */
void execute_path_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "./hsh: 1: ", 10);
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("execve");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
	else
	{
		perror("fork");
		free(cmd_path);
	}
}

/**
 * execute_command - executes a command, handling direct path or searching PATH
 * @args: argument array
 */
void execute_command(char **args)
{
	if (!args[0])
		return;

	if (args[0][0] == '/')
		execute_direct_path(args);
	else
		execute_path_command(args);
}
