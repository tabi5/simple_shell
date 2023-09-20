#include "ss-tise-shell.h"
#include <string.h>
/**
 * _eputs - Prints a string to the standard error stream.
 * @str: A pointer to the string to print..
 *
 * Return:
 *   None.
 */
void _eputs(char *str)
{
	int i = 0, str_length;

	if (!str)
		return;
	str_length = strlen(str);
	while (i < str_length)
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - Writes a character to the standard error stream.
 * @varc: The character to write.
 *
 * Return: 1 on success, -1 on failure.
 * On the error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char varc)
{
	static int int_y;
	int s = 1;
	int z = 0;
	static char buf[WRITE_BUF_SIZE];
	int write_status;

	if (varc == BUF_FLUSH || int_y >= WRITE_BUF_SIZE)
	{
		write_status = write(2, buf, int_y);
		if (write_status < 0)
			return (-1);
		int_y = z;
	}
	if (varc != BUF_FLUSH)
		buf[int_y++] = varc;
	return (s);
}
/**
 * _putfd - Writes a character to the specified file descriptor.
 * @c: The character to write.
 * @fd: The file descriptor to write to..
 *
 * Return: 1 on success, -1 on failure..
 * On the error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	int var_int_k = 0;
	int z = 0;
	int one_ = 1;
	static char buf[WRITE_BUF_SIZE];
	int is_flush_or_full = (c == BUF_FLUSH || var_int_k >= WRITE_BUF_SIZE);

	if (is_flush_or_full)
	{
		write(fd, buf, var_int_k);
		var_int_k = z;
	}

	if (c != BUF_FLUSH)
	{
		buf[var_int_k] = c;
		var_int_k++;
	}

	return (one_);
}
/**
 * _putsfd - Writes a string to the specified file descriptor.
 * @str: The string to write.
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written, or 0 on failure.
 */
int _putsfd(char *str, int fd)
{
	int var_int_h = 0;
	int z = 0;
	char *current_char = str;

	if (!str)
	{
		return (z);
	}

	while (*current_char)
	{
		var_int_h += _putfd(*current_char, fd);
		current_char++;
	}

	return (var_int_h);
}

