#include "shell.h"

/**
 * execute_command - executes a command with arguments
 * @line: input command line
 * @shell_name: shell program name for errors
 *
 * Return: void
 */
void execute_command(char *line, char *shell_name)
{
    pid_t pid;
    char *argv[64];
    char *cmd_path;
    int i = 0;

    if (!line || line[0] == '\0')
        return;

    argv[i] = strtok(line, " ");
    while (argv[i] && i < 63)
    {
        i++;
        argv[i] = strtok(NULL, " ");
    }
    argv[i] = NULL;

    /* Find full path of command */
    cmd_path = find_command(argv[0]);
    if (!cmd_path)
    {
        write(STDERR_FILENO, shell_name, strlen(shell_name));
        write(STDERR_FILENO, ": 1: ", 5);
        write(STDERR_FILENO, argv[0], strlen(argv[0]));
        write(STDERR_FILENO, ": not found\n", 12);
        return;  /* Do NOT fork if command doesn't exist */
    }

    pid = fork();
    if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        perror(shell_name);
        free(cmd_path);
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        free(cmd_path);
    }
    else
    {
        perror("fork");
        free(cmd_path);
    }
}
