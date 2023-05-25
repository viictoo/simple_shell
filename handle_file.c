#include "shell.h"

/**
 * handle_file - Handles a file as input to the shell program.
 * @file_path: The path to the file.
 * @env: The environment variables.
 * @program_name: The name of the program.
 * @path: The program path.
 * @exit_status: pointer to exit status.
 * Return: Nothing.
 */
void handle_file(char *file_path, char **env, char *program_name, char *path,
		int *exit_status)
{
	int file = open(file_path, O_RDONLY);
	char *lineText = NULL;
	size_t num_items = 0;
	int line_number = 0;
	ssize_t user_input;
	char *params[MAX_ARGC];
	const char *error_message = ": cannot open ";
	const char *error_message2 = ": No such file";

	if (file < 0)
	{
		write(STDERR_FILENO, program_name, _strlen(program_name));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, _itoa(line_number), _strlen(_itoa(line_number)));
		write(STDERR_FILENO, error_message, _strlen(error_message));
		write(STDERR_FILENO, file_path, _strlen(file_path));
		write(STDERR_FILENO, error_message2, _strlen(error_message2));
		write(STDERR_FILENO, "\n", 1);
		exit(2);
	}
	while ((user_input = file_getline(&lineText, &num_items, file)) != -1)
	{
		line_number++;
		lineText[user_input - 1] = '\0';
		split_tokens(lineText, params, MAX_ARGC);

		if (params[0] != NULL)
			handle_logic(params, program_name, env,
					exit_status, line_number, path);
	}

	free(lineText);
	close(file);
}


/**
 * run_cmds - Execute a series of commands based on given conditions
 * @commands: Array of commands to execute
 * @num_commands: Number of commands in the array
 * @env: Array of environment variables
 * @program_name: Name of the program
 * @exit_status: Pointer to the exit status
 * @path: Path variable
 * @line_number: Line number of the commands
 * Return: Nothing.
 */
void run_cmds(char **commands, int num_commands, char **env,
		char *program_name, int *exit_status,
		char *path, int line_number)
{
	char *command, *args[MAX_ARGC];
	int i, exec_flag;

	for (i = 0; i < num_commands; i++)
	{
		command = commands[i];

		split_tokens(command, args, MAX_ARGC);

		if (args[0] == NULL)
			continue;

		exec_flag = 1;
		if (_strcmp(args[0], "&&") == 0)
		{
			exec_flag = (*exit_status == 0);
		}
		else if (_strcmp(args[0], "||") == 0)
		{
			exec_flag = (*exit_status != 0);
		}

		if (exec_flag)
			handle_command(args, program_name, env, exit_status,
					line_number, path);

		if (i < num_commands - 1)
			trim_operator(commands[i + 1], args[0]);
	}
}


/**
 * trim_operator - Trim the operator prefix from a command
 * @command: Pointer to the command string
 * @op: Pointer to the op string to be removed
 * Return: Nothing.
 */
void trim_operator(char *command, const char *op)
{
	size_t operator_length = _strlen(op), new_length;
	size_t prefix_length = _strspn(command, " \t");
	size_t command_length = _strlen(command);

	if (prefix_length > 0 && command_length > operator_length)
	{
		new_length = command_length - prefix_length - operator_length;
		_memmove(command, command + prefix_length + operator_length,
				new_length + 1);
	}
}

/**
 * process_file - Process the contents of a file
 * @filename: Name of the file to process
 * @env: Array of environment variables
 * @program_name: Name of the program
 * @exit_status: Pointer to the exit status
 * @path: Path variable
 * Return: Nothing
 */
void process_file(const char *filename, char **env, char *program_name,
		int *exit_status, char *path)
{
	int file_desc = open(filename, O_RDONLY);
	char *buf = NULL, *commands[MAX_COMMANDS], *comment_start, *token;
	size_t num_items = 0, read_bytes;
	int line_number = 0, num_commands = 0;

	if (file_desc == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	while ((int)(read_bytes = file_getline(&buf, &num_items, file_desc)) != -1)
	{
		line_number++;
		buf[read_bytes - 1] = '\0';

		comment_start = _strchr(buf, '#');
		if (comment_start != NULL)
			*comment_start = '\0';

		token = _strtok(buf, ";");
		while (token != NULL && num_commands < MAX_COMMANDS)
		{
			commands[num_commands++] = token;
			token = _strtok(NULL, ";");
		}

		run_cmds(commands, num_commands, env, program_name,
				exit_status, path, line_number);
		num_commands = 0;
	}

	free(buf);
	close(file_desc);
}

/**
 * file_exec - Executes a file with specified parameters.
 * @filename: The name of the file to be executed.
 * @env: An array of environment variables.
 * @program_name: The name of the program being executed.
 * @exit_status: A pointer to store the exit status of the program.
 * @path: The search path for the executable file.
 * Return: Nothing.
 */
void file_exec(const char *filename, char **env, char *program_name,
		int *exit_status, char *path)
{
	process_file(filename, env, program_name, exit_status, path);
}
