#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

/**
 * execute_command - executes command if found
 * @args: arguments array, args[0] is command
 *
 * Return: void
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!args[0])
		return;

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
