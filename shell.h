#ifndef GF_H
#define GF_H
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stddef.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>
extern char **environ;

#define MAX_ALIASES 1024
#define MAX_COMMANDS 1024

/**
 * struct alias_s - Structure representing an alias in a shell program.
 * @name: Pointer to a string that holds the name of the alias.
 * @value: Pointer to a string that holds the value of the alias.
 * @next: Pointer to the next alias in the linked list.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;


#define MAX_PATHS 32
#define MAX_ARGC 1024
#define BUFFER_SIZE 4096


void execute_command(char *shell_name, char *command, char **args, char **env,
		int use_full_path, int line_number, int *exit_status);

void print_error(char *program_name, char *command, int status,
		int line_number);
void handle_input(char *path, char **env, char *program_name,
		int *exit_status);
void handle_command(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path);
void search_command(char **args, char *path, char *program_name,
		char **env, int *exit_status, int line_number);
void handle_exit(char *command, int *exit_status);
void split_tokens(char *buf, char **args, int max_args);

char *_getenv(const char *name);
void construct_full_path(char *full_path, const char *dir,
		const char *filename);


void *_my_realloc(void *ptr, unsigned int prev_size, unsigned int curr_size);
void handle_line_ptr(char **lineptr, size_t *n,
		char *buffer, size_t buffer_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t file_getline(char **lineptr, size_t *n, int file);


char *_strtok(char *str, const char *delim);
size_t _strspn(const char *str, const char *accept);
size_t _strcspn(const char *str, const char *reject);
char *_strchr(const char *str, int c);
int _strcmp(const char *s1, const char *s2);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
void *_memmove(void *destination, const void *source, size_t num_bytes);
int _strncmp(const char *s1, const char *s2, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strcat(char *dest, const char *src);
int _atoi(const char *s);

int _unsetenv(const char *name);
int _putenv(char *string);

int _setenv(const char *name, const char *value, int overwrite);
void set_environment_variable(char *variable, char *value);
void unset_environment_variable(char *variable);

void print_environment(void);

void free_split_string(char **strings);
char **split_string(const char *str, char delimiter);

void display_prompt(void);
void handle_file(char *file_path, char **env, char *program_name,
		char *path, int *exit_status);
int _feof(FILE *stream);

void run_cmds(char **commands, int num_commands, char **env,
		char *program_name, int *exit_status,
		char *path, int line_number);
void process_file(const char *filename, char **env, char *program_name,
		int *exit_status, char *path);
void file_exec(const char *filename, char **env, char *program_name,
		int *exit_status, char *path);
void trim_operator(char *command, const char *op);


int read_input(char **buf, size_t *len, char *program_name);


void process_input(char *buf, char *program_name, char **env, int *exit_status,
		int line_number, char *path);
void tokenize_input(char *buf, char **commands, int *num_commands);
void remove_op(char *command, char *op);
void handle_logic(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path);
int is_logical_operator(char *arg);

void remove_double_quotes(char **args);
void handle_variable_replacement(char **args, int *exit_status);

void handle_exit_command(char *arg, int *exit_status,
		char *program_name, int line_number);
void handle_setenv_command(char *arg1, char *arg2, int *exit_status);
void handle_unset_command(char *arg);
void handle_echo_command(char **args, int *exit_status);
void handle_echo_arguments(char **args, int *exit_status);

void handle_logic_op(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path);

void handle_alias_command(char **args);
void handle_other_commands(char **args, char *program_name, char **env,
		int *exit_status, int line_number, char *path);
void handle_alias_command_arguments(char *alias_value, char *program_name,
		char **env, int *exit_status, int line_number, char *path);

void handle_env_command(void);

void int_to_str(int value, char *str, size_t size);

long _strtol(const char *str, char **endptr, int base);
int _isdigit(int c);
int _isspace(int c);


void add_alias(const char *name, const char *value);
void print_aliases(void);
char *get_alias_value(const char *name);
void print_alias(const char *name, const char *value);
void print_alias_not_found(const char *alias);
void handle_alias(char **args);
char **split_string(const char *str, char delimiter);
void free_split_string(char **strings);
char *_strtok_r(char *str, const char *delim, char **saveptr);

void print_cd_error(const char *program_name, int line_number,
		const char *dir);
void change_directory(char *dir, int *exit_status, char *program_name,
		int line_number);
void change_dir_to(char *program_name, int line_number, int *exit_status);
void build_error_message(char *buffer, const char *program_name,
		const char *command, int status, int line_number);
char *_itoa(int num);
int num_len(int num);
char *_strncat(char *dest, const char *src, size_t n);
int get_base(int base, const char *str);
#endif
