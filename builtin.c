#include"main.h"

/**
 * ourshell_exit - Exits the shell. After freeing allocated resources.
 * @command: A string representing the input from the user.
 */
void ourshell_exit(char *command)
{
	free(command);
	print_str("\n", 1);
	exit(1);
}

/**
 * ourshell_env - Prints all the environmental variables in the current shell.
 * @command: A string representing the input from the user.
 */
void ourshell_env(__attribute__((unused))char *command)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * ourshell_cd - Changes the current working directory.
 * if no parameter is passed it will change directory to HOME.
 * @command: A string representing the input from the user.
 */
void ourshell_cd(char *command)
{
	int index;
	int token_count;
	char **aop;
	const char *delim = "\n\t ";

	token_count = 0;
	aop = token_interface(command, delim, token_count);
	if (aop[0] == NULL)
	{
		single_free(2, aop, command);
		return;
	}
	if (aop[1] == NULL)
	{
		index = find_path("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(aop[1], "-") == 0)
		print_str(aop[1], 0);

	else
		chdir(aop[1]);
	double_free(aop);
}

/**
 * get_builtins - Finds the right function needed for execution.
 * @str: The name of the function that is needed.
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*get_builtins(char *str))(char *str)
{
	int i;

	builtin_t buildin[] = {
		{"exit", ourshell_exit},
		{"env", ourshell_env},
		{"cd", ourshell_cd},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].f);
		}
	}
	return (NULL);
}

/**
 * built_in - Checks for builtin functions.
 * @string: An array of all the arguments passed to the shell.
 * @command: A string representing the input from the user.
 * Return: If function is found 0. Otherwise -1.
 */
int built_in(char **string, char *command)
{
	void (*build)(char *);

	build = get_builtins(string[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", string[0]) == 0)
		double_free(string);
	build(command);
	return (0);
}
