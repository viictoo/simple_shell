#include "shell.h"

/**
 * handle_alias - Handles the alias command with the given arguments.
 * @args: An array of strings representing the command arguments.
 * Return: None.
 **/
void handle_alias(char **args)
{
	int i = 1;
	char *alias, *equal_sign, *name, *value;

	if (args[1] == NULL)
	{
		print_aliases();
		return;
	}
	while (args[i] != NULL)
	{
		alias = args[i];
		equal_sign = charchr(alias, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			name = alias;
			value = equal_sign + 1;
			if (value[0] == '\'' && value[charlen(value) - 1] == '\'')
			{
				value[charlen(value) - 1] = '\0';
				value++;
			}
			add_alias(name, value);
		} else if (alias[0] == '\'' && alias[charlen(alias) - 1] == '\'')
		{
			alias[charlen(alias) - 1] = '\0';
			alias++;
			value = get_alias_value(alias);
		} else
		{
			value = get_alias_value(alias);
			if (value != NULL)
			{
				print_alias(alias, value);	}
			else
			{
				print_alias_not_found(alias);	}
		}
		i++;
	}
}
/**
 * split_string - Splits a string into an array based on a delimiter.
 * @str: The string to be split.
 * @delimiter: The delimiter character used to split the string.
 * Return: A dynamically allocated array of strings (char**)
 **/

char **split_string(const char *str, char delimiter)
{
	char **result = NULL;
	int count = 0;
	const char *temp = str;
	char *token = NULL;
	char *rest = NULL;
	int i = 0;

	while ((token = _strtok_r((char *)temp, &delimiter, &rest)) != NULL)
	{
		count++;
		temp = NULL;
	}

	result = (char **)malloc((count + 1) * sizeof(char *));
	temp = str;

	while ((token = _strtok_r((char *)temp, &delimiter, &rest)) != NULL)
	{
		result[i] = chardup(token);
		i++;
		temp = NULL;
	}
	result[i] = NULL;
	return (result);
}

/**
 * free_split_string - Frees the memory allocated for the array of strings.
 * @strings: The array of strings to be freed.
 * Return: None.
 **/

void free_split_string(char **strings)
{
	int i = 0;

	if (strings == NULL)
		return;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}

	free(strings);
}

/**
 * _strtok_r - Breaks a string intotokens based on a set of delimiters
 * @str: The string to be tokenized.
 * @delim: The delimiter string used to determine token boundaries.
 * @saveptr: char* variable that stores the position of the next token
 * Return: A pointer to the next token
 **/

char *_strtok_r(char *str, const char *delim, char **saveptr)
{

	char *token;

	if (str == NULL && *saveptr == NULL)
	{
		return (NULL);
	}
	if (str != NULL)
	{
		*saveptr = str;
	}
	*saveptr += _strspn(*saveptr, delim);
	if (**saveptr == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	token = *saveptr;
	*saveptr += _strcspn(*saveptr, delim);
	if (**saveptr != '\0')
	{
		**saveptr = '\0';
		(*saveptr)++;
	} else
	{
		*saveptr = NULL;
	}
	return (token);
}
