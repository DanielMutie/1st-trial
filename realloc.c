#include "shell.h"

/**
 **_set_bytes - fills memory with a specified byte
 *@mem: the pointer to the memory area
 *@byte: the byte to fill *mem with
 *@size: the number of bytes to be filled
 *Return: (mem) a pointer to the memory area mem
 */
char *_set_bytes(char *mem, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		mem[i] = byte;
	return (mem);
}

/**
 * free_strings - releases memory allocated for an array of strings
 * @str_array: array of strings
 */
void free_strings(char **str_array)
{
	char **current_ptr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(current_ptr);
}

/**
 * _resize_memory - resizes a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the resized memory block
 */
void *_resize_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

