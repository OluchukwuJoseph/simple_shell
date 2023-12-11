#include "shell.h"

/**
 * is_space - counts space in a string
 * @input: string
 * Return: amount of space
 */
size_t is_space(char *input)
{
	size_t space = 0, i = 0;

	if (input == NULL)
		return (0);

	for (; input[i] != '\0'; i++)
	{
		if (input[i] == ' ')
			space++;
	}
	return (space);

}

/**
 * custom_strdup - duplicates a string
 * @input: string to be duplicated
 * Return: Duplicated string on sucess
 */
char *custom_strdup(char *input)
{
	size_t length = 0, i = 0;
	char *output = NULL;

	if (input == NULL)
		return (NULL);

	length = _strlen(input);
	output = (char *)malloc(sizeof(char) * (length + 1));
	if (output == NULL)
		return (NULL);

	for (; i < length; i++)
		output[i] = input[i];
	output[i] = '\0';
	return (output);
}

/**
 * _strlen - counts the characters in a string
 * @input: string to count
 * Return: Length of string
 */
size_t _strlen(char *input)
{
	size_t length = 0;

	while (input[length] != '\0')
		length++;
	return(length);
}
