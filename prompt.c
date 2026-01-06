#include "shell.h"

/**
 * print_prompt - prints the shell prompt if input is from terminal
 *
 * Return: void
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 8);
}
