#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* Function prototypes */
char *_getenv(const char *name);
char *find_command(char *command);

/**
 * main - Entry point of the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv);

/**
 * shell_loop - Runs the main shell loop
 */
void shell_loop(void);

/**
 * execute_command - Executes a command
 * @args: Argument vector
 */
void execute_command(char **args);

/**
 * print_prompt - Prints shell prompt
 */
void print_prompt(void);

/**
 * trim_whitespace - Trims whitespace
 * @str: Input string
 *
 * Return: Trimmed string
 */
char *trim_whitespace(char *str);

/**
 * split_line - Splits a line into tokens
 * @line: Input line
 *
 * Return: Token array
 */
char **split_line(char *line);

#endif /* SHELL_H */
