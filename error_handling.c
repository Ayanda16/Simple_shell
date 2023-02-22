#include"main.h"

/**
 * error_printing - Prints a message error when a comand is not found.
 * @count: A counter keeping track of the number of commands run on the shell.
 * @argv: arguments parsed to the program.
 * @string: The specific command not being found.
 */

void error_printing(char *argv, int count, char *string)
{
	print_str(argv, 1);
	print_str(": ", 1);
	print_number(count);
	print_str(": ", 1);
	print_str(string, 1);
}

/**
 * exec_error - Prints exec errors.
 * @argv: The name of the program running the shell.
 * @count: Keeps track of how many commands have been entered.
 * @tmp_string: The command that filed.
 */

void exec_error(char *argv, int count, char *tmp_string)
{
	error_printing(argv, count, tmp_string);
	print_str(": ", 1);
	perror("");
	exit(1);
}

/**
 * print_number - Prints an unsigned number
 * @n: unsigned integer to be printed
 * Return: The amount of numbers printed
 */
int print_number(int n)
{
	int div;
	int len;
	unsigned int num;

	div = 1;
	len = 0;

	num = n;

	for (; num / div > 9; )
		div *= 10;

	for (; div != 0; )
	{
		len += _write_char('0' + num / div);
		num %= div;
		div /= 10;
	}

	return (len);
}

/**
 * _write_char - Writes a character to stdout
 * @c: Character that will be written to stdout
 * Return: Upon success how many characters were written.
 */

int _write_char(char c)
{
	return (write(1, &c, 1));
}
