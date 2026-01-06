#include "shell.h"

/**
 * trim_whitespace - removes leading and trailing whitespace from a string
 * @str: string to trim
 *
 * Return: void
 */
void trim_whitespace(char *str)
{
	int start = 0, end = strlen(str) - 1;
	int i = 0;

	while (str[start] == ' ' || str[start] == '\t')
		start++;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'))
		end--;

	while (start <= end)
		str[i++] = str[start++];
	str[i] = '\0';
}

/**
 * split_line - splits a line into arguments array by whitespace
 * @line: input line
 *
 * Return: NULL-terminated array of strings (needs free), or NULL on failure
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
