#include "shell.h"

/**
 * is_executable - checks if a file is an executable command
 * @info: info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *path)
{
	struct stat file_stat;

	(void)info;
	if (!path || stat(path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates characters within a range
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * search_executable_in_path - searches for an executable in the PATH string
 * @info: info struct
 * @pathstr: the PATH string
 * @cmd: the command to search for
 *
 * Return: full path of command if found, otherwise NULL
 */
char *search_executable_in_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_characters(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

