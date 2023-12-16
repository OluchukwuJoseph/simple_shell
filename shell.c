#include "shell.h"

/**
 * main - Takes input from the command line and execute them
 * @ac: Amount of argument passed
 * @av: Array containing arguments passed
 * @environ: List of enviroment variables
 * Return: 0 on sucess
 */
int main(__attribute__((unused))int ac, char **av, char **environ);
int main(__attribute__((unused))int ac, char **av, char **environ)
{
	char *command = NULL, **args = NULL, *exit_call = NULL;
	char *exit_argument = NULL;
	size_t len, command_counter = 1;
	ssize_t command_length = 0;
	int exit_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		len = 0;
		command_length = custom_getline(&command, &len, stdin);
		if (command_length == -1)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		command[command_length - 1] = '\0';
		if (is_space(command) == _strlen(command))
		{
			command_counter++;
			free(command);
			command = NULL;
			exit_status = 0;
			continue;
		}
		if (compare_strings(command, "exit") == 1)
		{
			free(command);
			exit(exit_status);
		}
		exit_call = take_first_word(command, ' ');
		if (compare_strings(exit_call, "exit") == 1)
		{
			exit_argument = strmod(command, ' ');
			exit_status = custom_exit(exit_argument);
			if (exit_status == -1)
			{
				printf("%s: %ld: %s: Illegal number:%s\n", 
			av[0], command_counter, exit_call, exit_argument);
				command_counter++;
				free(exit_argument);
				free(exit_call);
				exit_call = NULL;
				free(command);
				command = NULL;
				exit_status = 2;
				continue;
			}
			free(exit_argument);
			free(exit_call);
			free(command);
			exit(exit_status);
		}
		if (exit_call != NULL)
			free(exit_call);
		if (tokenize(command, &args) == 1)
		{
			printf("%s: %ld: %s not found\n", av[0], command_counter, command);
			command_counter++;
			free(command);
			command = NULL;
			exit_status = 2;
			continue;
		}
		if (execute(args, environ) == 1)
		{
			command_counter++;
			free(command);
			command = NULL;
			free_double_pointer(args);
			args = NULL;
			exit_status = 2;
			continue;
		}
		free(command);
		command = NULL;
		free_double_pointer(args);
		command_counter++;
		exit_status = 0;
	}
	return (0);
}

/**
 * custom_getline - reads an entire line from stream
 * @lineptr: buffer to write to
 * @len: length of buffer
 * @stream: File descriptor to take input from
 * Return: Number of characters read on success
 * -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *len, FILE *stream)
{
	size_t i = 0;
	char character;

	if (!stream)
		return (-1);

	if (*lineptr == NULL || len == 0)
	{
		*len = 1024;
		*lineptr = (char *)malloc(sizeof(char) * (*len));
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		character = fgetc(stream);
		if (character == EOF || character == '\n')
			break;
		(*lineptr)[i] = character;
		i++;
		if (i >= *len)
		{
			*len = i * 2;
			*lineptr = (char *)realloc(*lineptr, *len);
			if (*lineptr == NULL)
				return (-1);
		}
	}
	if (i == 0)
		return (-1);
	(*lineptr)[i] = '\0';
	return ((ssize_t)i + 1);
}
