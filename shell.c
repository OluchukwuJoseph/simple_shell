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
		printf("$ ");
		len = 0;
		command_length = getline(&command, &len, stdin);
		if (command_length == -1)
			break;
		command[command_length - 1] = '\0';
		if (stat(command, &command_info) != 0)
		{
			printf("%s: %ld: %s\n", av[0], command_counter, command);
			command_counter++;
			free(command);
			continue;
		}
		args = (char **)malloc(sizeof(char *) * 2);
		if (args == NULL)
		{
			free(command);
			break;
		}
		args[0] = command;
		args[1] = NULL;
		if (execute(args, environ) == -1)
		{
			printf("%s: %ld: %s\n", av[0], command_counter, command);
			command_counter++;
			free(args[0]);
			free(args);
			continue;
		}
		if (is_terminal == 1)
			break;
		command_counter++;
		free(args[0]);
		free(args);

	}
	free(args[0]);
	free(args);
	return (0);
}
