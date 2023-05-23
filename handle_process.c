#include "shell.h"

/**
 * process_input - Processes the  line.
 * @buf: The input line to be processed.
 * @program_name: name of the program.
 * @env: An array of strings containing the environment variables.
 * @exit_status: Pointer to the exit status of the shell.
 * @line_number: The line number of the command in the input file.
 * @path: The PATH variable containing the directories
 * Return: None.
 **/
void process_input(char *buf, char *program_name,
		char **env, int *exit_status, int line_number, char *path)
{
	char *commands[MAX_COMMANDS];
	int num_commands = 0, i, is_hash = 0;
	char *args[MAX_ARGC], *command;

	tokenize_input(buf, commands, &num_commands);

	for (i = 0; i < num_commands; i++)
	{
		command = commands[i];

		split_tokens(command, args, MAX_ARGC);

		if (args[0] == NULL)
		continue;
		while (args[is_hash] != NULL)
		{
			if (args[is_hash][0] == '#')
			{
				args[is_hash] = NULL;
				break;
			}
			is_hash++;
		}
		handle_logic(args, program_name, env, exit_status, line_number, path);
	}

}

/**
 * handle_logic - Handlescommands involving logical operators
 * @args: strings containing the command and its arguments.
 * @program_name: name of the program.
 * @env: strings containing the environment variables.
 * @exit_status: Pointer to the exit status of the shell.
 * @line_number: The line number of the command in the input file.
 * @path: The PATH variable containing the directories
 * Return: void.
 */
void handle_logic(char **args, char *program_name,
		char **env, int *exit_status, int line_number, char *path)
{
	int j = 0;
	int should_continue = 1;
	int temp_args_index = 0;
	char *temp_args[MAX_ARGC];

	while (args[j] != NULL && should_continue)
	{
		if (is_logical_operator(args[j]))
		{
			break;
		}
		temp_args_index = 0;
		while (args[j] != NULL && !is_logical_operator(args[j]))
		{
			temp_args[temp_args_index++] = args[j];
			j++;
		}
		temp_args[temp_args_index] = NULL;
		handle_command(temp_args, program_name, env,
				exit_status, line_number, path);

		if (args[j] != NULL)
		{
			if (_strcmp(args[j], "&&") == 0 && *exit_status != 0)
			{
				should_continue = 0;
			} else if (_strcmp(args[j], "||") == 0 && *exit_status == 0)
			{
				should_continue = 0;
			}
			j++;
		}
	}
}
/**
 * is_logical_operator - Checks for logical operator.
 * @arg: The string to be checked.
 * Return: 1 if logical operator, 0 otherwise.
 **/

int is_logical_operator(char *arg)
{
	return (_strcmp(arg, "&&") == 0 || _strcmp(arg, "||") == 0);
}
