#include "shell.h"

/**
 * find_command - finds executable in PATH
 * @command: command name
 *
 * Return: full path or NULL
 */
char *find_command(char *command)
{
char *path, *copy, *dir, *full;
int len;

if (command[0] == '/' && access(command, X_OK) == 0)
return (strdup(command));

path = _getenv("PATH");
if (!path)
return (NULL);

copy = strdup(path);
dir = strtok(copy, ":");

while (dir)
{
len = strlen(dir) + strlen(command) + 2;
full = malloc(len);
if (!full)
break;

strcpy(full, dir);
strcat(full, "/");
strcat(full, command);

if (access(full, X_OK) == 0)
{
free(copy);
return (full);
}

free(full);
dir = strtok(NULL, ":");
}

free(copy);
return (NULL);
}
