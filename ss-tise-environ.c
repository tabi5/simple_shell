#include "ss-tise-shell.h"

/**
 * _myenv - Prints the environment variables to the console.
 * @info: A pointer to a var_info_t struct containing
 * information about the environment variables.
 * Return: return Always 0.
 */
int _myenv(var_info_t *info)
{
	int r = 0;

	print_list_str(info->env);
	return (r);
}
/**
 * _getenv - Gets the value of an environment variable
 * @info: A pointer to a var_info_t struct containing
 * information about the environment variables.
 * @chname: The name of the environment variable
 *  to get the value of.
 *
 * Return: A pointer to the value of the environment
 * variable, or NULL if the environment
 * variable does not exist.
 */
char *_getenv(var_info_t *info, const char *chname)
{
	var_list_t *node = info->env;
	char *varp, *env_name = (char *)chname;

	while (node)
	{
		varp = starts_with(node->str, env_name);
		if (varp && *varp)
			return (varp);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - Sets the value of an environment variable.
 *
 * @info: A pointer to a var_info_t struct containing
 * information about the environment ariables.
 *
 *  Return: 0 on success, 1 on failure..
 */
int _mysetenv(var_info_t *info)
{
	char *var_name, *var_value;
	int r = 1;
	int s = 0;

	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (r);
	}
	var_name = info->argv[1];
	var_value = info->argv[2];
	if (_setenv(info, var_name, var_value))
		return (s);
	return (r);
}
/**
 * _myunsetenv - Unsets an environment variable..
 * @info: A pointer to a var_info_t struct containing
 * information about the environment  variables.
 * Return:  0 on success, 1 on failure..
 */
int _myunsetenv(var_info_t *info)
{
	int i;
	int r = 1;
	int s = 0;
	char *var_name;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (r);
	}
	for (i = 1; i <= info->argc; i++)
	{
		var_name = info->argv[i];
		_unsetenv(info, var_name);
	}
	return (s);
}
/**
 * populate_env_list - Populates a linked
 * list of environment variables.
 * @info: A pointer to a var_info_t struct
 * to store the linked list of environment variables.
 * Return: 0 on success, 1 on failure.
 */
int populate_env_list(var_info_t *info)
{
	var_list_t *node = NULL;
	size_t i;
	int s = 0;
	int env_count = 0;

	for (i = 0; environ[i]; i++)
	{
		add_node_end(&node, environ[i], 0);
		env_count++;
	}
	info->env = node;
	return (s);
}

