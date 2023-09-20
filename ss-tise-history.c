#include "ss-tise-shell.h"
/**
 * get_history_file - This function gets the history file -
 * from the home directory.
 * @info: A pointer to a var_info_t structure
 * that contains information about the shell state.
 * Return: A string containing the path to
 *   the history file, or NULL if an error occurred.
 */
char *get_history_file(var_info_t *info)
{
	char *varbuf, *vardir;
	int pathLength = 0;

	vardir = _getenv(info, "HOME=");
	if (!vardir)
		return (NULL);
	pathLength = _strlen(vardir) + _strlen(HIST_FILE) + 2;
	varbuf = malloc(sizeof(char) * pathLength);
	if (!varbuf)
		return (NULL);
	varbuf[0] = 0;
	_strcpy(varbuf, vardir);
	_strcat(varbuf, "/");
	_strcat(varbuf, HIST_FILE);
	return (varbuf);
}
/**
 * write_history -This function writes the command history to
 * a history file in the home directory.
 *@info: A pointer to a var_info_t structure that
 * contains information about the shell state.
 *
 * Return: return 1 if the history was successfully written,
 *  or -1 if an error occurred.
 */
int write_history(var_info_t *info)
{
	ssize_t szfd;
	char *varflname = get_history_file(info);
	var_list_t *node = NULL;
	int writeStatus = 1;

	if (!varflname)
		return (-1);

	szfd = open(varflname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(varflname);
	if (szfd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, szfd);
		_putfd('\n', szfd);
	}
	_putfd(BUF_FLUSH, szfd);
	close(szfd);
	return (writeStatus);
}
/**
 * read_history -This function reads the command history
 * from a history file in the home directory.
 *
 * @info: A pointer to a var_info_t structure
 * that contains information about the shell state.
 *
 * Return:  return  The number of commands in the history,
 *   or 0 if an error occurred.
 */
int read_history(var_info_t *info)
{
	int t, varlast = 0, varlnecot = 0, historyCount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat varst;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &varst))
		fsize = varst.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (t = 0; t < fsize; t++)
		if (buf[t] == '\n')
		{
			buf[t] = 0;
			build_history_list(info, buf + varlast, varlnecot++);
			varlast = t + 1;
		}
	if (varlast != t)
		build_history_list(info, buf + varlast, varlnecot++);
	free(buf);
	info->histcount = varlnecot;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	historyCount = info->histcount;
	return (historyCount);
}
/**
 *build_history_list -This function adds a command to the history list.
 *@info: A pointer to a var_info_t structure that contains
 * information about the shell state.
 *@buf: A string containing the command to be added to the history.
 *@linecount: The line number of the command in the history.
 *
 * Return: return 0 if the command was successfully added to the history,
 *  or an error code if an error occurred.
 */
int build_history_list(var_info_t *info, char *buf, int linecount)
{
	var_list_t *node = NULL;
	int addStatus = 0;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	addStatus = 0;
	return (addStatus);
}
/**
 * renumber_history -This function renumbers the command history list.
 *
 *@info: A pointer to a var_info_t structure that
 *contains information about the shell state.
 * Return: return The number of commands in the history.
 */
int renumber_history(var_info_t *info)
{
	var_list_t *node = info->history;
	int k = 0;
	int historyCount = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	historyCount = k;
	return (info->histcount = historyCount);
}



