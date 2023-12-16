#include "shell.h"

/**
 * _getcwd - gets the current working directory
 * Return: Nothing
 */
char *_getcwd(void)
{
	int cwd_size = 1024;
	char *cwd = NULL;

	cwd = (char *)malloc(sizeof(char) * (cwd_size + 1));
	if (cwd == NULL)
	{
		perror("Malloc failed\n");
		return (NULL);
	}

	while (getcwd(cwd, cwd_size) == NULL)
	{
		if (errno == ERANGE)
		{
			cwd_size *= 2;
			cwd = (char *)malloc(sizeof(char) * (cwd_size + 1));
			if (cwd == NULL)
			{
				perror("Malloc failed\n");
				return (NULL);
			}
		}
		else
		{
			perror("getcwd failed\n");
			break;
		}
	}
	return (cwd);
}

/**
 * custom_exit - returns a exit status
 * @input: exit status in string
 * Return: Exit status on success
 * -1 on failure
 */
int custom_exit(char *input)
{
	int i = 0, numbers = 0, exit_status = 0, characters = 0;
	char character;

	character = input[0]; 
	input[0] = '0';
	while (input[i] != '\0')
	{
		if (input[i] >= 0 && input[i] <= '9')
			numbers++;
		if (!(input[i] >= '0' && input[i] <= '9'))
			characters++;
		i++;
	}

	if (characters > 0)
	{
		input[0] = character;
		return (-1);
	}
	i = 0;
	while (i < numbers)
	{
		exit_status = exit_status * 10 + (input[i] - '0');
		i++;
	}
	return (exit_status);
}
