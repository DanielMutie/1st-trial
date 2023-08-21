#include "shell.h"

/**
 * is_command_separator - checks if the current character in the buffer
 * is a command separator
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of current position in buf
 *
 * Return: 1 if command separator, 0 otherwise
 */
int is_command_separator(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_separator_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_separator_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_separator_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_command_separator - checks whether to continue chaining based on
 * the last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_command_separator(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_separator_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_separator_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias_var - replaces aliases and variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias_var(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_alias(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = get_string_after(node->str, '=');
		if (!p)
			return (0);
		p = string_duplicate(p);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_variables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				string_duplicate(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				string_duplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_var(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				string_duplicate(get_string_after(node->str, '=')));
			continue;
		}
		replace_string(&info->argv[i], string_duplicate(""));

	}
	return (0);
}

/**
 * replace_string_value - replaces the value of a string
 * @old: address of the old string
 * @new: new string value
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string_value(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

