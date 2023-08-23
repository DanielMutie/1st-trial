#include "shell.h"

/**
 * buffer_input - buffers multiple commands in a chain
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_len: address of length of buffer
 *
 * Return: number of bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *buffer_len)
{
	ssize_t bytes_read = 0;
	size_t buffer_position = 0;

	if (!*buffer_len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, buffer_len, stdin);
#else
		bytes_read = _getline(info, buffer, buffer_len);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* Check if it's a command chain */
			{
				*buffer_len = bytes_read;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - gets a line of input without newline
 * @info: parameter struct
 *
 * Return: number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* command chain buffer */
	static size_t position, j, buffer_len;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_input(info, &buffer, &buffer_len);
	if (bytes_read == -1)
		return (-1);
	if (buffer_len)
	{
		j = position;
		p = buffer + position;

		check_chain(info, buffer, &j, position, buffer_len);
		while (j < buffer_len)
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		position = j + 1;
		if (position >= buffer_len)
		{
			position = buffer_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_ptr = p;
		return (_strlen(p));
	}

	*buffer_ptr = buffer;
	return (bytes_read);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);
	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return (bytes_read);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t position, len;
	size_t k;
	ssize_t bytes_read = 0, bytes_returned = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		bytes_returned = *length;
	if (position == len)
		position = len = 0;

	bytes_read = read_buffer(info, buffer, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + position, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, bytes_returned, bytes_returned ? bytes_returned + k : k + 1);
	if (!new_p)
		return (p ? (free(p), -1) : -1);

	if (bytes_returned)
		_strncat(new_p, buffer + position, k - position);
	else
		_strncpy(new_p, buffer + position, k - position + 1);

	bytes_returned += k - position;
	position = k;
	p = new_p;

	if (length)
		*length = bytes_returned;
	*ptr = p;
	return (bytes_returned);
}

/**
 * sigintHandler - handles SIGINT (Ctrl+C)
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

