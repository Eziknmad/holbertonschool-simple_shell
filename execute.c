#include "shell.h"

/**
 * execute_command - executes a command with arguments
 * @line: input line
 * @shell_name: name of shell
 *
 * Return: void
 */
void execute_command(char *line, char *shell_name)
{
pid_t pid;
char *argv[64];
char *cmd;
int i = 0;

if (!line || line[0] == '\0')
return;

/* tokenize input */
argv[i] = strtok(line, " ");
while (argv[i] && i < 63)
{
i++;
argv[i] = strtok(NULL, " ");
}
argv[i] = NULL;

cmd = find_command(argv[0]);
if (!cmd)
{
write(STDERR_FILENO, shell_name, strlen(shell_name));
write(STDERR_FILENO, ": 1: ", 5);
write(STDERR_FILENO, argv[0], strlen(argv[0]));
write(STDERR_FILENO, ": not found\n", 12);
return;
}

pid = fork();
if (pid == 0)
{
execve(cmd, argv, environ);
perror(shell_name);
exit(1);
}
wait(NULL);
free(cmd);
}
