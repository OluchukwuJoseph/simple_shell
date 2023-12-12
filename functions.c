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
int tokenize(char *file, char ***args)
{
	char *token = NULL, *command = NULL, *arguments = NULL;
	char *file_dup = NULL, *token_dup = NULL, *path_to_file = NULL;
	int num_of_args = 0, i = 0;
	struct stat file_info;

	if (file[0] == '/')
		command = custom_strdup(file);
	else
	{
		file_dup = custom_strdup(file);
		arguments = strmod(file_dup, ' ');
		token_dup = take_first_word(file_dup, ' ');
		path_to_file = add_path(token_dup);
		free(token_dup);
		free(file_dup);
		if (path_to_file == NULL)
		{
			free(arguments);
			return (-1);
		}
		if (arguments != NULL)
		{
			command = add_strings(path_to_file, "", arguments);
			free(path_to_file);
			free(arguments);
		}
		if (arguments == NULL)
		{
			command = custom_strdup(path_to_file);
			free(path_to_file);
			free(arguments);
		}
	}
	/*Count the number of tokens in the string*/
	num_of_args = is_space(command);
	num_of_args++;
	/*Allocate memory for an array of strings*/
	(*args) = (char **)malloc(sizeof(char *) * (1 + num_of_args));
	if (*args == NULL)
		return (-1);
	/*Populate the array with tokenized strings*/
	token = strtok(command, " ");
	while (token != NULL)
	{
		(*args)[i] = custom_strdup(token);
		token = strtok(NULL, " ");
		i++;
	}
	(*args)[i] = NULL;
	if (stat((*args)[0], &file_info) != 0)
	{
		free_double_pointer(*args);
		free(command);
		return (-1);
	}
	free(command);
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
char *add_path(char *file)
{
	char *environ = getenv("PATH"), *environ_dup = NULL;
	char *token = NULL, *full_path = NULL, *file_dup = custom_strdup(file);
	struct stat file_info;
	int file_exists = 1;

	environ_dup = custom_strdup(environ);
	token = strtok(environ_dup, ":");
	while (token != NULL)
	{
		full_path = add_strings(token, "/", file_dup);
		if (full_path == NULL)
		{
			free(environ_dup);
			free(token);
			free(file_dup);
		}
		if (stat(full_path, &file_info) != 0)
		{
			free(full_path);
			file_exists = 0;
		}
		if (file_exists == 1)
			break;
		file_exists = 1;
		token = strtok(NULL, ":");
	}
	if (token == NULL)
	{
		free(environ_dup);
		/*free(full_path);*/
		free(file_dup);
		return (NULL);
	}
	free(environ_dup);
	free(file_dup);
	return (full_path);
}

/**
 * take_first_word - Take first word from a string
 * The first word is the characters before limit
 * @input: String
 * @limit: Character to look out for
 * Return: First word on sucess
 * NULL on Failure (Insufficient Memory)
 */
char *take_first_word(char *input, char limit)
{
	char *output = NULL;
	int i = 0, j = 0;

	while (input[i] != '\0')
	{
		if (input[i] == limit)
			break;
		i++;
	}

	output = (char *)malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (NULL);
	for (; j < i; j++)
		output[j] = input[j];
	output[j] = '\0';

	return (output);
}
