#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * shell_loop - Main shell loop that reads and executes commands
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	while (1)
	{
		print_prompt();
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		args = split_line(line);
		execute_command(args);
		free(args);
	}
}
