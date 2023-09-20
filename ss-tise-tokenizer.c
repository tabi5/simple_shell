#include "ss-tise-shell.h"
/**
 * strtow - A function that splits a string into words.
 * @varst: The string to be split.
 * @r: The delimiter to split the string on.
 * Return: A pointer to an array of strings (words).
 * Each word is null-terminated.
 * Returns NULL if varst is NULL or empty, or if the function
 * fails to allocate memory.
 */
char **strtow(char *varst, char *r)
{
	int t, i, b, q, varintnumwords = 0;
	char **p;
	char *temp = varst;

	if (temp == NULL || temp[0] == 0)
		return (NULL);
	if (!r)
		r = " ";
	for (t = 0; temp[t] != '\0'; t++)
		if (!is_delim(temp[t], r) && (is_delim(temp[t + 1], r) || !temp[t + 1]))
			varintnumwords++;

	if (varintnumwords == 0)
		return (NULL);
	p = malloc((1 + varintnumwords) * sizeof(char *));
	if (!p)
		return (NULL);
	for (t = 0, i = 0; i < varintnumwords; i++)
	{
		while (is_delim(temp[t], r))
			t++;
		b = 0;
		while (!is_delim(temp[t + b], r) && temp[t + b])
			b++;
		p[i] = malloc((b + 1) * sizeof(char));
		if (!p[i])
		{
			for (b = 0; b < i; b++)
				free(p[b]);
			free(p);
			return (NULL);
		}
		for (q = 0; q < b; q++)
			p[i][q] = temp[t++];
		p[i][q] = 0;
	}
	p[i] = NULL;
	return (p);
}
/**
 * strtow2 - A function that splits a string into words.
 * @varstr: The string to be split.
 * @chd: The delimiter to split the string on.
 * Return: A pointer to an array of strings (words).
 * Each word is null-terminated.
 * Returns NULL if varstr is NULL or empty,
 * or if the function fails to allocate memory.
 */
char **strtow2(char *varstr, char chd)
{
	int o, i, j, n, intnumwords = 0;
	char **t;
	char *temp = varstr;

	if (temp == NULL || temp[0] == 0)
		return (NULL);
	for (o = 0; temp[o] != '\0'; o++)
		if ((temp[o] != chd && temp[o + 1] == chd) ||
				(temp[o] != chd && !temp[o + 1]) || temp[o + 1] == chd)
			intnumwords++;
	if (intnumwords == 0)
		return (NULL);
	t = malloc((1 + intnumwords) * sizeof(char *));
	if (!t)
		return (NULL);
	for (o = 0, i = 0; i < intnumwords; i++)
	{
		while (temp[o] == chd && temp[o] != chd)
			o++;
		j = 0;
		while (temp[o + j] != chd && temp[o + j] && temp[o + j] != chd)
			j++;
		t[i] = malloc((j + 1) * sizeof(char));
		if (!t[i])
		{
			for (j = 0; j < i; j++)
				free(t[j]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < j; n++)
			t[i][n] = temp[o++];
		t[i][n] = 0;
	}
	t[i] = NULL;
	return (t);
}

