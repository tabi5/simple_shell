#include "ss-tise-shell.h"
/**
 * add_node - This function creates a new node and adds it to the
 * beginning of a linked list.
 *
 * Parameters:
 * @head: A pointer to a pointer to the first node in the linked list.
 * @str: A string to be stored in the new node.
 * @num: An integer to be stored in the new node.
 * Return: A pointer to the new node, or NULL if an error occurred.
 */
var_list_t *add_node(var_list_t **head, const char *str, int num)
{
	var_list_t *new_head;
	int nodeSize = sizeof(var_list_t);
	char *new_str = NULL;

	if (!head)
		return (NULL);
	new_head = malloc(nodeSize);
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, nodeSize);
	new_head->num = num;
	if (str)
	{
		new_str = _strdup(str);
		new_head->str = new_str;
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
/**
 * add_node_end - Adds a new node at the end of a var_list_t list.
 * @head: Double pointer to the head of the list.
 * @str: String to be included in the new node.
 * @num: Integer to be included in the new node.
 * Description: This function adds a new node at the end of a var_list_t list.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
var_list_t *add_node_end(var_list_t **head, const char *str, int num)
{
	var_list_t *new_node, *node;
	int count = 0;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(var_list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(var_list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
			count++;
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}
/**
 * print_list_str - Prints all the strings in a var_list_t list and returns
 * the number of nodes.
 * @k: Pointer to the head of the list.
 *
 * Description: This function prints all the strings in
 * a var_list_t list and returns the number of nodes.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const var_list_t *k)
{
	size_t h = 0;
	int counter = 0;

	while (k)
	{
		if (k->str)
		{
			_puts(k->str);
			counter++;
		}
		else
			_puts("(nil)");

		_puts("\n");
		k = k->next;
		h++;
	}
	return (h);
}

/**
 * delete_node_at_index - Deletes a node at a specific
 *index in a var_list_t list.
 * @head: Double pointer to the head of the list.
 * @varindex: Index of the node to be deleted.
 *
 * Description: This function deletes a node at a
 * specific index in a var_list_t list.
 * Return: 1 if successful, 0 otherwise.
 */
int delete_node_at_index(var_list_t **head, unsigned int varindex)
{
	var_list_t *node, *prev_node;
	unsigned int i = 0;
	int counter = 0;
	int z = 0;

	if (!head || !*head)
		return (z);

	if (!varindex)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == varindex)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		counter++;
		prev_node = node;
		node = node->next;
	}
	return (z);
}

/**
 * free_list - Frees a linked list of type var_list_t.
 * @addhead_ptr: Double pointer to the head of the list.
 *
 * Description: This function frees a linked list of type var_list_t.
 * It takes one parameter: a double pointer to the head of the list.
 * It checks if the head is NULL or if the list is empty. If either is true,
 * it returns without doing anything.
 * It sets 'node' to point to the head of the list.
 * It enters a loop that continues as long as 'node'
 * is not NULL. Inside the loop,
 * it sets 'next_node' to point to the next node in the list,
 * frees the string contained in 'node'
 * and then frees 'node' itself. It then moves
 * to the next node in the list and repeats the process.
 * After it has visited and freed all nodes,
 *it sets the head of the list to NULL.
 * After freeing all the nodes, it prints
 *out the total number of nodes freed.
 *
 */
void free_list(var_list_t **addhead_ptr)
{
	var_list_t *node, *next_node, *head;
	int counter = 0;
	int total_str_len = 0;

	if (!addhead_ptr || !*addhead_ptr)
		return;
	head = *addhead_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		if (node->str)
		{
			total_str_len += strlen(node->str);
			free(node->str);
		}
		free(node);
		node = next_node;
		counter++;
	}
	*addhead_ptr = NULL;
}

