#include "shell.h"

/**
 * count_items - counts the number of items in a linked list
 * @list: pointer to the first node
 *
 * Return: the number of items in the list
 */
size_t count_items(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

/**
 * convert_list_to_strings - converts a linked list to an array of strings
 * @start: pointer to the first node
 *
 * Return: an array of strings
 */
char **convert_list_to_strings(list_t *start)
{
	list_t *node = start;
	size_t count = count_items(start), i;
	char **strings;
	char *str;

	if (!start || !count)
		return (NULL);

	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * display_list - prints all elements of a linked list
 * @start: pointer to the first node
 *
 * Return: the number of nodes in the list
 */
size_t display_list(const list_t *start)
{
	size_t count = 0;

	while (start)
	{
		_puts(convert_number(start->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(start->str ? start->str : "(nil)");
		_puts("\n");
		start = start->next;
		count++;
	}
	return (count);
}

/**
 * find_node_with_prefix - finds a node whose string starts with the given prefix
 * @node: pointer to the head of the list
 * @prefix: the prefix to match
 * @next_char: the next character after the prefix to match
 *
 * Return: the matching node or NULL
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char next_char)
{
	char *position = NULL;

	while (node)
	{
		position = starts_with(node->str, prefix);
		if (position && ((next_char == -1) || (*position == next_char)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_position - gets the position of a node within a linked list
 * @head: pointer to the head of the list
 * @node: pointer to the node
 *
 * Return: the index of the node or -1 if not found
 */
ssize_t get_node_position(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

