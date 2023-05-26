#include "shell.h"

/**
 * tokenize_input - input buffer to individual commands.
 * @buf: input buffer
 * @commands: array to store the individual commands.
 * @num_commands: number of commands
 * Return: void
 **/

void tokenize_input(char *buf, char **commands, int *num_commands)
{
	char *token = _strtok(buf, ";");

	while (token != NULL && *num_commands < MAX_COMMANDS)
	{
		commands[*num_commands] = token;
		(*num_commands)++;
		token = _strtok(NULL, ";");
	}
}
/**
 * split_tokens - Splits string into tokens.
 * @buf: string to be split
 * @args: array to store the tokens.
 * @max_args: The max number of tokens to be stored
 * Return: void
 **/
void split_tokens(char *buf, char **args, int max_args)
{
	char *token = _strtok(buf, " ;");
	int arg_count = 0;

	while (token != NULL && arg_count < max_args)
	{
		args[arg_count++] = token;
		token = _strtok(NULL, " ;");
	}

	args[arg_count] = NULL;
}
/**
 *  remove_op - Removes a specified operator from string.
 * @command: string from which the operator will be removed.
 * @op: The operator to be removed
 * Return: void
 **/
void remove_op(char *command, char *op)
{
	int operator_length = _strspn(command, " \t") + charlen(op);

	_memmove(command, command + operator_length,
			charlen(command) - operator_length + 1);
}

/**
 * execute_command - Executes a command
 * @shell_name: The name of the programme
 * @command: command to be executed.
 * @args: array for the command.
 * @env: environment variables.
 * @use_full_path: Flag whether to use the full path for the command.
 * @line_number: The line number of the command in the input.
 * @exit_status: Pointer to the exit status variable
 * Return: VOID
 **/

void execute_command(char *shell_name, char *command, char **args, char **env,
		__attribute__((unused))int use_full_path, int line_number, int *exit_status)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("Not able to fork");
		*exit_status = 1;
	} else if (pid == 0)
	{

		if (execve(command, args, env) == -1)
		{
			if (errno == ENOENT)
			{
				print_error(shell_name, command, 127, line_number);
				exit(127);
			} else if (errno == EACCES)
			{
				print_error(shell_name, command, 126, line_number);
				exit(126);
			}
			else
			{
				print_error(shell_name, command, 9, line_number);
				exit(9);
			}
		}
	} else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			*exit_status = WEXITSTATUS(status);

		}
	}
}
