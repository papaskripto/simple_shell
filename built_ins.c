#include "shell.h"

/**
 * check_builtin_cmd - checks if the command is built in
 * @line: input line
 * @progg_nme: name of the program
 * @i: pointer to a variable
 * @argv: parsed command line
 * @head: double pointer to the environ linked list
 *
 * Return: Always 0 (Success)
 */
int check_builtin_cmd(char *line, char **argv, char *progg_nme,
		int *i, env_t **head)
{
	int a, l;
	long int b;

	if (!my_strcmp(argv[0], "exit"))
	{
		b = handle_exit(argv);
		if (b == -1)
			print_exit_error(i, progg_nme, argv);
		else
		{
			free_ptr(argv);
			free(line);
			fr_lst(head);
			exit(b);
		}
		return (1);
	}
	if (!my_strcmp(argv[0], "env"))
	{
		a = handle_env(argv, head);
		if (a == -1)
			print_env_error(argv);
		return (1);
	}
	if (!my_strcmp(argv[0], "setenv") || !my_strcmp(argv[0], "unsetenv"))
	{
		handle_setenv(argv, head, i, progg_nme);
		return (1);
	}
	if (!my_strcmp(argv[0], "cd"))
	{
		l = handle_cd(argv, head);
		if (l == -1)
		{
			print_cd_error(i, progg_nme, argv);
			write(2, "\n", 1);
		}
		return (1);
	}
	return (0);
}

/**
 * handle_exit - handles the builtin exit
 * @tokens: array of strings from the cmd
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
		num = atoi_(tokens[1]);
		return (num);
	}
	return (-1);
}

/**
 * handle_env - eumlates the bash env builtin
 * @arv: array of arguments from the command line
 * @head: double pointer to the env_t linked list
 *
 * Return: 0 on success, -1 on error
 */
int handle_env(char **arv, env_t **head)
{
	if (arv[1] == NULL)
	{
		prt_lst(*head);
		return (0);
	}
	return (-1);
}

/**
 * handle_cd - handles bash builtin cd command
 * @arv: array of arguments from the command line
 * @head: double pointer to the env_t linked list
 * Return: 0
 *
 */
int handle_cd(char **arv, env_t **head)
{
	char *home = NULL, *old = NULL, **env = NULL;

	env = lst_2_arr(*head);
	if (!arv[1])
	{
		home = get_env("HOME=", env);
		chdir(home);
		handle_pwd(home, env, head);
		free_ptr(env);
		return (1);
	}
	if (my_strcmp(arv[1], "-") == 0)
	{
		old = get_env("OLDPWD=", env);
		my_puts(old);
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
/**
 *  handle_pwd - helper function for cd
 *  @path: path of the working directories we want to change to
 *  @head: double pointer to the env_t linked list
 *  @env: double array containing the environment
 */

void handle_pwd(char *path, char **env, env_t **head)
{
	char **old = NULL, **current = NULL;
	int nodes = 0, set = 0;

	old = malloc(sizeof(char *) * 4);
	old[0] = my_strdup("old");
	old[1] = my_strdup("OLDPWD");
	old[2] = my_strdup(get_env("PWD=", env));
	old[3] = NULL;
	current = malloc(sizeof(char *) * 4);
	current[0] = my_strdup("current");
	current[1] = my_strdup("PWD");
	current[2] = my_strdup(path);
	current[3] = NULL;
	nodes = arr_2_lst(head, env);
	if (!nodes)
		return;
	set = my_setenv(head, old, 2);
	if (set < 0)
	{
		free_ptr(old);
		free_ptr(current);
		return;
	}
	free_ptr(old);
	set = my_setenv(head, current, 2);
	if (set < 0)
	{
		free_ptr(current);
		return;
	}
	free_ptr(current);
}
