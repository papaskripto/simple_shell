#include "shell.h"

/**
* cmd_exec -  executes commands
* @input: array of arguments from stdin
* @s: name of the program
* @i: index of error
* @head: linked list containing environment
* Return: return to main loop with 1 on success, or 0 on failure
*/

int cmd_exec(char **input, char *s, int *i, env_t **head)
{
	struct stat filestat;
	int status = 0;
	char *full_command = NULL, **env = NULL;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		print_error(i, s, input);
		free_ptr(input);
		exit(EXIT_SUCCESS);
	}
	if (child_pid == 0)
	{
		env = lst_2_arr(*head);
		if (get_env("PATH=", env)[0] != '/')
			execve(input[0], input, env);
		full_command = find_path(input, env);
		if (!full_command && !stat(input[0], &filestat))
		{
			if (execve(input[0], input, env) == -1)
			{
				print_error(i, s, input);
				free_ptr(input), free_ptr(env);
				return (0);
			}
			free_ptr(input);
			free_ptr(env);
		}
		if (execve(full_command, input, env) == -1)
		{
			print_error(i, s, input);
			free(full_command), free_ptr(input), free_ptr(env);
			exit(EXIT_SUCCESS);
		}
	}
	else
		wait(&status);
	free_ptr(input), free_ptr(env);
	return (1);
}

/**
 * main - simple command-line argument interpreter
 * prints a prompt and waits for the user to input a command,
 * then creates a child process in which it exececutes the command
 * @ac: number of arguments
 * @av: array of arguments
 *
 * Return: always 0, for success
 */
int main(int ac, char *av[])
{
	size_t len = 0;
	int cmd_count = 0, getline_output;
	char **input = NULL, *line = NULL, *progg_nme = av[0];
	env_t *head = NULL;

	if (ac != 1)
	{
		print_main_error(av);
		exit(127);
	}
	signal(SIGINT, handle_sigint);
	arr_2_lst(&head, environ);
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
			print_prompt();
		getline_output = getline(&line, &len, stdin);

		if (getline_output < 0)
		{
			if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
				my_putchar('\n');
			break;
		}
		cmd_count++;
		if (my_strcmp(line, "\n") == 0)
			continue;
		input = prs_lne(line, getline_output);
		if (!input)
			continue;
		if (check_builtin_cmd(line, input, progg_nme, &cmd_count, &head))
		{
			free_ptr(input);
			continue;
		}
		if (!cmd_exec(input, progg_nme, &cmd_count, &head))
			break;
	}
	fr_lst(&head), free(line);
	return (0);
}
