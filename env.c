#include "shell.h"
#include <string.h>

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The environment variable name.
 *
 * Return: Pointer to the value string, or NULL if not found.
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
