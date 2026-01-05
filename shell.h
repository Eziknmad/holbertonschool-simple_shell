#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
 * shell_loop - main shell loop
 *
 * Return: void
 */
void shell_loop(void);

/**
 * print_prompt - displays shell prompt
 *
 * Return: void
 */
void print_prompt(void);

/**
 * execute_command - executes a single command
 * @line: command entered by user
 *
 * Return: void
 */
void execute_command(char *line);

/**
 * find_command - finds command in PATH
 * @command: command to find
 *
 * Return: full path or NULL
 */
char *find_command(char *command);

/**
 * _getenv - gets environment variable value
 * @name: variable name
 *
 * Return: pointer to value or NULL
 */
char *_getenv(char *name);

/**
 * trim_whitespace - removes leading and trailing whitespace
 * @str: string to trim
 *
 * Return: void
 */
void trim_whitespace(char *str);

#endif /* SIMPLE_SHELL_H */
