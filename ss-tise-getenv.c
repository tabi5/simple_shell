#include "ss-tise-shell.h"

/**
 * get_environ - Gets the environment variables for the
 * given var_info_t struct..
 * @info: A pointer to the var_info_t struct
 * Return: A pointer to an array of strings containing the
 * environment variables for the given var_info_t struct.
 */
char **get_environ(var_info_t *info)
{
	int is_environ_null_or_changed = (!info->environ || info->env_changed);

	if (is_environ_null_or_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
/**
 * _unsetenv - Unsets the environment variable specified
 * by the chvar string from the info struct.
 * @info: A pointer to the var_info_t struct.
 * the Structure containing potential arguments.
 *       Used to maintain constant function prototype.
 * @chvar: A string containing the name of
 * the environment variable to unset..
 * Return: 1 if the environment variable was unset
 * successfully, 0 otherwise..
 */
int _unsetenv(var_info_t *info, char *chvar)
{
	var_list_t *node = info->env;
	int is_start_with_chvar;
	size_t t = 0;
	char *h;
	int is_node_or_chvar_null = (!node || !chvar);

	if (is_node_or_chvar_null)
	{
		return (0);
	}

	while (node)
	{
		h = starts_with(node->str, chvar);
		is_start_with_chvar = (h && *h == '=');
		if (is_start_with_chvar)
		{
			info->env_changed = delete_node_at_index(&(info->env), t);
			t = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		t++;
	}

	return (info->env_changed);
}
/**
 * _setenv - Sets the environment variable specified by
 * the cvr string and chval string in the info struct.
 * @info: the Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 * @cvr: A string containing the name of the environment
 * variable to set.
 * @chval:A string containing the value of the
 * environment variable to set.
 *  Return: 0 on success, 1 on failure..
 */
int _setenv(var_info_t *info, char *cvr, char *chval)
{
	char *buf = NULL;
	var_list_t *node;
	char *varchp;
	int zer_ = 0;
	int sec_ = 1;
	int is_cvr_or_chval_null;
	int is_start_with_cvr;

	is_cvr_or_chval_null = (!cvr || !chval);
	if (is_cvr_or_chval_null)
	{
		return (zer_);
	}
	buf = malloc(_strlen(cvr) + _strlen(chval) + 2);
	if (!buf)
	{
		return (sec_);
	}
	_strcpy(buf, cvr);
	_strcat(buf, "=");
	_strcat(buf, chval);
	node = info->env;
	while (node)
	{
		varchp = starts_with(node->str, cvr);
		is_start_with_cvr = (varchp && *varchp == '=');

		if (is_start_with_cvr)
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (zer_);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, zer_);
	free(buf);
	info->env_changed = 1;
	return (zer_);
}
