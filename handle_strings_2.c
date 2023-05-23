#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: destination pointer
 * @src: source pointer
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *destination = dest;

	while (*src != '\0')
	{
		*destination = *src;
		destination++;
		src++;
	}
	*destination = '\0';
	return (dest);
}

/**
 * _strdup - function that returns a pointer to
 * a newly allocated space in memory
 * @str: character array
 * Return: a pointer to the duplicated string or NULL
 */
char *_strdup(const char *str)
{
	char *p;

	if (str == NULL)
		return (NULL);

	p = (char *) malloc(strlen(str) + 1);

	if (p == NULL)
		return (NULL);
	_strcpy(p, str);
	return (p);
}

/**
 * _strncmp - function to compare two strings
 * @s1: first string
 * @s2: second string
 * @n: number of chars to compare
 * Return: integer value to indicate the difference
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (0);
	}
	return (0);
}


/**
 * _memcpy - Copies a specified number of bytes
 * @dest: destination memory block.
 * @src: source memory block.
 * @n: Number of bytes to be copied.
 * Return: A pointer to the destination
 **/

void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *dest_ptr = (char *)dest;
	const char *src_ptr = (const char *)src;

	for (i = 0; i < n; i++)
	{
		dest_ptr[i] = src_ptr[i];
	}

	return (dest);
}
/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string, where the result will be stored.
 * @src: The source string to be appended to @dest.
 * Return: A pointer to the resulting string @dest.
 **/

char *_strcat(char *dest, const char *src)
{
	char *dest_ptr = dest;

	while (*dest_ptr != '\0')
	{
		dest_ptr++;
	}

	while (*src != '\0')
	{
		*dest_ptr = *src;
		dest_ptr++;
		src++;
	}
	*dest_ptr = '\0';

	return (dest);
}
