#include "shell.h"
#include <string.h>

/**
 * _getenv - gets the value of an environment variable.
 * @name: the name of the environment variable.
 * Return: pointer to the value string or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i, len;

	if (!name)
		return (NULL);

	len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}

	return (NULL);
}
