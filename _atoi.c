#include "shell.h"

/**
 * detectInteractive - Determines if the shell is in interactive mode
 * @info: Pointer to struct containing information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int detectInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->fileDescRead <= 2);
}

/**
 * isDelimiter - Checks if a character is a delimiter
 * @character: The character to check
 * @delimiterSet: The set of delimiters
 *
 * Return: 1 if character is a delimiter, 0 otherwise
 */
int isDelimiter(char character, char *delimiterSet)
{
	while (*delimiterSet)
	{
		if (*delimiterSet++ == character)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * isAlphabetic - Checks if a character is alphabetic
 * @character: The character to check
 *
 * Return: 1 if character is alphabetic, 0 otherwise
 */
int isAlphabetic(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
	{
		return (1);
	}
	return (0);
}

/**
 * stringToInteger - Converts a string to an integer
 * @inputString: The string to convert
 *
 * Return: Converted integer, or 0 if no numbers in string
 */
int stringToInteger(char *inputString)
{
	int index, sign = 1, numFlag = 0, output;
	unsigned int result = 0;

	for (index = 0; inputString[index] != '\0' && numFlag != 2; index++)
	{
		if (inputString[index] == '-')
		{
			sign *= -1;
		}

		if (inputString[index] >= '0' && inputString[index] <= '9')
		{
			numFlag = 1;
			result *= 10;
			result += (inputString[index] - '0');
		}
		else if (numFlag == 1)
		{
			numFlag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}

