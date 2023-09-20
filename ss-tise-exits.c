#include "ss-tise-shell.h"

/**
 * _strncpy - the func copies a string.
 *@varldt: the destination string will be copied to.
 *@chs: a source string.
 *@varm: thecount of characters to be copied.
 *Return: return the concatenated string
 */
char *_strncpy(char *varldt, char *chs, int varm)
{
	int vari = 0;
	int varb;
	char *varchar_s = varldt;
	char current_char;

	while ((current_char = chs[vari]) != '\0' && vari < varm - 1)
	{
		varldt[vari] = current_char;
		vari++;
	}
	if (vari < varm)
	{
		varb = vari;
		while (varb < varm)
		{
			varldt[varb] = '\0';
			varb++;
		}
	}

	return (varchar_s);
}
/**
 **_strncat - func concatenates two strings.
 *@vardest: the first var string.
 *@src_ch: the second var string.
 *@m: a amount of bytes to be maximally used.
 *Return: return the concatenated string.
 */
char *_strncat(char *vardest, char *src_ch, int m)
{
	int var_int_v = 0;
	int var_j = 0;
	char *vars = vardest;
	char current_char;

	while ((current_char = vardest[var_int_v]) != '\0')
	{
		var_int_v++;
	}
	while ((current_char = src_ch[var_j]) != '\0' && var_j < m)
	{
		vardest[var_int_v] = current_char;
		var_int_v++;
		var_j++;
	}
	if (var_j < m)
	{
		vardest[var_int_v] = '\0';
	}

	return (vars);
}

/**
 **_strchr - the locates a character in a string.
 *@vars: a string to be parsed.
 *@varc: a character to look for.
 *Return: return(vars) a pointer to the memory area vars
 */
char *_strchr(char *vars, char varc)
{
	char *current_char = vars;

	do {
		if (*current_char == varc)
		{
			return (current_char);
		}
	} while (*current_char++ != '\0');

	return (NULL);
}
