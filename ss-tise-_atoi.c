#include "ss-tise-shell.h"
/**
 * is_delim - Checks if a character is a delimiter.
 * @chr: the A character has been to check.
 * @chdelim: A string of delimiters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char chr, char *chdelim)
{
	for (; *chdelim; chdelim++)
	{
		if (*chdelim == chr)
			return (1);
	}
	return (0);
}
/**
 * interactive - Checks if the shell is interactive..
 * @info: A pointer to a var_info_t struct
 * containing information about the shell.
 *
 * Return: return 1 if the shell is interactive, 0 otherwise..
 */
int interactive(var_info_t *info)
{
	int is_interactive;

	is_interactive = isatty(STDIN_FILENO) && info->readfd <= 2;
	return (is_interactive);
}
/**
 * _isalpha - Checks if a character is alphabetic..
 * @chin: An integer representing the character.
 * Return: return 1 if the character is alphabetic,
 * 0 otherwise..
 */

int _isalpha(int chin)
{
	int cr = chin;
	int s = 1;
	int e = 0;

	if ((cr >= 'a' && cr <= 'z') || (cr >= 'A' && cr <= 'Z'))
		return (s);
	else
		return (e);
}
/**
 * _atoi - the func Converts a string to an integer.
 * @chs: A pointer to a string..
 * Return: return The integer value of the string,
 * or 0 if the string is not a valid integer.
 */
int _atoi(char *chs)
{
	int inti;
	int sign_int = 1;
	int flag_int = 0;
	int intoutput;
	unsigned int intresult = 0;

	for (inti = 0; chs[inti] != '\0' && flag_int != 2; inti++)
	{
		if (chs[inti] == '-')
			sign_int *= -1;

		if (chs[inti] >= '0' && chs[inti] <= '9')
		{
			flag_int = 1;
			intresult = intresult * 10 + (chs[inti] - '0');
		}
		else if (flag_int == 1)
			flag_int = 2;
	}

	intoutput = sign_int == -1 ? -intresult : intresult;

	return (intoutput);
}

