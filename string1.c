#include "shell.h"

/**
 * string_copy - duplicates a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *string_copy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = 0;
	return (destination);
}

/**
 * string_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * display_string - prints a given string
 * @str: the string to be displayed
 *
 * Return: Nothing
 */
void display_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		display_character(str[index]);
		index++;
	}
}

/**
 * display_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int display_character(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[i++] = c;
	return (1);
}

