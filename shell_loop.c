#include "shell.h"

/**
 * shell_loop - main shell loop
 *
 * Return: last command exit status
 */
int shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int status = 0;
	int ret;

	while (1)
	{
		print_prompt();

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			return (status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		trim_whitespace(line);
		args = split_line(line);
		if (!args)
			continue;

		ret = execute_command(args);
		free(args);

		if (ret == -1)
		{
			free(line);
			exit(status);
		}

		status = ret;
	}
}
