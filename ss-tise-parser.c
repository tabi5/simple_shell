#include "ss-tise-shell.h"
/**
 * is_cmd - Checks if the given file path points to a regular file.
 *
 * @info: A pointer to a var_info_t structure.
 *  This parameter is not used in the function.
 * @varfpath: The file path to be checked.
 *
 * Return: returns 1 if the file path points to
 *  a regular file, otherwise returns 0.
 */

int is_cmd(var_info_t *info, char *varfpath)
{
	struct stat varst;
	int result = 0;

	(void)info;
	if (varfpath && !stat(varfpath, &varst))
	{
		if (varst.st_mode & S_IFREG)
		{
			result = 1;
		}
	}

	return (result);
}
/**
 * dup_chars - Duplicates characters from a given string within
 * a specified range, excluding the colon character.
 *
 * @varpathstr: The string from which
 * characters are to be duplicated.
 * @varstart: The starting index from
 * where characters are to be duplicated.
 * @varstop: The ending index up to where
 * characters are to be duplicated.
 *
 * Return: Returns a pointer to the buffer containing
 *  the duplicated characters.
 */

char *dup_chars(char *varpathstr, int varstart, int varstop)
{
	static char buf[1024];
	int d = 0, p = 0;
	char current_char;

	for (p = 0, d = varstart; d < varstop; d++)
	{
		current_char = varpathstr[d];
		if (current_char != ':')
			buf[p++] = current_char;
	}
	buf[p] = '\0';
	return (buf);
}
/**
 * find_path - Finds the path of a given command in the system's PATH variable.
 *
 * @info: A pointer to a var_info_t structure.
 * This parameter is used in the is_cmd function.
 * @pathvar: The system's PATH variable.
 * @varcmd: The command whose path is to be found.
 *
 * Return: Returns a pointer to the path of the command if
 *  it is found, otherwise returns NULL.
 */

char *find_path(var_info_t *info, char *pathvar, char *varcmd)
{
	int k = 0, varintcurr_pos = 0;
	char *path;
	int cmd_length;

	cmd_length = _strlen(varcmd);

	if (!pathvar)
		return (NULL);
	if ((cmd_length > 2) && starts_with(varcmd, "./"))
	{
		if (is_cmd(info, varcmd))
			return (varcmd);
	}
	while (1)
	{
		if (!pathvar[k] || pathvar[k] == ':')
		{
			path = dup_chars(pathvar, varintcurr_pos, k);
			if (!*path)
				_strcat(path, varcmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, varcmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathvar[k])
				break;
			varintcurr_pos = k;
		}
		k++;
	}
	return (NULL);
}

