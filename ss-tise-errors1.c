#include "ss-tise-shell.h"

/**
 * _erratoi - the func converts a string to an integer.
 * @vars: A pointer to a string containing
 * the integer to convert.
 * Return: The integer value of the string,
 * or -1 if the string is not a valid integer
 */
int _erratoi(char *vars)
{
	int var_int_j = 0;
	unsigned long int var_result = 0;
	char current_char;

	if (*vars == '+')
		vars++;


	while ((current_char = vars[var_int_j]) != '\0')
	{
		if (current_char >= '0' && current_char <= '9')
		{
			var_result = var_result * 10 + (current_char - '0');
			if (var_result > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
		var_int_j++;
	}

	return (var_result);
}
/**
 * print_error - the funcPrints
 * an error message to the console.
 * @info: A pointer to the var_info_t struct.
 * @estr: A string containing the error message.
 * Return: None.
 */
void print_error(var_info_t *info, char *estr)
{
	char *fname = info->fname;
	int line_count = info->line_count;
	char *arg0 = info->argv[0];

	_eputs(fname);
	_eputs(": ");
	print_d(line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(arg0);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints an integer to the specified file descriptor.
 * @varinput:The integer to print.
 * @varfd:The file descriptor to print to.
 *
 * Return: The number of characters printed.
 */
int print_d(int varinput, int varfd)
{
	int (*__putchar)(char) = _putchar;
	int var_k, count_int = 0;
	unsigned int int_abs_var, varintcurrent;
	int is_stderr = (varfd == STDERR_FILENO);

	if (is_stderr)
	{
		__putchar = _eputchar;
	}
	if (varinput < 0)
	{
		int_abs_var = -varinput;
		__putchar('-');
		count_int++;
	}
	else
	{
		int_abs_var = varinput;
	}
	varintcurrent = int_abs_var;
	for (var_k = 1000000000; var_k > 1; var_k /= 10)
	{
		if (int_abs_var / var_k)
		{
			__putchar('0' + varintcurrent / var_k);
			count_int++;
		}
		varintcurrent %= var_k;
	}
	__putchar('0' + varintcurrent);
	count_int++;

	return (count_int);
}
/**
 * convert_number - func Converts a long integer to a string
 * in a given base..
 * @intnum: The long integer to convert.
 * @intba: he base to convert to.
 * @intflg: Flags that control the conversion.
 *
 * Return:  pointer to the converted string.
 */
char *convert_number(long int intnum, int intba, int intflg)
{
	static char *vararr;
	static char buffer[50];
	char var_ch_sign = 0;
	char *var_ch_ptr;
	unsigned long lon = intnum;
	int is_negative = (!(intflg & CONVERT_UNSIGNED) && intnum < 0);

	if (is_negative)
	{
		lon = -intnum;
		var_ch_sign = '-';
	}
	vararr = (intflg & CONVERT_LOWERCASE) ? "0123456789abcdef"
		: "0123456789ABCDEF";
	var_ch_ptr = &buffer[49];
	*var_ch_ptr = '\0';

	do {
		*--var_ch_ptr = vararr[lon % intba];
		lon /= intba;
	} while (lon != 0);

	if (var_ch_sign)
	{
		*--var_ch_ptr = var_ch_sign;
	}

	return (var_ch_ptr);
}
/**
 * remove_comments - the function Removes comments
 * from a string.
 * @chbuf: A pointer to the string containing the code..
 * Return:
 *   None.
 */
void remove_comments(char *chbuf)
{
	int var_h;
	char current_char;

	for (var_h = 0; (current_char = chbuf[var_h]) != '\0'; var_h++)
	{
		int is_comment_start = (current_char == '#'
				&& (!var_h || chbuf[var_h - 1] == ' '));
		if (is_comment_start)
		{
			chbuf[var_h] = '\0';
			break;
		}
	}
}

