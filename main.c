#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: 0 on success, or exit code on failure
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();

	return (0);
}
