#ifndef _ourshell_
#define _ourshell_

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdarg.h>
#include<signal.h>
#include<stddef.h>

#define PROMPT "$ "

/**
 * struct builtin_d - Defines the builtins functions.
 * @built: The name of the build in command.
 * @f: A pointer to the right builtin function.
 */

typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

/*global variable*/
extern char **environ;

/* functions */
char **token_interface(char *command, const char *delim, int token_count);
int count_token(char *command, const char *delim);
char **tokenize(int token_count, char *command, const char *delim);
void create_child(char **aop, char *command, int count, char **argv);
void parse_line(char *command, size_t size, int command_counter, char **argv);
char *path_finder(char *string;
int find_path(char *str);
char **tokenize_path(int index, char *str);
char *search_directories(char **pathtok, char *string);
char *build_path(char *dir, char *string);
void double_free(char **var);
void single_free(int n, ...);
int _strcmp(char *s1, char *s2);
char *_strdup(char *src);
void print_str(char *str, int new_line);
int print_number(int n);
int _write_char(char c);
int _strlen(char *str);

/* builtins */
int built_in(char **string, char *command);
void (*get_builtins(char *str))(char *str);
void ourshell_exit(char *command);
void ourshell_env(char *command);
void ourshell_cd(char *command);

/* error handling */

void error_printing(char *argv, int count, char *string);
void exec_error(char *argv, int count, char *tmp_string);

#endif

