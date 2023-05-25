#include "shell.h"

/**
 * handle_command - Handles the execution of a command in a shell program.
 * @args: Pointer to a pointer that holds the command arguments.
 * @program_name: Pointer to a string that holds the name of the shell program.
 * @env: Pointer to an array of strings representing the program's environment.
 * @exit_status: Pointer to the variable that holds the exit status.
 * @line_number: The line number where the command is encountered.
 * @path: Pointer to a string that holds the system's PATH variable.
 * Return: Nothing.
 */
void handle_command(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path)
{
	remove_double_quotes(args);
	handle_variable_replacement(args, exit_status);

	if (_strcmp(args[0], "exit") == 0)
		handle_exit_command(args, exit_status, program_name,
				line_number);
	else if (_strcmp(args[0], "cd") == 0)
		change_directory(args[1], exit_status,
				program_name, line_number);
	else if (_strcmp(args[0], "env") == 0)
		handle_env_command();
	else if (_strcmp(args[0], "setenv") == 0)
		handle_setenv_command(args[1], args[2], exit_status);
	else if (_strcmp(args[0], "unsetenv") == 0)
		handle_unset_command(args[1]);
	else if (_strcmp(args[0], "&&") == 0)
		handle_logic_op(args + 1, program_name, env, exit_status,
				line_number, path);
	else if (_strcmp(args[0], "alias") == 0)
		handle_alias_command(args);
	else
		handle_other_commands(args, program_name, env, exit_status,
				line_number, path);
}


/**
 * int_to_str - Converts an integer to a string.
 * @value: The integer value to convert.
 * @str: Pointer to a character array to store the resulting string.
 * @size: The size of the character array.
 * Return: Nothing.
 */
void int_to_str(int value, char *str, size_t size)
{
	size_t is_negative, i;
	int num_digits, temp;

	if (str == NULL || size == 0)
		return;
	is_negative = 0;
	if (value < 0)
	{
		is_negative = 1;
		value = -value;
	}
	num_digits = 1;
	temp = value;
	while (temp /= 10)
		num_digits++;
	if (num_digits + is_negative + 1 > size)
		return;

	i = num_digits + is_negative;
	while (i-- > is_negative)
	{
		str[i] = '0' + (value % 10);
		value /= 10;
	}
	if (is_negative)
	{
		str[0] = '-';
	}
	str[num_digits + is_negative] = '\0';
}

/**
 * handle_echo_command - Handles the "echo" command in a shell program.
 * @args: Pointer to a pointer that holds the command arguments.
 * @exit_status: Pointer to the variable that holds the exit status.
 * Return: Nothing.
 */
void handle_echo_command(char **args, int *exit_status)
{
	if (args[1] != NULL)
	{
		handle_echo_arguments(args + 1, exit_status);
	}
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * handle_echo_arguments - funtion that increments.
 * @args: Pointer to a pointer that holds the command arguments.
 * @exit_status: Pointer to the variable that holds the exit status.
 * Return: Nothing.
 */
void handle_echo_arguments(char **args,
		__attribute__((unused))int *exit_status)
{
	int i = 0;

	while (args[i] != NULL)
	{
		i++;
	}
}
