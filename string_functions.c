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

/**
 * add_strings - adds 3 strings together
 * @first: First string
 * @delim: Delimeter
 * @second: Second String
 * Return: New String
 */
char *add_strings(char *first, char *delim, char *second)
{
	int first_length = _strlen(first), second_length = _strlen(second);
	int delim_length = _strlen(delim), i = 0, j;
	int length = first_length + second_length + delim_length;
	char *output = NULL;

	if (first == NULL && second == NULL && delim == NULL)
		return (NULL);

	output = (char *)malloc(sizeof(char) * (length + 1));
	if (output == NULL)
		return (NULL);


	for (j = 0; j < first_length; i++, j++)
		output[i] = first[j];
	for (j = 0; j < delim_length; i++, j++)
		output[i] = delim[j];
	for (j = 0; j < second_length; i++,j++)
		output[i] = second[j];
	output[i] = '\0';
	return (output);
}

/**
 * strmod - Removes characters from a string till it finds limit
 * @input: String
 * @limit: Character to look out for
 * Return: New string on sucess
 * NULL on failure (Could not find limit, Insufficient Memory)
 */
char *strmod(char *input, char limit)
{
	int i = 0, delimiter = 0, j = 0;
	char *output = NULL;

	if (input == NULL)
		return (NULL);

	while (input[i] != '\0')
	{
		if (input[i] == limit)
		{
			delimiter = 1;
			break;
		}
		i++;
	}
	if (delimiter == 0)
		return (NULL);
	output = (char *)malloc(sizeof(char) * ((_strlen(input) - i) + 1));
	if (output == NULL)
		return (NULL);

	for (; input[i] != '\0'; j++, i++)
		output[j] = input[i];
	output[j] = '\0';
	return (output);
}
