#include "shell.h"

/**
* get_env - gets the value of a environment variable
* @name: env key to check
* @env: array of strings containing environment copy
*
* Return: value of name in env
*/


char *get_env(char *name, char **env)
{
	int i;

	for (i = 0; env[i]; i++)
		if (my_strncmp(env[i], name, my_strlen(name)) == 0)
			return (env[i] + my_strlen(name));
	return (NULL);
}

/**
* get_env_path - transform the PATH string in an array of strings
* @name: key (key=value) to select in env
* @env: array of strings containing the environment copy
*
* Return: value at key, in the form of an array of strings
*/


char **get_env_path(char *name, char **env)
{
	char **value = NULL, **path = NULL;
	int i;

	for (i = 0; env[i]; i++)
	{
		path = token_strtok(env[i], '=');
		if (my_strcmp(name, path[0]) == 0)
		{
			value = token_strtok(path[1], ':');
			free_ptr(path);
			return (value);
		}
		else
			free_ptr(path);
	}
	free_ptr(path);
	free_ptr(value);
	return (NULL);
}
/**
* find_path - connect directories in PATH with input command
* to check if executable
* @s: input, in form array of strings
* @env: array of strings containing the environment copy
*
* Return: concatenated string on success, NULL on failure
*/


char *find_path(char **s, char **env)
{
	int i;
	char *dir = NULL;
	char *prog = NULL;
	char **value_of_path = NULL;

	value_of_path = get_env_path("PATH", env);
	if (!value_of_path)
	{
		free_ptr(value_of_path);
		return (NULL);
	}

	for (i = 0; value_of_path[i]; i++)
	{
		dir = mystr_concat(value_of_path[i], "/");
		prog = mystr_concat(dir, s[0]);

		if (access(prog, X_OK) == 0)
		{
			free_ptr(value_of_path);
			free(dir);
			return (prog);
		}
		free(dir);
		free(prog);
	}
	free_ptr(value_of_path);
	return (NULL);
}
