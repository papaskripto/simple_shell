#include "shell.h"

/**
 * my_setenv - sets an environment variable,
 * @head: double pointer to the environ linked list
 * @argv: name and value of the variable to set
 * @args: number of arguments
 *
 * Return: 0 on success, -1 on failure
 */
int my_setenv(env_t **head, char **argv, int args)
{
	char *buffer1 = NULL, *buffer2 = NULL;
	int index = 0;

	if (!head || !*head)
		return (0);

	if (args != 3)
		return (-1);

	buffer1 = mystr_concat(argv[1], "=");
	buffer2 = mystr_concat(buffer1, argv[2]);
	free(buffer1);

	index = index_list_fnd(*head, argv[1]);
	if (index == 0)
	{
		add_node_at_end(head, buffer2);
		free(buffer2);
		return (0);
	}

	if (index > 0)
	{
		delete_index_node(head, index);
		node_at_index(head, buffer2, index);
		free(buffer2);
		return (0);
	}

	free(buffer2);
	return (0);
}

/**
 * my_unsetenv - unsets an environment variable,
 * handles the unsetenv builtin
 * @head: double pointer to the environ linked list
 * @argv: array of strings, includes parsed line
 * Return: 0 on success, -1 on failure
 */
int my_unsetenv(env_t **head, char **argv)
{
	int index;

	if (!argv[1])
		return (-1);

	index = index_list_fnd(*head, argv[1]);
	if (index == 0 || !head || !*head)
		return (0);

	else
		delete_index_node(head, index);

	return (0);
}

/**
 * handle_setenv - handles the setenv and unsetenv builtins
 * @argv: array of arguments from the command line
 * @head: pointer to the env_t linked list
 * @i: index of the command in history
 * @progg_nme: name of the program
 *
 */
void handle_setenv(char **argv, env_t **head, int *i, char *progg_nme)
{
	int n = 0, m = 0, args = 0;
	char *unset_err = "unsetenv: Too few arguments.\n";

	while (argv[args])
		args++;

	if (!my_strcmp(argv[0], "setenv"))
	{
		n = my_setenv(head, argv, args);
		if (n == -1)
			print_setenv_error(i, progg_nme, argv);
	} else if (!my_strcmp(argv[0], "unsetenv"))
	{
		m = my_unsetenv(head, argv);
		if (m == -1)
			write(2, unset_err, my_strlen(unset_err));
	}
}

/**
 * print_setenv_error - prints a custom error message for setenv
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 *
 */
void print_setenv_error(int *i, char *s, char **argv)
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
	buffer5 = mystr_concat(buffer4, ": Bad variable name\n");
	free(buffer4);
	write(2, buffer5, my_strlen(buffer5));
	free(buffer5);
}
