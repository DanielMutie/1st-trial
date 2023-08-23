#include "shell.h"

/**
 * copy_string - copies a string with a specified length
 * @destination: the destination string
 * @source: the source string
 * @length: the maximum number of characters to copy
 *
 * Return: pointer to the destination string
 */
char *copy_string(char *destination, char *source, int length)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < length - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < length)
	{
		j = i;
		while (j < length)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * concatenate_strings - concatenates two strings with a specified length
 * @destination: the destination string
 * @source: the source string
 * @length: the maximum number of bytes to use
 *
 * Return: pointer to the destination string
 */
char *concatenate_strings(char *destination, char *source, int length)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < length)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < length)
		destination[i] = '\0';
	return (result);
}

/**
 * find_character - finds the first occurrence of a character in a string
 * @string: the string to search
 * @character: the character to find
 *
 * Return: pointer to the first occurrence of the character in the string, or NULL if not found
 */
char *find_character(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

