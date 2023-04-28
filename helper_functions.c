#include "shell.h"

void handle_sigint(int sig)
{
	(void)sig;
	 _putchar('\n');
	 print_prompt();
	 fflush(stdout);
}

void free_ptr(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
}

char **prs_lne(char *line, int get)
{
	char **input = NULL;

	if (line[get - 1] == '\n')
		line[get - 1] = '\0';
	input = _strtok(line, ' ');

	return (input);
}
