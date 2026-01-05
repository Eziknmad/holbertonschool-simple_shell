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

#endif /* SIMPLE_SHELL_H */
