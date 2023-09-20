#include "ss-tise-shell.h"
/**
 * list_len - Calculates the length of a linked list
 * and the total length of the strings in the list.
 * @f: Pointer to the head of the list.
 *
 * Description: This function calculates the length of
 * a linked list of type var_list_t and also calculates
 * Return: The number of nodes in the list.
 */
size_t list_len(const var_list_t *f)
{
	size_t j = 0;
	int total_str_len = 0;
	int total_char_count = 0;

	while (f)
	{
		if (f->str)
		{
			total_str_len += strlen(f->str);
			total_char_count += strlen(f->str) + 1;
		}
		f = f->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - Converts a linked list of
 * type var_list_t into an array of strings.
 * @head: Pointer to the head of the list.
 *
 * Description: This function converts a linked list of type
 * var_list_t into an array of strings.
 *
 * Return: A pointer to an array of strings if successful,
 * NULL otherwise.
 */
char **list_to_strings(var_list_t *head)
{
	var_list_t *node = head;
	size_t k = list_len(head), p;
	char **varstrs;
	char *str;
	int total_char_count = 0;

	if (!head || !k)
		return (NULL);
	varstrs = malloc(sizeof(char *) * (k + 1));
	if (!varstrs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (p = 0; p < k; p++)
				free(varstrs[p]);
			free(varstrs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		varstrs[k] = str;
		total_char_count += _strlen(str);
	}
	varstrs[k] = NULL;
	return (varstrs);
}

/**
 * print_list - Prints all the elements of a var_list_t list.
 * @f: Pointer to the first node in the list.
 *
 * This function iterates through a linked list of type var_list_t,
 * and prints each element. The 'num' element is converted to a string
 * and printed, followed by a colon and a space. The 'str' element is
 * then printed. If 'str' is NULL, "(nil)" is printed instead.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list(const var_list_t *f)
{
	size_t k = 0;
	int base = 10;
	int uppercase = 0;

	while (f)
	{
		char *num_str = convert_number(f->num, base, uppercase);
		char *str_to_print = f->str ? f->str : "(nil)";

		_puts(num_str);
		_putchar(':');
		_putchar(' ');
		_puts(str_to_print);
		_puts("\n");

		f = f->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - Finds the first node in a
 * var_list_t list where the
 * 'str' element starts with a given prefix.
 * @node: Pointer to the first node in the list.
 * @varprefix: The prefix to search for at the start of 'str'.
 * @d: The character that should follow the prefix. If -1,
 * any character is allowed.
 *
 * This function iterates through a linked list of type var_list_t,
 * and checks each 'str' element to see if it starts with 'varprefix'.
 * If 'd' is not -1, it also checks that
 * the character following 'varprefix' is 'd'.
 *
 * Return: A pointer to the first node where 'str'
 * starts with 'varprefix'
 * (and is followed by 'd', if 'd' is not -1).
 *         If no such node is found, it returns NULL.
 */
var_list_t *node_starts_with(var_list_t *node, char *varprefix, char d)
{
	char *z = NULL;
	var_list_t *current_node = node;

	while (current_node)
	{
		z = starts_with(current_node->str, varprefix);
		if (z && ((d == -1) || (*z == d)))
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Returns the index of a node in a var_list_t list.
 * @head: Pointer to the first node in the list.
 * @node: The node whose index is to be found.
 *
 * This function iterates through a linked list of type var_list_t,
 * and checks each node to see if it is the same as 'node'.
 *
 * Return: The index of 'node' if it is found in the list, starting from 0.
 *         If 'node' is not found in the list, it returns -1.
 */
ssize_t get_node_index(var_list_t *head, var_list_t *node)
{
	size_t index = 0;
	var_list_t *current_node = head;

	while (current_node)
	{
		if (current_node == node)
			return (index);
		current_node = current_node->next;
		index++;
	}
	return (-1);
}




