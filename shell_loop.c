#include "shell.h"

/**
 * shell_loop - main shell loop
 * @shell_name: name of shell
 *
 * Return: void
 */
void shell_loop(char *shell_name)
{
char *line = NULL;
size_t len = 0;
ssize_t read;

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
execute_command(line, shell_name);
}
}
