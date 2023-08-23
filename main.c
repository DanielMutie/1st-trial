#include "shell.h"

/**
 * main - starting point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int ac, char **av)
{
	info_t info_array[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	if (ac == 2)
	{
		file_descriptor = open(av[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info_array->readfd = file_descriptor;
	}
	initialize_env_list(info_array);
	read_history(info_array);
	run_shell(info_array, av);
	return (EXIT_SUCCESS);
}

