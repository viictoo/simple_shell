#include "shell.h"

/**
 * _strtol - Converts a string to a long integer.
 * @str: The string to be converted.
 * @endptr: address of the first invalid character
 * @base: The base to be used for the conversion
 * Return: The converted long integer value.
 */
long _strtol(const char *str, char **endptr, int base)
{
	long value = 0;
	int sign = 1, digit;

	base = get_base(base, str);
	while (_isspace(*str))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (_isdigit(*str) || (*str >= 'a' && *str <= 'f')
			|| (*str >= 'A' && *str <= 'F'))
	{
		if (_isdigit(*str))
		{
			digit = *str - '0';
		} else if (*str >= 'a' && *str <= 'f')
		{
			digit = *str - 'a' + 10;
		} else
		{
			digit = *str - 'A' + 10;
		}
		if (digit >= base)
			break;
		value = value * base + digit;
		str++;
	}
	if (endptr != NULL)
		*endptr = (char *)str;
	value *= sign;
	return (value);
}

/**
 * get_base - Determines base
 * @base: The base specified
 * @str: The string t convert
 * Return: base for the string
 */
int get_base(int base, const char *str)
{
	if (base == 0)
	{
		if (*str == '0')
		{
			if (str[1] == 'x' || str[1] == 'X')
			{
				base = 16;
				str += 2;
			}
			else
			{
				base = 8;
				str++;
			}
		}
		else
		{
			base = 10;
		}
	}
	return (base);
}

/**
 * _isdigit - Checks if a character is a digit.
 * @c: The character to be checked.
 * Return: non zero if digit, 0 otherwise.
 */

int _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * _isspace - Checks if a character is a digit.
 * @c: The character to be checked.
 * Return: non zero if space, 0 otherwise.
 */
int _isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r');
}
