#include "shell.h"

/**
 * _itoa - Converts an integer to a string representation.
 * @num: The integer to be converted
 * Return: The string representation of the given integer.
 **/
char *_itoa(int num)
{
	char *buffer;
	int numcount = num_len(num);
	unsigned int out_num;

	buffer = malloc(sizeof(char) * (numcount + 1));
	if (!buffer)
		return (NULL);
	buffer[numcount] = '\0';
	if (num < 0)
	{
		out_num = num * -1;
		buffer[0] = '-';
	}
	else
	{
		out_num = num;
	}
	numcount--;
	do {
		buffer[numcount] = (out_num % 10) + '0';
		out_num /= 10;
		numcount--;
	} while (out_num > 0);

	return (buffer);
}


/**
 * num_len - Calculates the number of digits in an integer.
 * @num: The integer to calculate the number
 * Return: The number of digits in the given integer.
 **/
int num_len(int num)
{
	unsigned int out_num;
	int numcount = 1;

	if (num < 0)
	{
		numcount++;
		out_num = num * -1;
	}
	else
	{
		out_num = num;
	}
	while (out_num > 9)
	{
		numcount++;
		out_num /= 10;
	}

	return (numcount);
}

/**
 * _strncat - Concatenates  n characters fromsource string to the destination
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of characters to concatenate.
 * Return: char pointer
 **/
char *_strncat(char *dest, const char *src, size_t n)
{
	char *dest_start = dest;

	while (*dest)
	{
		dest++;
	}
	while (n > 0 && *src)
	{
		*dest++ = *src++;
		n--;
	}
	*dest = '\0';
	return (dest_start);
}

/**
 * print_error - Prints an error message with the provided details.
 * @program_name: The name of the program or command.
 * @command: The specific command or action related to the error.
 * @status: The status or code associated with the error.
 * @line_number: The line number where the error occurred
 * Return: void
 **/

void print_error(char *program_name, char *command,
		int status, int line_number)
{
	char error_buf[256];

	build_error_message(error_buf, program_name, command, status, line_number);
	write(STDERR_FILENO, error_buf, _strlen(error_buf));
}
