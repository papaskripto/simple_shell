#include "shell.h"

/**
 * my_putchar - writes the character c to standard output
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
	return (write(1, &c, 1));
}


/**
 * print_prompt - prints a prompt for the shell
 */
void print_prompt(void)
{
	char *s = "DGShell:😊$ ";

	write(1, s, 2);
}

/**
 * my_puts - prints a string to standard output
 * @str: pointer to the string to print
 */
void my_puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		my_putchar(str[i]);
	my_putchar('\n');
}
