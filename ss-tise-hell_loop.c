#include "ss-tise-shell.h"
/**
 * hsh-This function is the main function for a shell program.
 * It reads input from the user,
 * parses it, and executes the appropriate command.
 * It supports built-in commands as well
 * as external commands. It also handles signals and
 * maintains a history of commands.
 * @info: A pointer to a var_info_t structure that
 * contains information about the shell state.
 * @varchav: A pointer to an array of strings
 * representing the command and its arguments.
 *
 * Return: The status of the last command executed, or -2 if an error occurred.
 */
int hsh(var_info_t *info, char **varchav)
{
	ssize_t t = 0;
	int varintbuiltin_ret = 0;
	int exitStatus = 0;
	int errorNumber = 0;

	while (t != -1 && varintbuiltin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(info);
		if (t != -1)
		{
			set_info(info, varchav);
			varintbuiltin_ret = find_builtin(info);
			if (varintbuiltin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exitStatus = info->status;
	if (varintbuiltin_ret == -2)
	{
		if (info->err_num == -1)
			exitStatus = info->status;
		else
			errorNumber = info->err_num;
	}
	if (exitStatus)
		exit(exitStatus);
	if (errorNumber)
		exit(errorNumber);
	return (varintbuiltin_ret);
}
/**
 * find_builtin -This function checks if the first argument in the command line
 * input matches any of the built-in commands.
 * If a match is found, it executes the corresponding built-in function.
 * Parameters:
 *@info: A pointer to a var_info_t structure that contains
 * information about the shell state.
 * Return: return value of the built-in function if a match is found,
 * or -1 if no match is found.
 */
int find_builtin(var_info_t *info)
{
	int h, varbuilt_in_ret = -1;
	int numBuiltins = 8;

	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (h = 0; h < numBuiltins; h++)
		if (_strcmp(info->argv[0], builtintbl[h].type) == 0)
		{
			info->line_count++;
			varbuilt_in_ret = builtintbl[h].func(info);
			break;
		}
	return (varbuilt_in_ret);
}
/**
 * find_cmd - This function checks if the first argument in
 * the command line input is a command.
 * If it is, it finds the path of the command and executes it.
 * If the command is not found,
 * it prints an error message.
 * @info: A pointer to a var_info_t structure that contains
 * information about the shell state.
 *
 * Returns: void
 */
void find_cmd(var_info_t *info)
{
	char *path = NULL;
	int r, o;
	int isCommand = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (r = 0, o = 0; info->arg[r]; r++)
		if (!is_delim(info->arg[r], " \t\n"))
			o++;
	if (!o)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		isCommand = is_cmd(info, info->argv[0]);
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && isCommand)
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd -This function creates a new process by calling fork,
 * and then replaces the current
 * process image with a new process image using execve.
 * It handles errors during
 * forking and executing, and waits for the
 * child process to terminate.
 *@info: A pointer to a var_info_t structure that
 * contains information about the shell state.
 * Returns: void
 */
void fork_cmd(var_info_t *info)
{
	pid_t varchild_pid;
	int execStatus = 0;

	varchild_pid = fork();
	if (varchild_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (varchild_pid == 0)
	{
		execStatus = execve(info->path, info->argv, get_environ(info));
		if (execStatus == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

