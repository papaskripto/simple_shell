#include "shell.h"

/**
 * print_error - prints a custom error message
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 *
 */
void print_error(int *i, char *s, char **argv)
{
	char *buffer1 = NULL, *buffer2 = NULL, *buffer3 = NULL,
	     *buffer4 = NULL, *buffer5 = NULL;
	char *number = NULL;

	number = convert_num_str(*i, 10);

	buffer1 = mystr_concat(s, ": ");
	buffer2 = mystr_concat(buffer1, number);
	free(buffer1);
	buffer3 = mystr_concat(buffer2, ": ");
	free(buffer2);
	buffer4 = mystr_concat(buffer3, argv[0]);
	free(buffer3);
	buffer5 = mystr_concat(buffer4, ": not found\n");
	free(buffer4);
	write(2, buffer5, my_strlen(buffer5));
	free(buffer5);
}

/**
 * print_env_error - prints a custom error message for env builtin
 * @argv: array of arguments from the command line
 */
void print_env_error(char **argv)
{
	char *buffer1 = NULL, *buffer2 = NULL, *buffer3 = NULL;

	buffer1 = mystr_concat(argv[0], ": ");
	buffer2 = mystr_concat(buffer1, argv[1]);
	free(buffer1);
	buffer3 = mystr_concat(buffer2, ": No such file or directory\n");
	free(buffer2);
	write(2, buffer3, my_strlen(buffer3));
	free(buffer3);
}

/**
 * print_exit_error - prints a custom error message for exit builtin
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 */

void print_exit_error(int *i, char *s, char **argv)
{
	char *buffer1 = NULL, *buffer2 = NULL, *buffer3 = NULL;
	char *buffer4 = NULL, *buffer5 = NULL, *buffer6 = NULL, *buffer7 = NULL;
	char *number = NULL;

	number = convert_num_str(*i, 10);

	buffer1 = mystr_concat(s, ": ");

	buffer2 = mystr_concat(buffer1, number);
	free(buffer1);
	buffer3 = mystr_concat(buffer2, ": ");
	free(buffer2);
	buffer4 = mystr_concat(buffer3, argv[0]);
	free(buffer3);
	buffer5 = mystr_concat(buffer4, ": Illegal number: ");
	free(buffer4);
	buffer6 = mystr_concat(buffer5, argv[1]);
	free(buffer5);
	buffer7 = mystr_concat(buffer6, "\n");
	free(buffer6);
	write(2, buffer7, my_strlen(buffer7));
	free(buffer7);
}

/**
 * print_main_error - prints a custom error message for main
 * @av: array of arguments passed to main
 */

void print_main_error(char **av)
{
	char *buffer1 = NULL, *buffer2 = NULL, *buffer3 = NULL;

	buffer1 = mystr_concat(av[0], ": 0: Can't open ");
	buffer2 = mystr_concat(buffer1, av[1]);
	free(buffer1);
	buffer3 = mystr_concat(buffer2, "\n");
	free(buffer2);
	write(2, buffer3, my_strlen(buffer3));
	free(buffer3);
}

/**
 * print_cd_error - prints a custom error message for cd
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 *
 */
void print_cd_error(int *i, char *s, char **argv)
{
	char *buffer1 = NULL, *buffer2 = NULL, *buffer3 = NULL, *buffer4 = NULL;
	char *buffer5 = NULL, *buffer6 = NULL;
	char *number = NULL;

	number = convert_num_str(*i, 10);

	buffer1 = mystr_concat(s, ": ");
	buffer2 = mystr_concat(buffer1, number);
	free(buffer1);
	buffer3 = mystr_concat(buffer2, ": ");
	free(buffer2);
	buffer4 = mystr_concat(buffer3, argv[0]);
	free(buffer3);
	buffer5 = mystr_concat(buffer4, ": can't cd to ");
	free(buffer4);
	buffer6 = mystr_concat(buffer5, argv[1]);
	free(buffer5);
	write(2, buffer6, my_strlen(buffer6));
	free(buffer6);
}
