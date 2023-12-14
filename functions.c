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
 * @file: The input command string to tokenize.
 * @args: A double pointer (array of strings)
 * Return: 0 on success, -1 on failure
*/
int tokenize(char *file, char ***args);
int tokenize(char *file, char ***args)
{
	char *token = NULL, *command = NULL, *arguments = NULL;
	char *file_dup = custom_strdup(file);
	char *token_dup = NULL, *path_to_file = NULL;
	int num_of_args = 0, i = 0;
	struct stat file_info;

	if (file_dup[0] == '/')
	{
		free(file_dup);
		command = custom_strdup(file);
	}
	else
	{
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
		return (0);
	/*Populate the array with tokenized strings*/
	token = strtok(command, " \n\t\r");
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
