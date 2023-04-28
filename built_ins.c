#include "shell.h"

/**
 * check_builtin_cmd - checks if the command is built in
 * @line: input line
 * @progg_nme: name of the program
 * @i: pointer to a variable
 *
 * Return: Always 0 (Success)
 */
int check_builtin_cmd(char *line, char **argv, char *progg_nme, int *i, env_t **head)
{
	int a, l;
	long int b;

	if (!_strcmp(argv[0], "exit"))
	{
		b = hande_exit(argv);
		if (b == -1)
			print_error_exit(i, progg_nme, argv);
		else
		{
			free_ptr(argv);
			free(line);
			free_list(head);
			exit(m);
		}
		return (1);
	}
	if (!_strcmp(argv[0], "env"))
	{
		a = handling_env(argv, head);
		if (a == -1)
			print_error_env(argv);
		return (1);
	}
	if (!_strcmp(argv[0], "setenv") || !_strcmp(argv[0], "unsetenv"))
	{
		handling_setenv(argv, head, i, progg_nme);
		return (1);
	}
	if (!_strcmp(argv[0], "cd"))
	{
		l = handling(argv, head);
		if (l == -1)
		{
			print_error_cd(i, prog_name, argv);
			write(2, "\n", 1);
		}
		return (1);
	}
	return (0);
}

/**
 * handling_exit - handles the builtin exit
 * @tokens - array of strings from the cmd
 *
 * Return: 0 if there are no arguments,
 * -1 on failure, or the value of the argument
 */
long int handle_exit(char **tokens)
{
	int flag = 0, i;
	long int num = 0;

	if (tokens[1] == NULL)
		return (num);
	for (i = 0; tokens[1][i]; i++)
	{
		if ((tokens[1][i] >= '0' && tokens[1][i] <= '9') || tokens[1][0] == '+')
		{
			flag = 1;
			if (tokens[1][i + 1] < '0' || tokens[1][i + 1] > '9')
				break;
		}
		else
			break;
		flag = 0;
	}
	if (flag == 1)
	{
		num = _atoi(tokens[1]);
		return (num);
	}
	return (-1);
}

/**
 * handling_env - eumlates the bash env builtin
 * @arv: array of arguments from the command line
 * @head: double pointer to the env_t linked list
 *
 * Return: 0 on success, -1 on error
 */
int handle_env(char **arv, env_t **head)
{
	if (arv[1] == NULL)
	{
		print_list(*head);
		return (0);
	}
	return (-1);
}

/**
 * handling_cd - handles bash builtin cd command
 * @arv: array of arguments from the command line
 *
 */
int handling_cd(char **arv, env_t **head)
{
	char *home = NULL, *old = NULL, **env = NULL;

	env = list_to_arr(*head);
	if (!arv[1])
	{
		home = get_env_val("HOME=", env);
		chdir(home);
		handle_pwd(home, env, head);
		free_ptr(env);
		return (1);
	}
	if (_strcmp(arv[1], "-") == 0)
	{
		old = get_env_val("OLDPWD=", env);
		_puts(old);
		handle_pwd(old, env, head);
		chdir(old);
		free_ptr(env);
		return (1);
	}
	if (chdir(arv[1]) < 0)
	{
		free_ptr(env);
		return (-1);
	}
	else
	{
		handle_pwd(arv[1], env, head);
		free_ptr(env);
		return (1);
	}
	return (0);
}

void handle_pwd(char *path, char **env, env_t **head)
{
	char **old = NULL, **current = NULL;
	int nodes = 0, set = 0;

	old = malloc(sizeof(char *) * 4);
	old[0] = _strdup("old");
	old[1] = _strdup("OLDPWD");
	old[2] = _strdup(get_env_val("PWD=", env));
	old[3] = NULL;
	current = malloc(sizeof(char *) * 4);
	current[0] = _strdup("current");
	current[1] = _strdup("PWD");
	current[2] = _strdup(path);
	current[3] = NULL;
	nodes = arr_to_list(head, env);
	if (!nodes)
		return;
	set = _setenv(head, old, 2);
	if (set < 0)
	{
		free_ptr(old);
		free_ptr(current);
		return;
	}
	free_ptr(old);
	set = _setenv(head, current, 2);
	if (set < 0)
	{
		free_ptr(current);
		return;
	}
	free_ptr(current);
}
