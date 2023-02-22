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

#define PROMPT "ourshell $ "

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
char **token_interface(char *, const char *, int);
int count_token(char *, const char *);
char **tokenize(int, char *, const char *);
void create_child(char **, char *, int, char **);
void parse_line(char *, size_t, int, char **);
char *path_finder(char *);
int str_len(char *);
int find_path(char *);
char **tokenize_path(int, char *);
char *search_directories(char **, char *);
char *build_path(char *, char *);
void double_free(char **);
void single_free(int, ...);
int _strcmp(char *, char *);
char *_strdup(char *);
void print_str(char *, int);
int print_number(int);
int _write_char(char);
int _strlen(char *str);

/* builtins */
int built_in(char **, char *);
void (*get_builtins(char *))(char *);
void ourshell_exit(char *);
void ourshell_env(char *);
void ourshell_cd(char *);

/* error handling */

void error_printing(char *, int, char *);
void exec_error(char *, int, char *);

#endif

