#include "shell.h"


/**
 * remove_double_quotes - Removes double quotes from a string.
 * @args: Pointer to a pointer that holds the string to modify.
 * Return: Nothing.
 */
void remove_double_quotes(char **args)
{
	int i = 0;
	size_t arg_length;

	while (args[i] != NULL)
	{
		if (args[i][0] == '\"' && args[i][_strlen(args[i]) - 1] == '\"')
		{
			arg_length = _strlen(args[i]);
			_memmove(args[i], args[i] + 1, arg_length - 2);
			args[i][arg_length - 2] = '\0';
		}
		i++;
	}
}

/**
 * handle_variable_replacement - Handles variable
 * replacement in command arguments.
 * @args: Pointer to a pointer that holds the command arguments.
 * @exit_status: Pointer to the variable that holds the exit status.
 * Return: Nothing.
 */
void handle_variable_replacement(char **args, int *exit_status)
{
	int i = 0;
	char *variable, status_str[10], pid_str[10];
	char *value;

	while (args[i] != NULL)
	{
		if (args[i][0] == '$')
		{
			variable = args[i] + 1;
			if (_strcmp(variable, "?") == 0)
			{
				int_to_str(*exit_status, status_str,
						sizeof(status_str));
				args[i] = _strdup(status_str);
			}
			else if (_strcmp(variable, "$") == 0)
			{
				int_to_str(getpid(), pid_str, sizeof(pid_str));
				args[i] = _strdup(pid_str);
			} else
			{
				value = _getenv(variable);
				if (value != NULL)
					args[i] = _strdup(value);
				else if (value == NULL)
					args[i] = NULL;
			}
		}
		i++;
	}
}


/**
 * handle_exit_command - Handles the "exit" command in a shell program.
 * @arg: Pointer to a string that holds the argument of the "exit" command.
 * @exit_status: Pointer to the variable that holds the exit status.
 * @program_name: Pointer to a string that holds the name of the shell program.
 * @line_number: The line number where the "exit" command is encountered.
 * Return: Nothing.
 */
void handle_exit_command(char *arg, int *exit_status,
		char *program_name, int line_number)
{
	char *endptr;
	long exit_code;

	if (arg != NULL)
	{

		exit_code = _strtol(arg, &endptr, 10);
		if (*endptr == '\0' && exit_code <= INT_MAX && exit_code >= 0)
		{
			*exit_status = (int)exit_code;
		}
		else
		{
			print_error(program_name, arg, 23, line_number);
			*exit_status = 2;
		}
	}
	exit(*exit_status);
}
