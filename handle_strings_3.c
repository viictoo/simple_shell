#include "shell.h"

/**
 *  charchr - Locates the first occurrence of a character in a string.
 * @str: The string to be searched.
 * @c: The character to be located
 * Return: A pointer to the first occurrence c
 **/

char *charchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * charcmp - function to compare two strings
 * @s1: first string
 * @s2: second string
 * Return: integer value to indicate the difference
 */
int charcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] < s2[i])
		{
			return (-1);
		} else if (s1[i] > s2[i])
		{
			return (1);
		}
		i++;
	}

	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else if (s1[i] == '\0')
		return (-1);
	else
		return (1);
}


/**
 * charlen - calculates the length of a string
 * @s: pointer to variable
 * Return: length of string
 */
int charlen(const char *s)
{
	int length;

	length = 0;
	while (*s != '\0')
	{
		length++;
		s++;
	}

	return (length);
}
