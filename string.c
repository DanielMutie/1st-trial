#include "shell.h"

/**
 * _length - calculates the length of a string
 * @str: the string to calculate length
 *
 * Return: the length of the string
 */
int _length(char *str)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str++)
		count++;
	return (count);
}

/**
 * _compare_strings - performs a lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _compare_strings(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * is_prefix - checks if one string is a prefix of another
 * @str: the string to search
 * @prefix: the prefix to find
 *
 * Return: pointer to next character of str if found, otherwise NULL
 */
char *is_prefix(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _string_concat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_string_concat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (result);
}

