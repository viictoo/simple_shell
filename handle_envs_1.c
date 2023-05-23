#include "shell.h"

/**
 * handle_env_command - Handles the "env" command.
 * Return: Nothing.
 */
void handle_env_command(void)
{
	print_environment();
}

/**
 * handle_setenv_command - Handles the setenv.
 * @arg1: Pointer to a string that holds the first argument of setenv.
 * @arg2: Pointer to a string that holds the second argument of setenv
 * @exit_status: Pointer to the variable that holds the exit status.
 * Return: Nothing.
 */
void handle_setenv_command(char *arg1, char *arg2, int *exit_status)
{
	const char *error_message;

	if (arg1 != NULL && arg2 != NULL)
	{
		set_environment_variable(arg1, arg2);
	}
	else
	{
		error_message = "Error: Invalid number of arguments for setenv command.\n";
		write(STDERR_FILENO, error_message, strlen(error_message));

		*exit_status = 1;
	}
}

/**
 * handle_unset_command - Handles the "unset" command.
 * @arg: Pointer to a string that holds the argument of the "unset" command.
 * Return: Nothing.
 */
void handle_unset_command(char *arg)
{
	const char *error_message;

	if (arg != NULL)
	{
		if (unsetenv(arg) != 0)
		{
			perror("Error unsetting environment variable");
		}
	}
	else
	{
		error_message = "Use: unset VAR.\n";
		write(STDERR_FILENO, error_message, strlen(error_message));
	}
}
/**
 * print_environment - Prints the current environment variables.
 * Return: Nothing.
 */
void print_environment(void)
{
	char **env = environ;
	char buffer[4096];
	int len;

	while (*env != NULL)
	{
		len = 0;
		while ((*env)[len] != '\0')
		{
			buffer[len] = (*env)[len];
			len++;
		}
		buffer[len++] = '\n';
		write(STDOUT_FILENO, buffer, len);
		env++;
	}
}
