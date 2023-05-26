#include "shell.h"


/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * @env: An array of strings containing the environment variables.
 * Return: Exit status of the program.
 */

int main(int argc, char **argv, char **env)
{
	int exit_status = 0;
	char *path_value = _getenv("PATH");
	int num_paths = 0;
	char *path_copy = chardup(path_value);
	char *dir = _strtok(path_copy, ":");


	while (dir != NULL && num_paths < MAX_PATHS)
		dir = _strtok(NULL, ":");
	if (argc == 2)
	{
		free(path_copy);
		handle_file(argv[1], env, argv[0], path_value, &exit_status);
	}
	else
	{
		free(path_copy);
		handle_input(path_value, env, argv[0], &exit_status);
	}

	return (exit_status);
}


/**
 * search_command - Search for a command in the specified path.
 * @args: An array of arguments passed to the command.
 * @path: The search path for the command.
 * @program_name: The name of the program invoking the command.
 * @env: An array of environment variables.
 * @exit_status: A pointer to store the exit status of the command.
 * @line_number: The line number where the command is located.
 * Return: Nothing.
 */

void search_command(char **args, char *path, char *program_name, char **env,
		int *exit_status, int line_number)
{
	char *p_copy = chardup(path), *full_path;
	char *dir = _strtok(p_copy, ":");
	int found = 0;

	while (dir != NULL)
	{
		full_path = malloc(charlen(dir) + charlen(args[0]) + 2);
		construct_full_path(full_path, dir, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			execute_command(program_name, full_path, args, env, 0,
					line_number, exit_status);
			found = 1;
			free(full_path);
			break;
		}
		free(full_path);

		dir = _strtok(NULL, ":");
	}

	if (!found)
	{
		print_error(program_name, args[0], 127, line_number);
		*exit_status = 127;
	}

	free(p_copy);
}

/**
 * handle_exit - Handle the exit command.
 * @command: The exit command string.
 * @exit_status: A pointer to store the exit status.
 * Return: Nothing.
 */

void handle_exit(char *command, int *exit_status)
{
	int exeunt;

	if (command != NULL)
	{
		exeunt = _atoi(command);
		*exit_status = exeunt;
	}
	exit(*exit_status);
}


/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable to retrieve.
 * Return: a pointer to the value of the environment variable or NULL.
 */
char *_getenv(const char *name)
{
	char **env_var = environ, *key_name, *val;

	while (*env_var != NULL)
	{
		key_name = *env_var;
		val = charchr(key_name, '=');

		if (val != NULL)
		{
			*val = '\0';
			if (charcmp(key_name, name) == 0)
			{
				*val = '=';
				return (val + 1);
			}
			*val = '=';
		}
		env_var++;
	}

	return (NULL);
}

/**
 * construct_full_path - Construct the full path of a file.
 * @full_path: A pointer to store the full path of the file.
 * @dir: The directory portion of the path.
 * @filename: The filename portion of the path.
 * Return: Nothing.
 */
void construct_full_path(char *full_path, const char *dir,
		const char *filename)
{
	char slash[2] = "/";

	charcopy(full_path, dir);
	_strcat(full_path, slash);
	_strcat(full_path, filename);
}
