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
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
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
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

/**
 * execute_command - dispatches command execution
 * @args: argument array
 *
 * Return: exit status
 */
int execute_command(char **args)
{
	if (!args || !args[0])
		return (0);

	/* Check if args[0] is an absolute or relative path */

	if (args[0][0] == '/' ||                 /* absolute path */
	    (args[0][0] == '.' &&                 /* relative path starting with . */
	     (args[0][1] == '/' ||                /* ./ */
	      (args[0][1] == '.' && args[0][2] == '/')))) /* ../ */
		return (execute_direct_path(args));

	return (execute_path_command(args));
}
