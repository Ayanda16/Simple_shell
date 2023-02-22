#include"main.h"

/**
 * _strcat - Function to concatenate the value character by
 * character of src to dest.
 * Description: "/bin" "ls" = "/bin/ls" - "src/dest" <-- e. Expected output.
 * @dest: Variable on representetion of a program.
 * @src: Variable on representatio of the program path.
 * Return: Success (s_concat), string concatenated.
 */

char *_strcat(char *dest, char *src)
{
	char *s_concat = NULL;
	int lendest = 0, lensrc = 0, i_s = 0, idest = 0;

	if (dest && src)
	{
		lendest = _strlen(dest);
		lensrc = _strlen(src);
		s_concat = malloc(sizeof(char) * (lendest + lensrc + 2));

		if (s_concat)
		{
			while (src[i_s])
			{
				s_concat[i_s] = src[i_s];
				i_s++;
			}
			s_concat[i_s++] = '/';

			while (dest[idest])
			{
				s_concat[i_s] = dest[idest];
				idest++;
				i_s++;
			}
			s_concat[i_s] = '\0';
			return (s_concat);
		}
	}
	perror("_strcat - Unable to find dest and src.");
	return (NULL);
}

/**
 * _strcmp - compare 2 strings.
 * @s1: first string
 * @s2: second string
 * Return: Success (0) if both strings contains the same characters.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
 * _strlen - Function to find the length of a string.
 *  @str: String to be counted.
 *  Return: Then length of the string whitout the las character '\0'.
 */

int _strlen(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{}

	return (i);
}

/**
 * _strdup - create a copy of a string
 * @src: Contains the original string
 * Return: Gives back the copy of string
 */

char *_strdup(char *src)
{
	int i;
	int len;
	char *dest;

	len = _strlen(src);
	dest = malloc(sizeof(char) * (len + 1));

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * print_str - Prints a string character by character.
 * @str: String to be printed. If the string is NULL it will print (null)
 * @new_line: If integer is 0 a new line will be printed. Otherwise a new line
 * will not be printed.
 */
void print_str(char *str, int new_line)
{
	int i;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
		write(STDOUT_FILENO, &str[i], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}
