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
	int characters = 0, start_reading = 0;
	while (input[i] != '\0')
	{
		if (input[i] != limit)
			characters++;
		if (input[i] == limit && characters > 0)
			break;
		if (input[i] == limit && characters == 0)
			start_reading++;
		i++;
	}

	output = (char *)malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (NULL);
	for (; j < characters; j++, start_reading++)
		output[j] = input[start_reading];
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
	int characters = 0, spaces = 0, remove_spaces = 0;

	if (first_string == NULL || second_string == NULL)
		return (-1);

	while (first_string[i] != '\0')
	{
		if (first_string[i] != ' ' && first_string[i] != '\n'
				&& first_string[i] != '\t')
			characters++;
		if ((first_string[i] == ' ' || first_string[i] == '\n' ||
					first_string[i] == '\t') && characters > 0)
			spaces++;
		if ((first_string[i] == ' ' || first_string[i] == '\n' ||
					first_string[i] == '\t') && characters == 0)
			remove_spaces++;
		i++;
	}
	i = 0;
	while (first_string[remove_spaces] != '\0')
	{
		if (first_string[remove_spaces] == second_string[i])
			same++;
		i++;
		remove_spaces++;
	}
	if (i != same)
		return (0);
	return (1);
}
