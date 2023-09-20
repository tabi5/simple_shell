#include "ss-tise-shell.h"

/**
 * _strcpy -Copies the string pointed to by 'varchsrc', including the null
 * character, to the buffer pointed to by 'varchdest'.
 *
 * @varchdest: The destination buffer where the content is to be copied.
 * @varchsrc: The source string to be copied.
 *
 * Return: Returns a pointer to the destination string 'varchdest'.
 */
char *_strcpy(char *varchdest, char *varchsrc)
{
	char *d = varchdest;
	char *s = varchsrc;

	if (d == s || s == NULL)
		return (d);
	while (*s)
	{
		*d++ = *s++;
	}
	*d = '\0';
	return (varchdest);
}

/**
 * _strdup - a function that duplicates a string
 * @varchstr: the string to be duplicated
 *
 * Return: a pointer to the duplicated string or NULL
 * if insufficient memory was available
 */
char *_strdup(const char *varchstr)
{
	int length = 0, i = 0;
	char *varchret;
	const char *temp = varchstr;

	if (temp == NULL)
		return (NULL);
	while (*temp++)
		length++;
	varchret = malloc(sizeof(char) * (length + 1));
	if (!varchret)
		return (NULL);
	temp = varchstr;
	for (i = 0; i < length; i++)
		varchret[i] = temp[i];
	varchret[length] = '\0';
	return (varchret);
}

/**
 * _puts - a function that prints a string,
 * followed by a new line, to stdout
 * @varchstr: the string to be printed
 *
 * Return: void
 */
void _puts(char *varchstr)
{
	char *temp = varchstr;

	if (!temp)
		return;
	while (*temp != '\0')
	{
		_putchar(*temp);
		temp++;
	}
}

/**
 * _putchar - A function that writes the
 * character varchc to stdout.
 * @varchc: The character to print.
 *
 * This function uses a buffer to group the characters, and writes them
 * to stdout when the buffer is full or when it
 * is explicitly asked to flush (varchc == BUF_FLUSH).
 *
 * Return: On success, the function returns 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char varchc)
{
	static int q;
	static char buf[WRITE_BUF_SIZE];
	char *temp = buf;

	if (varchc == BUF_FLUSH || q >= WRITE_BUF_SIZE)
	{
		write(1, temp, q);
		q = 0;
	}
	if (varchc != BUF_FLUSH)
		temp[q++] = varchc;
	return (1);
}

