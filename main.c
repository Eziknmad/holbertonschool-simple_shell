#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	(void)argc; /* argc unused */
	shell_loop(argv[0]);
	return (0);
}
