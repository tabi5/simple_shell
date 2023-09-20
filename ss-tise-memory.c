#include "ss-tise-shell.h"
/**
 * bfree - Frees the memory pointed to by the
 * given pointer and sets it to NULL.
 *
 * @voptr: The pointer to the memory to be freed.
 *
 * Return: returns 1 if the memory was successfully
 *  freed and the pointer set to NULL,
 *            otherwise returns 0.
 */
int bfree(void **voptr)
{

	int result = 0;

	if (voptr && *voptr)
	{
		free(*voptr);
		*voptr = NULL;
		if (*voptr == NULL)
		{
			result = 1;
		}
	}

	return (result);
}
