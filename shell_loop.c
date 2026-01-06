#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;

	while (1)
	{
		print_prompt();

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		trim_whitespace(line);
		args = split_line(line);
		if (!args)
			continue;

		execute_command(args);
		free(args);
	}
}
