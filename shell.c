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
	char *command = NULL, **args = NULL;
	size_t len, command_counter = 1;
	ssize_t command_length = 0;
	int is_terminal = 0;

	if (!isatty(fileno(stdin)))
		is_terminal = 1;
	while(1)
	{
		printf("# ");
		len = 0;
		command_length = getline(&command, &len, stdin);
		if (command_length == -1)
			break;
		command[command_length - 1] = '\0';
		if (is_space(command) == _strlen(command))
		{
			command_counter++;
			free(command);
			continue;
		}
		if (compare_strings(command, "env") == 1)
		{
			print_env();
			free(command);
			continue;
		}
		if (tokenize(command, &args) == -1)
		{
			printf("%s: %ld: %s not found\n", av[0], command_counter, command);
			command_counter++;
			free(command);
			continue;
		}
		if (execute(args, environ) == -1)
		{
			printf("%s: %ld: %s not found\n", av[0], command_counter, command);
			command_counter++;
			free(command);
			free_double_pointer(args);
			continue;
		}
		free(command);
		free_double_pointer(args);
		if (is_terminal == 1)
			break;
		command_counter++;
	}
	if (command != NULL)
		free(command);
	return (0);
}
