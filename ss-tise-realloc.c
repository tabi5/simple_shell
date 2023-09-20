#include "ss-tise-shell.h"
/**
 * _memset - Fills the first 'varintn' characters of the memory area pointed
 * to by 'varchd' with the constant byte 'varchb'.
 *
 * @varchd: A pointer to the memory area to be filled.
 * @varchb: The character to fill the memory area with.
 * @varintn: The number of bytes to be filled.
 *
 *  Return: return a pointer to the memory area 'varchd'.
 */

char *_memset(char *varchd, char varchb, unsigned int varintn)
{
	unsigned int i;
	char *ptr = varchd;

	for (i = 0; i < varintn; i++, ptr++)
		*ptr = varchb;
	return (varchd);
}
/**
 * ffree- Frees a null-terminated array of pointers
 * and sets each pointer to NULL.
 *
 * @varchpp: The null-terminated array
 * of pointers to be freed.
 * Return: This function does not return a value.
 */

void ffree(char **varchpp)
{
	char **v = varchpp;
	char **temp;

	if (!varchpp)
		return;
	while (*varchpp)
	{
		temp = varchpp;
		free(*varchpp++);
		*temp = NULL;
	}
	free(v);
}
/**
 * _realloc -Changes the size of the memory block pointed to
 * by 'voptr' to 'new_sz' bytes.
 *
 * @voptr: A pointer to the memory block to be resized.
 * @varold_sz: The old size of the memory block.
 * @new_sz: The new size of the memory block.
 *
 * Return: Returns a pointer to the newly allocated memory,
 * or NULL if the request fails.
 */

void *_realloc(void *voptr, unsigned int varold_sz, unsigned int new_sz)
{
	char *t;
	unsigned int copy_size;

	if (!voptr)
		return (malloc(new_sz));
	if (!new_sz)
	{
		free(voptr);
		return (NULL);
	}
	if (new_sz == varold_sz)
		return (voptr);

	t = malloc(new_sz);
	if (!t)
		return (NULL);

	copy_size = varold_sz < new_sz ? varold_sz : new_sz;
	while (copy_size--)
		t[copy_size] = ((char *)voptr)[copy_size];
	free(voptr);
	return (t);
}

