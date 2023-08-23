#include "shell.h"

/**
 * display_command_history - displays the command history with line numbers
 * @info: Parameter struct. Used to maintain function prototype.
 *
 * Return: Always 0
 */
int display_command_history(info_t *info)
{
	print_list_str(info->history);
	return (0);
}

/**
 * remove_alias - removes an alias
 * @info: Parameter struct.
 * @alias_str: the alias string to remove
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *alias_str)
{
	char *p, c;
	int ret;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*p = c;
	return (ret);
}

/**
 * add_alias - adds an alias
 * @info: Parameter struct.
 * @alias_str: the alias string to add
 *
 * Return: Always 0 on success, 1 on error
 */
int add_alias(info_t *info, char *alias_str)
{
	char *p;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info, alias_str));

	remove_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_single_alias - prints a single alias
 * @alias_node: the alias node to print
 *
 * Return: Always 0 on success, 1 on error
 */
int print_single_alias(list_t *alias_node)
{
	char *p = NULL, *alias = NULL;

	if (alias_node)
	{
		p = _strchr(alias_node->str, '=');
		for (alias = alias_node->str; alias <= p; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_aliases - manages aliases similar to the alias builtin
 * @info: Parameter struct.
 *
 * Return: Always 0
 */
int manage_aliases(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_single_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			add_alias(info, info->argv[i]);
		else
			print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

