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
	output = (char *)malloc(sizeof(char) * (length + 1));
	if (output == NULL)
		return (NULL);

	for (; i < length; i++)
		output[i] = input[i];
	output[i] = '\0';
	return (output);
}

/**
 * is_space - counts space in a string
 * @input: string
 * Return: amount of space
 */
size_t is_space(char *input)
{
	size_t space = 0, i = 0;

	if (input == NULL)
		return (0);

	for (; input[i] != '\0'; i++)
	{
		if (input[i] == ' ')
			space++;
	}
	return (space);

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
	(*args) = (char **)malloc(sizeof(char *) * (num_of_args + 1));
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
