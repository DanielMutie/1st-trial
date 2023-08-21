#include "shell.h"

/**
 * convert_string_to_integer - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: The converted number, or -1 on error
 */
int convert_string_to_integer(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * print_error_message - Prints an error message
 * @info: The parameter and return info struct
 * @error_type: String containing specified error type
 *
 * Return: Nothing
 */
void print_error_message(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*custom_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;

	if (input < 0)
	{
		absolute_value = -input;
		custom_putchar('-');
		count++;
	}
	else
		absolute_value = input;

	current = absolute_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string in the specified base
 * @number: The number to be converted
 * @base: The base for conversion
 * @flags: Argument flags
 *
 * Return: The resulting string
 */
char *convert_to_string(long int number, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long num = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		num = -number;
		sign = '-';
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = digits[num % base];
		num /= base;
	} while (num != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_first_comment - Replaces the first '#' with '\0'
 * @buffer: Address of the string to modify
 *
 * Return: Always 0
 */
void remove_first_comment(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}

