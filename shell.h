#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/* Core loop */
void shell_loop(char *shell_name);

/* Prompt */
void print_prompt(void);

/* Execution */
void execute_command(char *line, char *shell_name);

/* PATH + ENV */
char *_getenv(char *name);
char *find_command(char *command);

/* Utils */
void trim_whitespace(char *str);

#endif
