#include "shell.h"
#include <string.h>

/**
 * execute_direct_path - executes command using a direct path
 * @args: argument array
 *
 * Return: exit status
 */
int execute_direct_path(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(1);
	}
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

/**
 * execute_path_command - executes command found in PATH
 * @args: argument array
 *
 * Return: exit status
 */
int execute_path_command(char **args)
{
	char *cmd_path;
	pid_t pid;
	int status;

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "./hsh: 1: ", 10);
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("execve");
		free(cmd_path);
		exit(1);
	}
	if (pid < 0)
	{
		free(cmd_path);
		perror("fork");
		return (1);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

/**
 * execute_command - executes a command
 * @args: argument array
 *
 * Return: command exit status, or -1 on exit
 */
int execute_command(char **args)
{
	int status;

	if (!args || !args[0])
		return (0);

	if (strcmp(args[0], "exit") == 0)
		return (-1);

	if (args[0][0] == '/' ||
		(args[0][0] == '.' &&
		(args[0][1] == '/' ||
		(args[0][1] == '.' && args[0][2] == '/'))))
	{
		status = execute_direct_path(args);
		return (status);
	}

	status = execute_path_command(args);
	return (status);
}
