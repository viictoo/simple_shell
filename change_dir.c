#include "shell.h"

/**
 * print_cd_error - Prints an error message related to the "cd" command.
 * @program_name: The name of the program or command.
 * @line_number: The line number where the error occurred.
 * @dir: The directory for which the error message is generated.
 * Return: NULL
 **/
void print_cd_error(const char *program_name, int line_number, const char *dir)
{
	const char *error_message = ": cd: can't cd to ";

	write(STDERR_FILENO, program_name, charlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, _itoa(line_number), charlen(_itoa(line_number)));
	write(STDERR_FILENO, error_message, charlen(error_message));
	write(STDERR_FILENO, dir, charlen(dir));
	write(STDERR_FILENO, "\n", 1);
}
/**
 * change_directory - Changes the current working directory.
 * @dir: The dire to change to. If NULL, changes to the home directory.
 * @exit_status: Pointer to the exit status variable.
 * @program_name: The name of the program or command.
 * @line_number: The line number where the function is called.
 * Return: None.
 **/
void change_directory(char *dir, int *exit_status,
		char *program_name, int line_number)
{
	const char *home = _getenv("HOME");
	char cwd[1024];

	if (dir == NULL)
	{
		if (chdir(home) == -1)
			perror("cd");
	} else if (charcmp(dir, "-") == 0)
	{
		change_dir_to(program_name, line_number, exit_status);

	} else
	{
		if (chdir(dir) == -1)
		{
			print_cd_error(program_name, line_number, dir);
		} else
		{

			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				_setenv("OLDPWD", _getenv("PWD"), 1);
				_setenv("PWD", cwd, 1);

			} else
			{
				perror("getcwd");
			}
		}
	}
}

/**
 *  change_dir_to - Changes to the specified directory.
 * @program_name: name of the program or command.
 * @line_number: The line number
 * @exit_status: exit status
 * Return: void
 **/
void change_dir_to(char *program_name, int line_number, int *exit_status)
{
	const char *previous_dir = _getenv("OLDPWD");
	const char *error_message = "cd: OLDPWD not set\n";
	char cwd[1024];

	if (previous_dir != NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			write(STDOUT_FILENO, previous_dir, charlen(previous_dir));
			write(STDOUT_FILENO, "\n", 1);
			if (chdir(previous_dir) == -1)
			{
				print_cd_error(program_name, line_number, "-");
				*exit_status = 2;
			}
			else
			{
				_setenv("OLDPWD", _getenv("PWD"), 1);
				_setenv("PWD", previous_dir, 1);
			}
		}
		else
			perror("getcwd");
	}
	else
	{
		write(STDERR_FILENO, error_message, charlen(error_message));
	}
}

/**
 * build_error_message - Builds an error message
 * @buffer: store the error message.
 * @program_name: The name of the program
 * @command: The specific command related to the error.
 * @status: The error status
 * @line_number: line number where the error occurred.
 * Return: void
 **/
void build_error_message(char *buffer, const char *program_name,
		const char *command, int status, int line_number)
{
	const char *error_msg = NULL;
	char line_number_str[12];
	size_t command_length;

	int_to_str(line_number, line_number_str, sizeof(line_number_str));
	if (status == 126)
	{
		error_msg = ": Permission denied\n";
	} else if (status == 23)
	{
		error_msg = ": exit: Illegal number: ";
		charcopy(buffer, program_name);
		_strcat(buffer, ": ");
		_strcat(buffer, line_number_str);
		_strcat(buffer, ": exit: Illegal number: ");
		_strcat(buffer, command);
		_strcat(buffer, "\n");
		return;
	}
	else
	{
		error_msg = ": not found\n";
	}
	charcopy(buffer, program_name);
	_strcat(buffer, ": ");
	_strcat(buffer, line_number_str);
	_strcat(buffer, ": ");
	command_length = charlen(command);
	if (command_length > 0 && _isspace((unsigned char)command[0]))
	{

		_strncat(buffer, command, command_length);
	} else
	{
		while (_isspace((unsigned char)*command))
			command++;
		_strcat(buffer, command);
	}
	_strcat(buffer, error_msg);
}

