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

int execute(char **args, char **argp);
char *custom_strdup(char *input);
size_t _strlen(char *input);

#endif
