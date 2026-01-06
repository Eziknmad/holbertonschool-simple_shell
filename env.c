#include "shell.h"
#include <string.h>

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the variable
 *
 * Return: pointer to value or NULL if not found
 */
char *_getenv(const char *name)
{
	int i, j;

	if (!name || !environ)
		return (NULL);

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
