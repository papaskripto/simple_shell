#include "shell.h"

/**
 * handle_sigint - doesn't exit in case of Ctrl-C
 * @sig: required for signal function to run properly
 * Return:0
 */
void handle_sigint(int sig)
{
	(void)sig;
	 my_putchar('\n');
	 print_prompt();
	 fflush(stdout);
}
/**
 * free_ptr - frees arrays of strings
 * @args: array of strings to free
 * Return:0
 */

void free_ptr(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
}
/**
* prs_lne - handle newline character if found, and parses the input line
* @line: line read from stdin
* @get: size of line returned from getline
*
* Return: parsed line
*/

char **prs_lne(char *line, int get)
{
	char **input = NULL;

	if (line[get - 1] == '\n')
		line[get - 1] = '\0';
	input = token_strtok(line, ' ');

	return (input);
}
