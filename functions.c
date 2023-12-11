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
	char *token = NULL, *command_dup = NULL;
	int num_of_args = 1, i = 0, j = 0;

	if (command == NULL)
		return (-1);
	if (command[0] != '/')
	{
		command_dup = add_env(command);
		if (command_dup == NULL)
			return (-1);
	}
	else
		command_dup = custom_strdup(command);
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
	free(command_dup);
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

/**
 * add_env - adds path environment variable to input and checks if file exists
 * @file: File
 * Return: A string containing the full path to file on Sucess
 * Returns NULL on error
 */
char *add_env(char *file)
{
	char *environ = getenv("PATH"), *environ_dup = custom_strdup(environ);
	char *token = NULL, *full_path = NULL;
	char *file_dup = custom_strdup(file);
	struct stat file_info;
	int file_exists = 1;

	token = strtok(environ_dup, ":");
	while (token != NULL)
	{
		full_path = add_strings(token, "/", file_dup);
		if (full_path == NULL)
		{
			free(token);
			free(file_dup);
			free(environ_dup);
		}
		if (stat(full_path, &file_info) != 0)
			file_exists = 0;
		if (file_exists == 1)
			break;
		token = strtok(NULL, ":");
		full_path = NULL;
	}
	if (file_exists == 0)
	{
		free(file_dup);
		free(full_path);
		free(environ_dup);
		return (NULL);
	}

	return (full_path);
}

/**
 * add_strings - adds 3 strings together
 * @first: First string
 * @delim: Delimeter
 * @second: Second String
 * Return: New String
 */
char *add_strings(char *first, char *delim, char *second)
{
	int first_length = _strlen(first), second_length = _strlen(second);
	int delim_length = _strlen(delim), i = 0, j;
	int length = first_length + second_length + delim_length;
	char *output = NULL;

	if (first == NULL && second == NULL && delim == NULL)
		return (NULL);

	output = (char *)malloc(sizeof(char) * (length + 1));
	if (output == NULL)
		return (NULL);


	for (j = 0; j < first_length; i++, j++)
		output[i] = first[j];
	for (j = 0; j < delim_length; i++, j++)
		output[i] = delim[j];
	for (j = 0; j < second_length; i++,j++)
		output[i] = second[j];
	output[i] = '\0';
	return (output);
}

