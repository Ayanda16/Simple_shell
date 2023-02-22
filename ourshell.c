#include"main.h"

/**
 * main - Entry point of the ourshell.
 * @argc: argument count UNUSED
 * @argv: pointer to arguments parsed to the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *command;
	size_t size;
	int command_counter;

	command_counter = 0;
	signal(SIGINT, SIG_IGN);
	do {
		command_counter++;
		command = NULL;
		size = 0;
		parse_line(command, size, command_counter, argv);

	} while (1);

	return (0);
}
