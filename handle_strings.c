#include "shell.h"

/**
 * _strtok - Breaks a string into a series of tokens.
 * @str: string to be tokenized.
 * @separator: delimiter characters.
 * Return: pointer to the next token
 **/

char *_strtok(char *str, const char *separator)
{
	static char *new_str;
	char *token;

	if (str != NULL)
	{
		new_str = str;
	}

	if (new_str == NULL || *new_str == '\0')
		return (NULL);

	new_str += _strspn(new_str, separator);
	if (*new_str == '\0')
	{
		return (NULL);
	}
	token = new_str;

	new_str += _strcspn(new_str, separator);
	if (*new_str != '\0')
	{
		*new_str = '\0';
		new_str++;
	}

	return (token);
}
/**
 * _memmove - Copies a block of memory
 * @destination: Pointer to the destination memory
 * @source: Pointer to the source memory block.
 * @num_bytes: Number of bytes to be copied
 * Return: pointer to the destination
 **/
void *_memmove(void *destination, const void *source, size_t num_bytes)
{
	char *str_out = (char *)destination;
	const char *str_in = (const char *)source;
	size_t i;

	if (str_out == str_in)
		return (str_out);

	if (str_in < str_out)
	{
		for (i = num_bytes; i > 0; i--)
			str_out[i - 1] = str_in[i - 1];
	} else
	{
		for (i = 0; i < num_bytes; i++)
			str_out[i] = str_in[i];
	}

	return (str_out);
}
/**
 * _strspn - Calculates the length of the initial segment of a string
 * @str: The string to be analyzed
 * @accept: The set of characters to be matched
 * Return: length of the initial segment of accepted chars
 **/


size_t _strspn(const char *str, const char *accept)
{
	const char *string = str;
	size_t n = 0;

	while (*string != '\0' && charchr(accept, *string) != NULL)
	{
		n++;
		string++;
	}

	return (n);
}
/**
 * _strcspn - Calculates the length of the initial segment of a string
 * @str: The string to be analyzed
 * @reject: The set of characters to be matched
 * Return: length of the initial segment of rejected chars
 **/
size_t _strcspn(const char *str, const char *reject)
{
	const char *string = str;
	size_t n = 0;

	while (*string != '\0' && charchr(reject, *string) == NULL)
	{
		n++;
		string++;
	}

	return (n);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: Pointer to a string representing the number to convert.
 * Return: converted value or 0
 */
int _atoi(const char *s)
{
	int i, j, n, len, started, digit;

	i = 0, j = 0, n = 0, len = 0;
	started = 0;
	digit = 0;

	while (s[len] != '\0')
		len++;

	while (i < len && started == 0)
	{
		if (s[i] == '-')
			++j;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (j % 2)
				digit = -digit;
			n = n * 10 + digit;
			started = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			started = 0;
		}
		i++;
	}

	if (started == 0)
		return (0);

	return (n);
}
