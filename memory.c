#include "shell.h"

/**
 * release_memory - deallocates memory and sets the pointer to NULL
 * @pointer: address of the pointer to deallocate
 *
 * Return: 1 if memory was released, else 0
 */
int release_memory(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

