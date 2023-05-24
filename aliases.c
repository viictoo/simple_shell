#include "shell.h"
alias_t *aliases;

/**
 * add_alias - Adds an alias with the specified name and value.
 * @name: The name of the alias to add.
 * @value: The value associated with the alias.
 * Return: (null) if successful.
 */
void add_alias(const char *name, const char *value)
{
	alias_t *current_alias = aliases;
	alias_t *previous_alias = NULL;

	while (current_alias != NULL)
	{
		if (_strcmp(current_alias->name, name) == 0)
		{
			free(current_alias->value);
			current_alias->value = _strdup(value);
			return;
		}
		previous_alias = current_alias;
		current_alias = current_alias->next;
	}

	alias_t *new_alias = (alias_t *)malloc(sizeof(alias_t));

	new_alias->name = _strdup(name);
	new_alias->value = _strdup(value);
	new_alias->next = NULL;

	if (previous_alias != NULL)
	{
		previous_alias->next = new_alias;
	}
	else
	{
		aliases = new_alias;
	}
}


/**
 * print_aliases - Prints all the aliases.
 * This function prints all the aliases stored in the collection.
 * No parameters are required.
 * Return: None.
 **/
void print_aliases(void)
{
	alias_t *current = aliases;
	int len = 4;
	char *output;

	while (current != NULL)
	{
		len += _strlen(current->name) + _strlen(current->value);
		output = malloc(len + 1);
		if (output == NULL)
		{
			write(STDERR_FILENO, "Memory allocation failed.\n", 26);
			return;
		}
		_strcpy(output, current->name);
		_strcat(output, "='");
		_strcat(output, current->value);
		_strcat(output, "'\n");

		write(1, output, len);
		free(output);
		current = current->next;
	}
}
/**
 * get_alias_value - Retrieves value associated with the specified alias name
 * @name: The name of the alias to retrieve the value for
 * Return: The value associated with the alias name, or NULL if not found.
 **/
char *get_alias_value(const char *name)
{
	alias_t *current = aliases;

	while (current != NULL)
	{
		if (_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
 * print_alias - Prints the specified alias name and value.
 * @name: The name of the alias to print
 * @value: The value associated with the alias.
 * Return: None.
 **/

void print_alias(const char *name, const char *value)
{
	write(1, name, _strlen(name));
	write(1, "='", 2);
	write(1, value, _strlen(value));
	write(1, "'\n", 2);
}

/**
 * print_alias_not_found - Prints a message
 * @alias: The name of the alias that was not found.
 * Return: None.
 **/
void print_alias_not_found(const char *alias)
{
	write(1, "alias: ", 7);
	write(1, alias, _strlen(alias));
	write(1, " not found\n", 11);
}
