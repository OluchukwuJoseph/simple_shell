#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;
int execute(char **args, char **argp);
char *custom_strdup(char *input);
size_t _strlen(char *input);
size_t is_space(char *input);
int tokenize(char *command, char ***args);
void free_double_pointer(char **pointer);
char *add_strings(char *first, char *delim, char *second);
char *add_path(char *file);
char *strmod(char *input, char limit);
char *take_first_word(char *input, char limit);
int compare_strings(char *first_string, char *second_string);
void print_env(void);
char *_getcwd(void);
ssize_t custom_getline(char **lineptr, size_t *len, FILE *stream);
int custom_exit(char *input);

#endif
