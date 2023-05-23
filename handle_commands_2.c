#include "shell.h"

/**
 * handle_logic_op - Handles logical operators (&& and ||) in my shell program.
 * @args: Pointer to a pointer that holds the command arguments.
 * @program_name: Pointer to a string that holds the name of the shell program.
 * @env: Pointer to an array of strings representing the program's environment.
 * @exit_status: Pointer to the variable that holds the exit status.
 * @line_number: The line number where the logical operator is encountered.
 * @path: Pointer to a string that holds the system's PATH variable.
 * Return: Nothing.
 */
void handle_logic_op(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path)
{
	if (*exit_status == 0)
	{
		handle_command(args, program_name, env,
				exit_status, line_number, path);
	}
}

/**
 * handle_alias_command - Function that calls handle_alias
 * @args: pointer to a pointer that holds arguments.
 * Return: Nohting.
*/
void handle_alias_command(char **args)
{
	handle_alias(args);
}

/**
 * handle_other_commands - Handles other commands in my shell program.
 * @args: Pointer to a pointer that holds the command arguments.
 * @program_name: Pointer to a string that holds the name of the shell program.
 * @env: Pointer to an array of strings representing the program's environment.
 * @exit_status: Pointer to the variable that holds the exit status.
 * @line_number: The line number where the command is encountered.
 * @path: Pointer to a string that holds the system's PATH variable.
 * Return : Nothing.
 */
void handle_other_commands(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path)
{
	int abs_path;
	char *alias_value = get_alias_value(args[0]);

	if (alias_value != NULL)
	{
		handle_alias_command_arguments(alias_value, program_name,
				env, exit_status, line_number, path);
	}
	else
	{
		abs_path = (args[0][0] == '/');
		if (abs_path)
		{
			execute_command(program_name, args[0], args, env,
					abs_path, line_number, exit_status);
		}
		else
		{
			search_command(args, path, program_name, env,
					exit_status, line_number);

		}
	}
}

/**
 * handle_alias_command_arguments - Handles the arguments for the "alias"
 * @alias_value: Pointer to a string that holds the value of the alias.
 * @program_name: Pointer to a string that holds the name of the shell program.
 * @env: Pointer to an array of strings representing the program's environment.
 * @exit_status: Pointer to the variable that holds the exit status.
 * @line_number: The line number where the "alias" command is encountered.
 * @path: Pointer to a string that holds the system's PATH variable.
 * Return: Nothing.
 */
void handle_alias_command_arguments(char *alias_value, char *program_name,
		char **env, int *exit_status, int line_number, char *path)
{
	char **alias_args = split_string(alias_value, ' ');

	handle_command(alias_args, program_name, env, exit_status, line_number, path);
	free_split_string(alias_args);
}
