#include "shell.h"

/**
 * execute_command - runs a command
 * @line: input
 * @shell_name: shell name
 *
 * Return: void
 */
void execute_command(char *line, char *shell_name)
{
pid_t pid;
char *argv[2];
char *cmd;

if (!line || line[0] == '\0')
return;

cmd = find_command(line);
if (!cmd)
{
write(STDERR_FILENO, shell_name, strlen(shell_name));
write(STDERR_FILENO, ": 1: ", 5);
write(STDERR_FILENO, line, strlen(line));
write(STDERR_FILENO, ": not found\n", 12);
return;
}

argv[0] = cmd;
argv[1] = NULL;

pid = fork();
if (pid == 0)
execve(cmd, argv, environ);

wait(NULL);
free(cmd);
}
