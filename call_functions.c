#include"main.h"

/**
 * parse_line - Parses the command line looking for commands and argumements.
 * This function it is also in charged of freeing memory that is not longer
 * needed by the program.
 * @command: A pointer to a string. Will always be NULL upon function entry.
 * @size: A holder for numbers of size_t. Will always be initilized to 0.
 * @command_counter: A counter keeping track of how many commands have been
 * entered into the shell.
 * @argv: commands parsed to the program
 */

void parse_line(char *command, size_t size, int command_counter, char **argv)
{
	int i;
	ssize_t read_len;
	int token_count;
	char **aop;
	const char *delim = "\n\t ";

	token_count = 0;
	write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));
	read_len = getline(&command, &size, stdin);
	if (read_len != -1)
	{
		aop = token_interface(command, delim, token_count);
		if (aop[0] == NULL)
		{
			single_free(2, aop, command);
			return;
		}
		i = built_in(aop, command);
		if (i == -1)
			create_child(aop, command, command_counter, argv);
		for (i = 0; aop[i] != NULL; i++)
			free(aop[i]);
		single_free(2, aop, command);
	}
	else
		ourshell_exit(command);
}

/**
 * create_child - Creates a child in order to execute another program.
 * @aop: An array of parameters
 * of a program and its parameters. This array is NULL terminated.
 * @command: The contents of the read line.
 * @count: A counter keeping track of how many commands have been entered
 * into the shell.
 * @argv: arguments parsed to the program
 */
void create_child(char **aop, char *command, int count, char **argv)
{
	pid_t id;
	int status;
	int i;
	int check;
	struct stat buf;
	char *tmp_string;
	char *string;

	id = fork();
	if (id == 0)
	{
		tmp_string = aop[0];
		string = path_finder(aop[0]);
		if (string == NULL)
		{
			check = stat(tmp_string, &buf);
			if (check == -1)
			{
				error_printing(argv[0], count, tmp_string);
				print_str(": not found", 0);
				single_free(2, command, tmp_string);
				for (i = 1; aop[i]; i++)
					free(aop[i]);
				free(aop);
				exit(100);
			}
			string = tmp_string;
		}
		aop[0] = string;
		if (aop[0] != NULL)
		{
			if (execve(aop[0], aop, environ) == -1)
				exec_error(argv[0], count, tmp_string);
		}
	}
	else
		wait(&status);
}

/**
 * token_interface - Meant to interact with other token functions, and make
 * them more accessible to other parts of the program.
 * @command: A string containing the raw user input.
 * @delim: A constant string containing the desired delimeter to tokenize line.
 * @token_count: A holder for the amount of tokens in a string.
 * Return: Upon success an array of tokens representing the command. Otherwise
 * returns NULL.
 */

char **token_interface(char *command, const char *delim, int token_count)
{
	char **aop;

	token_count = count_token(command, delim);
	if (token_count == -1)
	{
		free(command);
		return (NULL);
	}
	aop = tokenize(token_count, command, delim);
	if (aop == NULL)
	{
		free(command);
		return (NULL);
	}

	return (aop);
}

/**
 * tokenize - Separates a string into an array of tokens. DON'T FORGET TO FREE
 * on receiving function when using tokenize.
 * @command: A string containing the raw user input.
 * @delim: A constant string containing the desired delimeter to tokenize line
 * @token_count: An integer representing the amount of tokens in the array.
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL.
 */
char **tokenize(int token_count, char *command, const char *delim)
{
	int i;
	char **buffer;
	char *token;
	char *command_cp;

	command_cp = _strdup(command);
	buffer = malloc(sizeof(char *) * (token_count + 1));
	if (buffer == NULL)
		return (NULL);
	token = strtok(command_cp, delim);
	for (i = 0; token != NULL; i++)
	{
		buffer[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	buffer[i] = NULL;
	free(command_cp);
	return (buffer);
}

/**
 * count_token - Counts tokens in the passed string.
 * @command: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 * Return: Upon success the total count of the tokens. Otherwise -1.
 */
int count_token(char *command, const char *delim)
{
	char *str;
	char *token;
	int i;

	str = _strdup(command);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(str);
	return (i);
}
