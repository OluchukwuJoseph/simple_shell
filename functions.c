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
 * tokenize - Tokenizes a command string into an array of strings.
 * @command: The input command string to tokenize.
 * @args: A double pointer (array of strings)
 * @Return: 0 on success, -1 on failure
 */
int tokenize(char *command, char ***args)
{
	char *token = NULL, *command_dup = custom_strdup(command);
	int num_of_args = 1, i = 0, j = 0;

	if (command == NULL)
		return (-1);
	/*Count the number of tokens in the string*/
	while (command[j] != '\0')
	{

		if (command[j] == ' ')
			num_of_args++;
		j++;
	}
	/*Allocate memory for an array of strings*/
	(*args) = (char **)malloc(sizeof(char *) * (1 + num_of_args));
	if (*args == NULL)
		return (-1);
	/*Populate the array with tokenized strings*/
	token = strtok(command_dup, " ");
	while (token != NULL)
	{
		(*args)[i] = custom_strdup(token);
		token = strtok(NULL, " ");
		i++;
	}
	(*args)[i] = NULL;
	return (0);
}

/**
 * free_double_pointers - frees the strings in an array of strings
 * @pointer: Array of strings (double pointer)
 * Return: Nothing
 */
void free_double_pointer(char **pointer)
{
	int i = 0;

	while (pointer[i] != NULL)
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}
