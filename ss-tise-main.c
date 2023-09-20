#include "ss-tise-shell.h"
/**
 * main - Executes the main program.
 * @varac: The count of command line arguments.
 * @chav: The array of command line arguments.
 *
 * Return: Returns the exit code of the program.
 *            EXIT_SUCCESS if the program executed successfully,
 *            otherwise returns an error code.
 */

int main(int varac, char **chav)
{
	var_info_t info[] = { INFO_INIT };
	int varintfd = 2;
	int exit_code = EXIT_SUCCESS;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (varintfd)
			: "r" (varintfd));

	if (varac == 2)
	{
		varintfd = open(chav[1], O_RDONLY);
		if (varintfd == -1)
		{
			if (errno == EACCES)
				exit_code = 126;
			else if (errno == ENOENT)
			{
				_eputs(chav[0]);
				_eputs(": 0: Can't open ");
				_eputs(chav[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit_code = 127;
			}
			else
				exit_code = EXIT_FAILURE;

			return (exit_code);
		}
		info->readfd = varintfd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, chav);
	return (exit_code);
}

