#include "shell.h"

/**
 * split_string - splits a string into words using delimiters
 * @input: the input string
 * @delimiters: the delimeter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *input, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **words;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (i = 0; input[i] != '\0'; i++)
		if (!is_delimiter(input[i], delimiters) &&
		    (is_delimiter(input[i + 1], delimiters) || !input[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(input[i], delimiters))
			i++;
		k = 0;
		while (!is_delimiter(input[i + k], delimiters) && input[i + k])
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = input[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;
	return (words);
}

/**
 * split_string_alt - splits a string into words using a single delimiter
 * @input: the input string
 * @delimiter: the delimiter character
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_alt(char *input, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **words;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	for (i = 0; input[i] != '\0'; i++)
		if ((input[i] != delimiter && input[i + 1] == delimiter) ||
		    (input[i] != delimiter && !input[i + 1]) || input[i + 1] == delimiter)
			num_words++;
	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input[i] == delimiter && input[i] != delimiter)
			i++;
		k = 0;
		while (input[i + k] != delimiter && input[i + k] && input[i + k] != delimiter)
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = input[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;
	return (words);
}

