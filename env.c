#include "shell.h"

/**
 * _getenv - gets environment variable
 * @name: variable name
 *
 * Return: value or NULL
 */
char *_getenv(char *name)
{
int i, j;

for (i = 0; environ[i]; i++)
{
j = 0;
while (name[j] && environ[i][j] && name[j] == environ[i][j])
j++;

if (name[j] == '\0' && environ[i][j] == '=')
return (&environ[i][j + 1]);
}
return (NULL);
}
