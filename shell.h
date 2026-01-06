#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/* main.c */
int main(int argc, char **argv);

/* shell_loop.c */
void shell_loop(char *shell_name);

/* prompt.c */
void print_prompt(void);

/* execute.c */
void execute_command(char **args, char *shell_name);

/* path.c */
char *_getenv(const char *name);
char *find_command(char *command);

/* utils.c */
void trim_whitespace(char *str);
char **split_line(char *line);

#endif /* SIMPLE_SHELL_H */
