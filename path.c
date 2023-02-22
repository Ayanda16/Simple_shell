#include"main.h"

/**
 * path_finder - Function to find the the full path in the program environment.
 * @string: represents a command passed to the stdin
 * Return: full path
 */

char *path_finder(char *string)
{
	char *str = "PATH";
	char *new;
	char **pathtok;
	int index;
	char *dir;

	index = find_path(str);
	pathtok = tokenize_path(index, str);
	if (pathtok == NULL)
		return (NULL);

	dir = search_directories(pathtok, string);
	if (dir == NULL)
	{
		double_free(pathtok);
		return (NULL);
	}

	new = build_path(dir, string);
	if (new == NULL)
	{
		double_free(pathtok);
		return (NULL);
	}

	double_free(pathtok);

	return (new);
}

/**
 * double_free - Free double pointer variables.
 * @var: The address of the variable that need to be freed.
 */
void double_free(char **var)
{
	int index;

	for (index = 0; var[index] != NULL; index++)
		free(var[index]);
	free(var);
}

/**
 * find_path - Finds the index of an environmental variable.
 * @str: Environmental variable that needs to be found.
 * Return: Upon success returns the index of the environmental variable.
 * otherwise returns -1.
 */
int find_path(char *str)
{
	int i;
	int len;
	int j;

	len = strlen(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

/**
 * search_directories - Looks through directories stored in path_tokens for a
 * specific file. aka commmand.
 * @pathtok: A pointer to an array of strings representing the different
 * paths contained in the PATH environmental varible.
 * @string: Represents a command. For example ls, echo, pwd, /bin/ls etc.
 * Return: Upon success a string with the upper most directory containing
 * the command file. Otherwise returns NULL.
 */
char *search_directories(char **pathtok, char *string)
{
	int i, s;
	char *cwd;
	char *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
		return (NULL);
	if (string[0] == '/')
		string = string + 1;
	for (i = 0; pathtok[i] != NULL; i++)
	{
		s = chdir(pathtok[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(string, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (pathtok[i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}

/**
 * build_path - Combines two strings one representing the path directory and
 * one representing the command file.
 * @dir: Represents a directory in the path.
 * @string: Represents a file in a directory of the path.
 * Return: Upon success a string representing the full path of a command.
 * Otherwise NULL.
 */
char *build_path(char *dir, char *string)
{
	int i, j;
	int dir_len;
	int string_len;
	int len;
	char *built;

	if (dir == NULL || string == NULL)
		return (NULL);
	dir_len = strlen(dir) + 1;
	string_len = strlen(string) + 1;
	len = dir_len + string_len;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		for (j = 0; dir[j] != '\0'; j++, i++)
			built[i] = dir[j];
		built[i] = '/';
		i++;
		for (j = 0; string[j] != '\0'; j++, i++)
			built[i] = string[j];
	}
	built[--i] = '\0';
	return (built);
}
