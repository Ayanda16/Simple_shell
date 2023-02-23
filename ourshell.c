#include"main.h"

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */

void sig_handler(int sig)
{
	char *prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, prompt, 3);
}

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

	do {
		command_counter++;
		command = NULL;
		size = 0;
		parse_line(command, size, command_counter, argv);

	} while (1);

	return (0);
}
