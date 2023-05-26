#include "shell.h"

/**
 * _my_realloc - Reallocate memory for a previously allocated block.
 * @ptr: Pointer to the previously allocated block of memory.
 * @prev_size: Size of the previously allocated block.
 * @curr_size: Size of the new block to be allocated.
 * Return: Pointer to the newly allocated block or Null.
 */
void *_my_realloc(void *ptr, unsigned int prev_size, unsigned int curr_size)
{
	void *mem_block;
	char *ptr_dup, *pad;
	unsigned int idx;

	if (curr_size == prev_size)
		return (ptr);

	if (!ptr)
	{
		mem_block = malloc(curr_size);
		if (mem_block == NULL)
			return (NULL);

		return (mem_block);
	}

	if (curr_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}

	ptr_dup = ptr;
	mem_block = malloc(sizeof(*ptr_dup) * curr_size);
	if (mem_block == NULL)
	{
		free(ptr);
		return (NULL);
	}

	pad = mem_block;

	for (idx = 0; idx < prev_size && idx < curr_size; idx++)
		pad[idx] = *ptr_dup++;

	free(ptr);
	return (mem_block);
}

/**
 * handle_line_ptr - Updates the lineptr and n variables with
 * the contents of buff.
 * @lineptr: Pointer to a pointer that holds the line contents.
 * @n: Pointer to the variable that holds the size of the allocated buffer.
 * @buff: Buffer containing the new line contents.
 * @buffer_size: Size of the buffer.
 * Return: Nothing.
 */
void handle_line_ptr(char **lineptr, size_t *n, char *buff, size_t buffer_size)
{
	if (*lineptr == NULL)
	{
		if (buffer_size > 120)
			*n = buffer_size;
		else
			*n = 120;
		*lineptr = buff;
	}
	else if (*n < buffer_size)
	{
		if (buffer_size > 120)
			*n = buffer_size;
		else
			*n = 120;
		*lineptr = buff;
	}
	else
	{
		charcopy(*lineptr, buff);
		free(buff);
	}
}


/**
 * _getline - Reads a line from a stream.
 * @lineptr: Pointer to pointer that will store the line contents.
 * @n: Pointer to the variable that will store the size of the allocated buffer
 * @stream: Pointer to the input stream to read from.
 * Return: The number of characters read or 0
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char key_char = 'x', *buff;
	static ssize_t string;
	ssize_t ret_value;
	int val;

	if (string == 0)
		fflush(stream);
	else
		return (-1);
	string = 0;
	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (key_char != '\n')
	{
		val = read(STDIN_FILENO, &key_char, 1);
		if (val == -1 || (val == 0 && string == 0))
		{
			free(buff);
			return (-1);
		}
		if (val == 0 && string != 0)
		{
			string++;
			break;
		}
		if (string >= 120)
			buff = _my_realloc(buff, string, string + 1);
		buff[string] = key_char;
		string++;
	}
	buff[string] = '\0';
	handle_line_ptr(lineptr, n, buff, string);
	ret_value = string;
	if (val != 0)
		string = 0;
	return (ret_value);
}

/**
 * file_getline - Reads a line from a file descriptor.
 * @lineptr: Pointer to a pointer that will store the line contents.
 * @n: Pointer to the variable that will store.
 * @file: file descriptor.
 * Return: The number of characters read or 0.
 */
ssize_t file_getline(char **lineptr, size_t *n, int file)
{
	char key_char = 'x', *buff;
	static ssize_t string;
	ssize_t ret_value;
	int val;

	if (string == 0)
		fflush(stdout);
	else
		return (-1);
	string = 0;
	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);
	while (key_char != '\n')
	{
		val = read(file, &key_char, 1);
		if (val == -1 || (val == 0 && string == 0))
		{
			free(buff);
			return (-1);
		}
		if (val == 0 && string != 0)
		{
			string++;
			break;
		}
		if (string >= 120)
			buff = _my_realloc(buff, string, string + 1);
		buff[string] = key_char;
		string++;
	}
	buff[string] = '\0';
	handle_line_ptr(lineptr, n, buff, string);
	ret_value = string;
	if (val != 0)
		string = 0;

	return (ret_value);
}

