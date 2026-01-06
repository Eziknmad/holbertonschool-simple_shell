#include "shell.h"

/**
 * execute_command - forks and executes command with arguments
 * @args: arguments array (args[0] = command)
 * @shell_name: shell program name for error messages
 *
 * Return: void
 */
void execute_command(char **args, char *shell_name)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!args[0])
		return;

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", shell_name, args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(shell_name);
			free(cmd_path);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}
