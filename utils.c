#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * trim_whitespace - removes leading and trailing whitespace from str
 * @str: string to trim
 *
 * Return: void
 */
void trim_whitespace(char *str)
{
	int start = 0, end = strlen(str) - 1;
	int i;

	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'))
		str[end--] = '\0';

	if (start > 0)
	{
		i = 0;
		while (str[start])
			str[i++] = str[start++];
		str[i] = '\0';
	}
}

/**
 * split_line - splits line into tokens (words)
 * @line: input string to split
 *
 * Return: array of pointers to tokens, NULL terminated
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		tokens[position++] = token;
		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, " \t");
	}
	tokens[position] = NULL;
	return (tokens);
}
