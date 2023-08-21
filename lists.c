#include "shell.h"

/**
 * insert_at_start - Insert a new node at the beginning of the list
 * @head: A pointer to the head of the list
 * @str: The string for the new node
 * @num: Index used for history
 *
 * Return: A pointer to the new head node
 */
list_t *insert_at_start(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * insert_at_end - Insert a new node at the end of the list
 * @head: A pointer to the head of the list
 * @str: The string for the new node
 * @num: Index used for history
 *
 * Return: A pointer to the new node
 */
list_t *insert_at_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current;

	if (!head)
		return (NULL);

	current = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_strings - Print the string element of each node
 * @head: A pointer to the head of the list
 *
 * Return: The number of nodes in the list
 */
size_t print_list_strings(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index - Delete a node at a given index
 * @head: A pointer to the head of the list
 * @index: The index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	current = *head;

	if (!index)
	{
		*head = current->next;
		free(current->str);
		free(current);
		return (1);
	}

	while (current)
	{
		if (i == index)
		{
			prev_node->next = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		i++;
		prev_node = current;
		current = current->next;
	}

	return (0);
}

/**
 * free_list_nodes - Free all nodes in the list
 * @head: A pointer to the head of the list
 *
 * Return: void
 */
void free_list_nodes(list_t **head)
{
	list_t *current, *next_node;

	if (!head || !*head)
		return;

	current = *head;

	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}

	*head = NULL;
}

