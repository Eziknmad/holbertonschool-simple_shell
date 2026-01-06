#include "shell.h"

/**
 * print_prompt - prints shell prompt
 *
 * Return: void
 */
void print_prompt(void)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "#cisfun$ ", 9);
}
