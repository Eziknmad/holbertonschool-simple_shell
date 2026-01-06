#include "shell.h"

/**
 * shell_loop - main shell loop
 * @shell_name: name of the shell executable (argv[0])
 *
 * Return: void
 */
void shell_loop(char *shell_name)
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
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		trim_whitespace(line);

		if (line[0] == '\0')
			continue;

		args = split_line(line);
		if (!args)
			continue;

		execute_command(args, shell_name);

		free(args);
	}
}
