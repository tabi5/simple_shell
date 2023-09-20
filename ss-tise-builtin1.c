#include "ss-tise-shell.h"

/**
 * _myhistory - Prints the history list to the console.
 * @info: A pointer to a var_info_t struct
 * containing information about the history list.
 *  Return: returnAlways 0.
 */
int _myhistory(var_info_t *info)
{
	int return_ = 0;

	print_list(info->history);
	return (return_);
}
/**
 * unset_alias - it sets alias to string.
 * @info: A pointer to a var_info_t struct
 * containing information about the aliases.
 * @str: The name of the alias to unset.
 *
 * Return: 0 on success, 1 on failure.
 */
int unset_alias(var_info_t *info, char *str)
{
	char *ch_p, ch_c, *alias_name;
	int ret;

	ch_p = _strchr(str, '=');
	if (!ch_p)
		return (1);
	ch_c = *ch_p;
	*ch_p = 0;
	alias_name = str;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, alias_name, -1)));
	*ch_p = ch_c;
	return (ret);
}
/**
 * set_alias - the func sets alias to string.
 * @info: A pointer to a var_info_t struct
 * containing information about the aliases.
 * @str: A string containing the alias and
 * its value, in the format "alias_name=alias_value".
 *
 * Return: 0 on success, 1 on failure.
 */
int set_alias(var_info_t *info, char *str)
{
	char *chr_p;
	char *alias_name;
	int unset_result;
	int add_result;

	chr_p = _strchr(str, '=');
	if (!chr_p)
		return (1);

	alias_name = str;
	*chr_p = '\0';
	unset_result = unset_alias(info, alias_name);
	*chr_p = '=';

	if (!*(chr_p + 1))
		return (unset_result);

	add_result = (add_node_end(&(info->alias), str, 0) == NULL);
	return (add_result);
}

/**
 * print_alias - Prints an alias to the console.
 * @node: A pointer to a var_list_t struct
 * containing information about the alias.
 *
 * Return: return Always 0 on success, 1 on error
 */
int print_alias(var_list_t *node)
{
	char *chr_t = NULL, *chr_x = NULL;
	long int alias_length;
	int r = 1;

	if (node)
	{
		chr_t = _strchr(node->str, '=');
		alias_length = chr_t - node->str;
		for (chr_x = node->str; chr_x <= chr_t; chr_x++)
			_putchar(*chr_x);
		_putchar('\'');
		_puts(chr_t + 1);
		_puts("'\n");
		printf("Alias length: %ld\n", alias_length);
		return (0);
	}
	return (r);
}

/**
 * _myalias - Prints or sets aliases.
 * @info: A pointer to a var_info_t struct
 * containing information about the aliases.
 *  Return: return Always 0
 */
int _myalias(var_info_t *info)
{
	int q = 0;
	int r = 0;
	char *k = NULL, *alias_name;
	var_list_t *node = NULL;

	if (info->argc == 1)
	{

		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (q = 1; info->argv[q]; q++)
	{
		k = _strchr(info->argv[q], '=');
		alias_name = info->argv[q];
		if (k)
			set_alias(info, alias_name);
		else
			print_alias(node_starts_with(info->alias, alias_name, '='));
	}
	return (r);
}

