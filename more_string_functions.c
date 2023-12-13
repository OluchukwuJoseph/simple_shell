#include "shell.h"

/**
 * take_first_word - Take first word from a string
 * The first word is the characters before limit
 * @input: String
 * @limit: Character to look out for
 * Return: First word on sucess
 * NULL on Failure (Insufficient Memory)
 */
char *take_first_word(char *input, char limit)
{
	char *output = NULL;
	int i = 0, j = 0;

	while (input[i] != '\0')
	{
		if (input[i] == limit)
			break;
		i++;
	}

	output = (char *)malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (NULL);
	for (; j < i; j++)
		output[j] = input[j];
	output[j] = '\0';

	return (output);
}

/**
 * compare_strings - compares strings to see if they are the same
 * @first_string: First string
 * @second_string: Second string
 * Return: 1 if strings length and content are the same
 * -1 if any argument is NULL
 *  0 if string length are the same but the content is not
 */
int compare_strings(char *first_string, char *second_string)
{
	int i = 0, same = 0;

	if (first_string == NULL || second_string == NULL)
		return (-1);
	if (_strlen(first_string) != _strlen(second_string))
		return (0);

	while (first_string[i] != '\0')
	{
		if (first_string[i] == second_string[i])
			same++;
		i++;
	}
	if (i != same)
		return (0);
	return (1);
}
