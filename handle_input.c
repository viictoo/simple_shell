#include "shell.h"

/**
 * handle_input - Handles the input from the user in a shell program.
 * @path: Pointer to a string that holds the system's PATH variable.
 * @env: Pointer to an array of strings.
 * @program_name: Pointer to a string that holds the name of the shell program.
 * @exit_status: Pointer to the variable that holds the exit status.
 * Return: Nothing.
 */
void handle_input(char *path, char **env, char *program_name, int *exit_status)
{
	char *input_buffer = NULL;
	size_t len = 0;
	int non_interactive = 0;
	int line_num = 0;

	while (1 && !non_interactive)
	{
		line_num++;
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
			fflush(stdout);
		}
		if (!isatty(STDIN_FILENO))
			non_interactive = 1;

		if (read_input(&input_buffer, &len, program_name) == 1)
			break;

		process_input(input_buffer, program_name, env,
				exit_status, line_num, path);
	}

	free(input_buffer);
}

/**
 * display_prompt - function to display the prompt "$ ".
 * Return: Nothing.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
	}
}

/**
 * read_input - Reads input from the user in a shell program.
 * @buf: Pointer to a pointer that holds the input buffer.
 * @len: Pointer to a size_t variable that holds the length of the input buffer
 * @program_name: Pointer to a string that holds the name of the shell program.
 * Return: number of characters read or -1.
 */
int read_input(char **buf, size_t *len, char *program_name)
{
	if (_getline(buf, len, stdin) == -1)
	{
		if (_feof(stdin))
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror(program_name);
			exit(EXIT_FAILURE);
		}
	}

	(*buf)[_strcspn(*buf, "\n")] = '\0';
	return (0);
}

/**
 * _feof - Checks if the end-of-file indicator is set for a stream.
 * @stream: Pointer to the FILE object representing the stream to check.
 * Return: 0 Success.
 */
int _feof(__attribute__((unused))FILE * stream)
{
	char data_buff[1];
	int fd = open("/dev/null", O_RDONLY);
	int result = read(fd, data_buff, 1);

	close(fd);

	if (result == 0 || result == -1)
	{
		return (1);
	}

	return (0);
}

