#include "shell.h"

/**
 * execute - executes an executable program
 * @args: Arguments that will be passed to the program about to be executed
 * @argp: Environment variables to run with program
 * Return: Return 0 on sucess
 * Return -1 on failure
 */
int execute(char **args, char **argp)
{
	pid_t id;
	int status;

	id = fork();
	if (id < 0)
		return (-1);

	if (id > 0)
	{
		wait(&status);

		if (WEXITSTATUS(status) == 0)
			return (0);
		else
			return (-1);
	}

	if (id == 0)
	{
		if (execve(args[0], args, argp) == -1)
		{
			exit(1);
		}
		exit(0);
	}
	return (0);
}

/**
 * _strlen - counts the characters in a string
 * @input: string to count
 * Return: Length of string
 */
size_t _strlen(char *input)
{
	size_t length = 0;

	while (input[length] != '\0')
		length++;
	return(length);
}

/**
 * custom_strdup - duplicates a string
 * @input: string to be duplicated
 * Return: Duplicated string on sucess
 */
char *custom_strdup(char *input)
{
	size_t length = 0, i = 0;
	char *output = NULL;

	if (input == NULL)
		return (NULL);

	length = _strlen(input);
	output = (char *)malloc(sizeof(char) * length);
	if (output == NULL)
		return (NULL);

	for (; i <= length; i++)
		output[i] = input[i];

	return (output);
}
