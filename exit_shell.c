#include "shell.h"

/**
 * exit_shell - A function to handle the exit command of the shell
 * @input: The command input from the user
 * Returns: void
 */
void exit_shell(char *input)
{
	int exit_status = 0;
	int input_len = strlen(input);

	/* Check if input equals "exit" */
	if (input_len == 4 && input[0] == 'e' && input[1] == 'x' &&
		input[2] == 'i' && input[3] == 't')
	exit(0);

	/* Check if input starts with "exit " and tokenize the exit status */
	if (input_len > 5 && input[0] == 'e' && input[1] == 'x' &&
			input[2] == 'i' && input[3] == 't' && input[4] == ' ')
	{
		char *endptr;

		exit_status = strtol(input + 5, &endptr, 10);
		if (*endptr != '\0')
		{
			char *error_msg = "Invalid argument to exit\n";

			write(STDERR_FILENO, error_msg, strlen(error_msg));
			return;
		}
		exit(exit_status);
	}
}
