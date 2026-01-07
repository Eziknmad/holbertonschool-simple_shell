#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int shell_loop(void);
void print_prompt(void);

void execute_command(char **args);
int execute_direct_path(char **args);
int execute_path_command(char **args);

char *_getenv(const char *name);
char *find_command(char *command);

void trim_whitespace(char *str);
char **split_line(char *line);

#endif /* SIMPLE_SHELL_H */
