#include "shell.h"

/**
 * my_strcmp - function to compare strings
 * @str1: string to compare
 * @str2: string to compare
 * return: 0
 */


int my_strcmp(const char *str1, const char *str2)
{
	int i = 0;

	/* Iterate through both strings until the end of one is reached*/
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		/* If the characters differ, return the difference*/
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];

 			i++;
		}

	/* If both strings are equal, return 0*/
	return 0;
}

/**
 * print_enviroment - implements the env built in function
 * @argmnts: array of strings containing the command arguments
 */

void print_enviroment(char *arguments[64])
{
	/*Check if the command is "env"*/
	if (my_strcmp(arguments[0], "env") == 0)
	{
		/* Loop through the environment variables*/
		char* env_var = *environ;
		while (env_var != NULL)
		{
		/* Print each environment variable*/
		printf("%s\n", env_var);

		/* Move to the next environment variable*/
		env_var = *(environ++);
	}

	/* Exit the function*/
	exit(0);
	}
}

