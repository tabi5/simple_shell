#include "ss-tise-shell.h"


/**
 * clear_info -Clears the information in a var_info_t struct.
 * @info :-A pointer to the var_info_t struct to clear.
 * return None.
 */

void clear_info(var_info_t *info)
{
	char *arg = NULL;
	char **argv = NULL;
	char *path = NULL;
	int argc = 0;

	info->arg = arg;
	info->argv = argv;
	info->path = path;
	info->argc = argc;
}
/**
 * set_info - Sets the information in a var_info_t struct.
 * @info: A pointer to the var_info_t struct to set.
 * @chav: An array of strings containing the information
 * to set in the struct..
 */
void set_info(var_info_t *info, char **chav)
{
	int s = 0;
	char **temp_argv = NULL;

	info->fname = chav[0];
	if (info->arg)
	{
		temp_argv = strtow(info->arg, " \t");
		if (!temp_argv)
		{
			temp_argv = malloc(sizeof(char *) * 2);
			if (temp_argv)
			{
				temp_argv[0] = _strdup(info->arg);
				temp_argv[1] = NULL;
			}
		}
		info->argv = temp_argv;

		for (s = 0; info->argv && info->argv[s]; s++)
			;
		info->argc = s;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info - Frees allocated memory in a var_info_t structure.
 * Frees the memory allocated by the set_info() function.
 * This function frees memory allocated to various fields in the var_info_t
 * structure. If 'tot' is non-zero, it also frees the lists pointed to by
 * 'env', 'history', and 'alias', and closes the file descriptor in 'readfd'.
 *
 *@info: A pointer to the var_info_t struct to free.
 *@tot: A flag indicating whether to free all of the memory allocated by
 *  the set_info() function (if tot is non-zero) or just the argv member
 * of the var_info_t struct (if tot is zero).
 */
void free_info(var_info_t *info, int tot)
{
	if (!info)
		return;
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (tot)
	{
		if (!info->cmd_buf)
			free(info->arg);
		free_lists(info);
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		close_readfd(info);
		_putchar(BUF_FLUSH);
	}
}

/**
 * free_lists -Frees the memory allocated for the env,
 * history, and alias members of the info struc.
 *
 * This function frees the lists pointed to by 'env',
 * 'history', and 'alias'
 * in the var_info_t structure.
 *
 * @info:A pointer to the var_info_t struct to free.
 */
void free_lists(var_info_t *info)
{
	if (info->env)
		free_list(&(info->env));
	if (info->history)
		free_list(&(info->history));
	if (info->alias)
		free_list(&(info->alias));
}

/**
 * close_readfd -Closes the file descriptor in a var_info_t structure.
 *
 * This function closes the file descriptor in 'readfd'
 * if it is greater than 2.
 *
 * @info: info Pointer to the var_info_t structure.
 */
void close_readfd(var_info_t *info)
{
	if (info->readfd > 2)
		close(info->readfd);
}


