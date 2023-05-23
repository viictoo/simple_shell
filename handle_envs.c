#include "shell.h"

/**
 * _setenv - Set the value of an environment variable.
 * @name: The name of the environment variable to set.
 * @value: The value to assign to the environment variable.
 * @overwrite: Flag indicating whether to overwrite the variable.
 * Return: Nothing.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len_name, len_val, len_entry;
	char *pos, *entry;
	int result;

	if (name == NULL || value == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (!overwrite && _getenv(name) != NULL)
		return (0);

	len_name = _strlen(name);
	len_val = _strlen(value);
	len_entry = len_name + len_val + 2;
	entry = malloc(len_entry + 1);

	if (entry == NULL)
	{
		errno = ENOMEM;
		return (-1);
	}
	pos = entry;
	_strcpy(pos, name);
	pos += len_name;
	*pos++ = '=';
	_strcpy(pos, value);

	result = _putenv(entry);
	if (result != 0)
	{
		errno = EINVAL;
		free(entry);
		return (-1);
	}

	return (0);
}

/**
 * _putenv - Set an environment variable or update an existing one.
 * @string: Pointer to a string in the form of key=value.
 * Return: 0 Success.
 */
int _putenv(char *string)
{
	size_t length = _strlen(string), name_length, env_count = 0;
	char *equal_sign = _strchr(string, '='), **env = environ,
	     **env_copy, *new_entry;

	if (string == NULL || _strchr(string, '=') == NULL)
		return (-1);
	if (equal_sign == NULL)
		return (-1);
	name_length = (size_t)(equal_sign - string);
	while (*env != NULL)
	{
		env++;
		env_count++;
	}
	env_copy = malloc((env_count + 2) * sizeof(char *));
	if (env_copy == NULL)
		return (-1);
	_memcpy(env_copy, environ, env_count * sizeof(char *));
	env_copy[env_count + 1] = NULL;
	env = env_copy;
	while (*env != NULL)
	{
		if (_strncmp(*env, string, name_length) == 0 && (*env)[name_length] == '=')
		{   *env = string;
			environ = env_copy;
			return (0);
		}
		env++;
	}
	new_entry = malloc(length + 1);
	if (new_entry == NULL)
	{
		free(env_copy);
		return (-1);
	}
	_strcpy(new_entry, string);
	env_copy[env_count] = new_entry;
	environ = env_copy;
	return (0);
}



/**
 * _unsetenv - Unset (remove) an environment variable.
 * @name: The name of the environment variable to unset.
 * Return: 0 Success, -1 Failure;
 */
int _unsetenv(const char *name)
{
	char **env = environ, *env_name, *env_value, **src, **dst;
	int found = 0;

	if (name == NULL || _strchr(name, '=') != NULL)
		return (-1);

	while (*env != NULL)
	{
		env_name = *env;
		env_value = _strchr(env_name, '=');
		if (env_value != NULL)
		{
			*env_value = '\0';
			if (_strcmp(env_name, name) == 0)
			{
				src = env + 1;
				dst = env;
				while (*src != NULL)
					*dst++ = *src++;
				*dst = NULL;
				found = 1;
			}

			*env_value = '=';
		}

		env++;
	}

	return (found ? 0 : -1);
}

/**
 * set_environment_variable - Sets the value of an environment variable.
 * @variable: Pointer to a string representing the name of the env variable.
 * @value: Pointer to string representing value to assign to the env variable.
 * Return: Nothing.
 */
void set_environment_variable(char *variable, char *value)
{

	if (_setenv(variable, value, 1) != 0)
	{
		write(STDERR_FILENO, "setenv: failed to set environment variable\n", 42);
		write(STDOUT_FILENO, "\n", 1);
	}

}


/**
 * unset_environment_variable - Unsets (removes) an environment variable.
 * @variable: Pointer to a string.
 * Return: Nothing.
 */
void unset_environment_variable(char *variable)
{
	if (_unsetenv(variable) != 0)
	{
		write(STDERR_FILENO, "unsetenv: failed to unset environment variable\n", 47);
		write(STDOUT_FILENO, "\n", 1);
	}
}

