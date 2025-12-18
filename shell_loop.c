#include "shell.h"

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
 * execute_command - executes a single command
 * @line: command entered by user
 *
 * Return: void
 */
void execute_command(char *line)
{
pid_t pid;
char *argv[2];
int status;

argv[0] = line;
argv[1] = NULL;

pid = fork();
if (pid == 0)
{
if (execve(argv[0], argv, environ) == -1)
{
perror("./shell");
exit(1);
}
}
else if (pid > 0)
{
wait(&status);
}
else
{
perror("fork");
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
write(STDOUT_FILENO, "\n", 1);
return;
}
if (line[read - 1] == '\n')
line[read - 1] = '\0';
execute_command(line);
}
}
