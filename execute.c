#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * is_path_command - Checks if command contains a '/' char
 * @command: The command string
 *
 * Return: 1 if command contains '/', 0 otherwise
 */
int is_path_command(char *command)
{
	int i = 0;

	if (!command)
		return (0);

	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/**
 * run_path_command - Executes a command with path
 * @args: Argument list, args[0] is the command
 */
void run_path_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
	{
		execve(args[0], args, NULL);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

/**
 * run_command_with_path - Executes a command by searching PATH
 * @args: Argument list, args[0] is the command
 */
void run_command_with_path(char **args)
{
	char *full_path;

	full_path = find_command(args[0]);
	if (full_path)
	{
		pid_t pid;
		int status;

		pid = fork();
		if (pid == -1)
			perror("fork failed");
		if (pid == 0)
		{
			execve(full_path, args, NULL);
			perror("execve failed");
			free(full_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
			free(full_path);
		}
	}
	else
	{
		/* command not found, print error */
		fprintf(stderr, "%s: command not found\n", args[0]);
	}
}

/**
 * execute_command - Executes the command with arguments
 * @args: Null-terminated array of arguments
 */
void execute_command(char **args)
{
	if (args == NULL || args[0] == NULL)
		return;

	if (is_path_command(args[0]))
		run_path_command(args);
	else
		run_command_with_path(args);
}
