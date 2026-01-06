#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * shell_loop - Main shell loop
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	char **args;

	while (1)
	{
		print_prompt();
		if (getline(&line, &len, stdin) == -1)
			break;

		args = split_line(line);
		if (!args || !args[0])
		{
			free(args);
			continue;
		}

		execute_command(args);
		free(args);
	}
	free(line);
}
