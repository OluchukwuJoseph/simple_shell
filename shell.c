#include "shell.h"

int main(__attribute__((unused))int ac, char **av, char **environ)
{
	char *command = NULL, **args = NULL;
	size_t len, command_counter = 1;
	ssize_t command_length = 0;
	struct stat command_info;
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
		if (tokenize(command, &args) == -1)
		{
			printf("Memory Allocation failed\n");
			command_counter++;
			continue;
		}
		if (stat(args[0], &command_info) != 0)
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
			free(args[0]);
			free(args);
			continue;
		}
		free(args[0]);
		free(args);
		if (is_terminal == 1)
			break;
		command_counter++;

	}
	if (command != NULL)
		free(command);
	return (0);
}
