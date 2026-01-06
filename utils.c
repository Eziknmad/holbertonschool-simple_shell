#include "shell.h"
#include <string.h>

/**
 * trim_whitespace - Trims leading and trailing whitespace
 * @str: Input string
 *
 * Return: Trimmed string
 */
char *trim_whitespace(char *str)
{
	int start = 0;
	int end;

	if (!str)
		return (NULL);

	end = strlen(str) - 1;

	while (str[start] &&
	       (str[start] == ' ' ||
		str[start] == '\t' ||
		str[start] == '\n'))
		start++;

	while (end >= start &&
	       (str[end] == ' ' ||
		str[end] == '\t' ||
		str[end] == '\n'))
		end--;

	str[end + 1] = '\0';

	return (str + start);
}

/**
 * split_line - Splits a line into tokens
 * @line: Input line
 *
 * Return: NULL-terminated array of tokens
 */
char **split_line(char *line)
{
	int bufsize = 64, pos = 0;
	char **tokens;
	char *token;

	tokens = malloc(sizeof(char *) * bufsize);
	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		tokens[pos++] = token;
		token = strtok(NULL, " \t\n");
	}
	tokens[pos] = NULL;

	return (tokens);
}
