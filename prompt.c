#include "shell.h"
#include <unistd.h>

/**
 * print_prompt - displays shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
