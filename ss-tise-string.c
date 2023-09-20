#include "ss-tise-shell.h"
/**
 * _strlen - Calculates the length of a string.
 *
 *@varchs: The string whose length is to be calculated.
 *
 * Return: the length of the string.
 * If the string is NULL, returns 0.
 */

int _strlen(char *varchs)
{
	int e = 0;
	char *temp = varchs;

	if (!temp)
		return (0);

	while (*temp)
	{
		e++;
		temp++;
	}
	return (e);
}

/**
 *_strcmp - Compares two strings character by character.
 *
 * @varchs1: The first string to be compared.
 * @varchs2: The second string to be compared.
 *
 * Return:0 if the strings are identical.
 * If the strings are not identical,
 *            returns a positive value if the first
 * non-matching character in 'varchs1'
 *            is greater than the one in 'varchs2',
 *  and a negative value otherwise.
 */
int _strcmp(char *varchs1, char *varchs2)
{
	char *ptr1 = varchs1;
	char *ptr2 = varchs2;

	while (*ptr1 && *ptr2)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
	}
	if (*ptr1 == *ptr2)
		return (0);
	else
		return (*ptr1 < *ptr2 ? -1 : 1);
}
/**
 * starts_with - Checks if a string 'varhaystack'
 *  starts with another string 'varneedle'.
 *
 * @varhaystack: The string to be checked.
 * @varneedle: The prefix string.
 *
 * Return: Returns a pointer to the part of 'varhaystack'
 * after 'varneedle' if 'varhaystack' starts with 'varneedle',
 *            otherwise returns NULL.
 */

char *starts_with(const char *varhaystack, const char *varneedle)
{
	const char *h = varhaystack;
	const char *n = varneedle;

	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}
/**
 * _strcat - Concatenates the string pointed to by 'varchsrc'
 *   to the end of the string pointed to by 'varchdest'.
 *
 * @varchdest: The destination string. This string should
 *   have enough space to accommodate the concatenated result.
 * @varchsrc: The source string. This string will be
 * appended to the end of 'varchdest'.
 *
 * Return: Returns a pointer to the destination string 'varchdest'.
 */

char *_strcat(char *varchdest, char *varchsrc)
{
	char *varchret = varchdest;
	char *d = varchdest;
	char *s = varchsrc;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = '\0';
	return (varchret);
}


