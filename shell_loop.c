#include "shell.h"
#include <string.h>

/**
 * print_prompt - displays shell prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * _getenv - gets environment variable value
 * @name: variable name
 *
 * Return: pointer to value or NULL
 */
char *_getenv(char *name)
{
	int i, j;
	char *value;

	if (!name || !environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		while (name[j] && environ[i][j] && name[j] == environ[i][j])
			j++;

		if (name[j] == '\0' && environ[i][j] == '=')
		{
			value = &environ[i][j + 1];
			return (value);
		}
	}
	return (NULL);
}

/**
 * find_command - finds command in PATH or returns absolute path
 * @command: command to find
 *
 * Return: full path to command or NULL
 */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char full_path[1024];

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
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

/**
 * execute_command - executes a single command
 * @line: command entered by user
 *
 * Return: void
 */
void execute_command(char *line)
{
	pid_t pid;
	char *argv[2];
	char *cmd_path;
	int status;

	if (line[0] == '\0')
		return;

	cmd_path = find_command(line);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "./hsh: 1: ", 10);
		write(STDERR_FILENO, line, strlen(line));
		write(STDERR_FILENO, ": not found\n", 12);
		return;
	}

	argv[0] = cmd_path;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./hsh");
			free(cmd_path);
			exit(1);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		free(cmd_path);
	}
	else
	{
		perror("fork");
		free(cmd_path);
	}
}

/**
 * trim_whitespace - removes leading and trailing whitespace
 * @str: string to trim
 *
 * Return: void
 */
void trim_whitespace(char *str)
{
	int i, j;
	int len = strlen(str);

	/* Remove trailing whitespace */
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
	{
		str[len - 1] = '\0';
		len--;
	}

	/* Remove leading whitespace */
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;

	if (i > 0)
	{
		j = 0;
		while (str[i])
		{
			str[j] = str[i];
			j++;
			i++;
		}
		str[j] = '\0';
	}
}

/**
 * shell_loop - main shell execution loop
 *
 * Return: void
 */
void shell_loop(void)
{
	char *line;
	size_t len;
	ssize_t read;

	line = NULL;
	len = 0;

	while (1)
	{
		print_prompt();
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		trim_whitespace(line);
		execute_command(line);
	}
}
