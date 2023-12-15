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
			return (1);
	}

	if (id == 0)
	{
		if (execve(args[0], args, argp) == -1)
		{
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	return (0);
}

/**
 * tokenize - Tokenizes a command string into an array of strings.
 * @file: The input command string to tokenize.
 * @args: A double pointer (array of strings)
 * Return: 0 on success, -1 on failure
 */
int tokenize(char *file, char ***args);
int tokenize(char *file, char ***args)
{
	char *token = NULL, *command = NULL, *arguments = NULL;
	char *token_dup = NULL, *path_to_file = NULL, *file_dup = NULL;
	int num_of_args = 0, i = 0;

	file_dup = custom_strdup(file);
	arguments = strmod(file_dup, ' ');
	token_dup = take_first_word(file_dup, ' ');
	path_to_file = add_path(token_dup);
	if (path_to_file == NULL)
	{
		if (arguments != NULL)
			free(arguments);
		free(token_dup);
		free(file_dup);
		return (1);
	}
	if (arguments != NULL)
	{
		command = add_strings(path_to_file, "", arguments);
		free(path_to_file);
		free(arguments);
		if (file_dup[0] != '/')
			free(token_dup);
		free(file_dup);
	}
	if (arguments == NULL)
	{
		command = custom_strdup(path_to_file);
		free(path_to_file);
		if (file_dup[0] != '/')
			free(token_dup);
		free(file_dup);
	}
	/*Count the number of tokens in the string*/
	num_of_args = is_space(command);
	num_of_args++;
	/*Allocate memory for an array of strings*/
	(*args) = (char **)malloc(sizeof(char *) * (1 + num_of_args));
	if (*args == NULL)
		return (1);
	/*Populate the array with tokenized strings*/
	token = strtok(command, " \n\t\r");
	while (token != NULL)
	{
		(*args)[i] = custom_strdup(token);
		token = strtok(NULL, " \n\t\r");
		i++;
	}
	(*args)[i] = NULL;
	free(command);
	return (0);
}

/**
 * free_double_pointer - frees the strings in an array of strings
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
 * add_path - adds path environment variable to input and checks if file exists
 * @file: File
 * Return: A string containing the full path to file on Sucess
 * Returns NULL on error
 */
char *add_path(char *file)
{
	char *environ = getenv("PATH"), *environ_dup = NULL;
	char *token = NULL, *full_path = NULL, *file_dup = NULL;
	struct stat file_info;

	if (file[0] == '/')
	{
		if (stat(file, &file_info) == 0)
			return (file);
		else
			return (NULL);
	}
	file_dup = custom_strdup(file);
	environ_dup = custom_strdup(environ);
	token = strtok(environ_dup, ":");
	while (token != NULL)
	{
		full_path = add_strings(token, "/", file_dup);
		if (full_path == NULL)
		{
			free(environ_dup);
			free(file_dup);
		}
		if (stat(full_path, &file_info) == 0)
		{
			free(file_dup);
			free(environ_dup);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(environ_dup);
	free(file_dup);
	return (NULL);
}

/**
 * print_env - prints all environment variables
 * Return: Nothing
 */
void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
