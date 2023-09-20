#include "ss-tise-shell.h"

/**
 * _myexit - exits the shell.
 * @info: A pointer to a var_info_t struct
 * containing information about the shell.
 * Return: return exits with a given exit status,
 * (0) if info.argv[0] != "exit".
 * 2 on success, 1 on failure.
 */
int _myexit(var_info_t *info)
{
	int intexitcheck;

	if (info->argv[1])
	{
		intexitcheck = _erratoi(info->argv[1]);
		if (intexitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = intexitcheck;
	}
	else
	{
		info->err_num = -1;
	}

	return (-2);
}
/**
 * _mycd - changes a current directory of the process.
 * @info: a Structure containing potential arguments. Used to maintain.
 * constant the function prototype.
 * A pointer to a var_info_t struct
 * containing information about the shell.
 * Return: 0 on success, 1 on failure.
 */
int _mycd(var_info_t *info)
{
	char *chs, *dir, buffer[1024];
	int ret;

	chs = getcwd(buffer, 1024);
	if (!chs)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=");
		if (!dir)
			dir = "/";
		ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(chs);
			_putchar('\n');
			return (1);
		}
		_puts(dir), _putchar('\n');
		ret = chdir(dir);
	}
	else
		ret = chdir(info->argv[1]);
	if (ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _myhelp - Prints help for the given command.
 * @info:A pointer to a var_info_t struct containing
 * information about the command.
 * Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0 on success, 1 on failure.
 */
int _myhelp(var_info_t *info)
{
	char **charg_array = info->argv;
	int _return = 0;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*charg_array); /* temp att_unused workaround */
	return (_return);
}

