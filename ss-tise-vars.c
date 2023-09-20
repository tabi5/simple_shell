#include "ss-tise-shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * is_chain - A function that checks if a command chain
 * exists in a buffer.
 * @info: A pointer to a var_info_t structure.
 * @varchbuf: The buffer to be checked.
 * @h: A pointer to the index in the buffer where the check starts.
 * Return: 1 if a command chain is found, 0 otherwise.
 */
int is_chain(var_info_t *info, char *varchbuf, size_t *h)
{
	size_t y = *h;
	char *temp = varchbuf;

	if (temp[y] == '|' && temp[y + 1] == '|')
	{
		temp[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (temp[y] == '&' && temp[y + 1] == '&')
	{
		temp[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (temp[y] == ';')
	{
		temp[y] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*h = y;
	return (1);
}

/**
 * check_chain - A function that checks the command chain
 * type and updates the buffer and index accordingly.
 * @info: A pointer to a var_info_t structure.
 * @vbuf: The buffer to be updated.
 * @d: A pointer to the index in the buffer where the update starts.
 * @t: The index in the buffer where the null character should be placed.
 * @iln: The new value for the index if the status of info is true.
 */
void check_chain(var_info_t *info, char *vbuf, size_t *d, size_t t, size_t iln)
{
	size_t k = *d;
	char *temp = vbuf;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			temp[t] = 0;
			k = iln;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			temp[t] = 0;
			k = iln;
		}
	}

	*d = k;
}
/**
 * replace_alias - A function that replaces an alias in
 * a command with its value.
 * @info: A pointer to a var_info_t structure.
 *
 * Return: 1 if an alias was replaced, 0 otherwise.
 */
int replace_alias(var_info_t *info)
{
	int u;
	var_list_t *node;
	char *k;
	char *temp = info->argv[0];

	for (u = 0; u < 10; u++)
	{
		node = node_starts_with(info->alias, temp, '=');
		if (!node)
			return (0);
		free(temp);
		k = _strchr(node->str, '=');
		if (!k)
			return (0);
		k = _strdup(k + 1);
		if (!k)
			return (0);
		temp = k;
	}
	info->argv[0] = temp;
	return (1);
}
/**
 * replace_vars - Replaces variables in command-line arguments
 * and other strings.
 *
 * @info: A pointer to a structure containing information
 * about the variables to be replaced.
 * 0 on success, or a negative error code on failure.
 *
 * This function iterates over the array of variable names
 *and values in the `info` structure, replacing each variable
 *with its corresponding value. If the variable is not found
 *in the environment, it is replaced with an empty string.
 *
 * The function also replaces the special variables `$?` and `$$`.
 *The variable `$?` is replaced with the exit status of
 *the previous command, and the variable `$$`
 *is replaced with the process ID of the current process.;
 * Return: return always 0.
 */
int replace_vars(var_info_t *info)
{
	int d = 0;
	var_list_t *node;

	for (d = 0; info->argv[d]; d++)
	{
		if (info->argv[d][0] != '$' || !info->argv[d][1])
			continue;

		if (!_strcmp(info->argv[d], "$?"))
		{
			replace_string(&(info->argv[d]),
			_strdup(convert_number(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[d], "$$"))
		{
			replace_string(&(info->argv[d]),
			_strdup(convert_number(getpid(), 10, 0)));
		}
		else
		{
			node = node_starts_with(info->env, &info->argv[d][1], '=');
			if (node)
			{
				replace_string(&(info->argv[d]),
				_strdup(_strchr(node->str, '=') + 1));
			}
		}
	}

	return (0);
}
/**
 * replace_string -Replaces the old string with the new string.
 * @varchrold: A pointer to a pointer to a character array.
 * This is the string that will be replaced.
 * @varchnew: A pointer to a character array.
 * This is the string that will replace the old string.
 * Return:1 if the replacement was successful, 0 otherwise.
 */
int replace_string(char **varchrold, char *varchnew)
{
	char *temp = varchnew;

	free(*varchrold);
	*varchrold = temp;
	return (1);
}

