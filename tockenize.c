#include"main.h"

/**
 * tokenize_path - Separates a string representing paths as an array
 * of strings contining the path directories.
 * @index: Index of the path in the environment variables.
 * @str: string to separate and tokenize.
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL. Note!: Do not forget to free alocated
 * memory on receiving function or when possible.
 */

char **tokenize_path(int index, char *str)
{
	char *env_var;
	int token_count;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = _strlen(str);
	token_count = 0;
	env_var = environ[index] + (len + 1);
	path_tokens = token_interface(env_var, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}
