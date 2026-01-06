#include "shell.h"

/**
 * trim_whitespace - trims spaces
 * @str: string
 *
 * Return: void
 */
void trim_whitespace(char *str)
{
int i = 0, j = 0;

while (str[i] == ' ' || str[i] == '\t')
i++;

while (str[i])
str[j++] = str[i++];

while (j > 0 && (str[j - 1] == ' ' || str[j - 1] == '\t'))
j--;

str[j] = '\0';
}
