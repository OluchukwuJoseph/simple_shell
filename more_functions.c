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
