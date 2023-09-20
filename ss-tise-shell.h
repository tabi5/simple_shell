#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} var_list_t;

/**
 * struct passinfo - contains the pseudo-arguements to pass into a function,
 * allowing a uniform prototype for the function pointer struct.
 * @arg: a string generated from a getline containing arguements.
 * @argv:an array of the strings generated from arg.
 * @path: a string path for current command.
 * @env_changed: on if environ has been changed.
 * @status: a return status of the last exec'd command.
 * @cmd_buf: the address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read the line input.
 * @histcount: a history line number count.
 * @argc: a argument count.
 * @line_count: count of the error.
 * @err_num: a error code for exit()s.
 * @linecount_flag: if on the count this line of input.
 * @fname: the program of filename.
 * @env: a linked list local copy of environ.
 * @environ: a custom modified copy of environ from LL env.
 * @history: the history of a node.
 * @alias: the alias of node.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	var_list_t *env;
	var_list_t *history;
	var_list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} var_info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @func: a function name.
 * @type: a builtin command for flag.
 *
 */
typedef struct builtin
{
	char *type;
	int (*func)(var_info_t *);
} builtin_table;
int hsh(var_info_t *, char **);
int find_builtin(var_info_t *);
void find_cmd(var_info_t *);
void fork_cmd(var_info_t *);
int is_cmd(var_info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(var_info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(var_info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(var_info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(var_info_t *);
int _mycd(var_info_t *);
int _myhelp(var_info_t *);

/* toem_builtin1.c */
int _myhistory(var_info_t *);
int _myalias(var_info_t *);

/*toem_getline.c */
ssize_t get_input(var_info_t *);
int _getline(var_info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(var_info_t *);
void set_info(var_info_t *, char **);
void free_info(var_info_t *, int);
void free_lists(var_info_t *);
void close_readfd(var_info_t *);
/* toem_environ.c */
char *_getenv(var_info_t *, const char *);
int _myenv(var_info_t *);
int _mysetenv(var_info_t *);
int _myunsetenv(var_info_t *);
int populate_env_list(var_info_t *);

/* toem_getenv.c */
char **get_environ(var_info_t *);
int _unsetenv(var_info_t *, char *);
int _setenv(var_info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(var_info_t *info);
int write_history(var_info_t *info);
int read_history(var_info_t *info);
int build_history_list(var_info_t *info, char *buf, int linecount);
int renumber_history(var_info_t *info);

/* toem_lists.c */
var_list_t *add_node(var_list_t **, const char *, int);
var_list_t *add_node_end(var_list_t **, const char *, int);
size_t print_list_str(const var_list_t *);
int delete_node_at_index(var_list_t **, unsigned int);
void free_list(var_list_t **);

/* toem_lists1.c */
size_t list_len(const var_list_t *);
char **list_to_strings(var_list_t *);
size_t print_list(const var_list_t *);
var_list_t *node_starts_with(var_list_t *, char *, char);
ssize_t get_node_index(var_list_t *, var_list_t *);
/* toem_vars.c */
int is_chain(var_info_t *, char *, size_t *);
void check_chain(var_info_t *, char *, size_t *, size_t, size_t);
int replace_alias(var_info_t *);
int replace_vars(var_info_t *);
int replace_string(char **, char *);

#endif

