#include "shell.h"

/**
 * token_count - counts tokens in a string for token_strtok
 * @str: string to tokenize
 * @delim: delimeter between tokens
 *
 * Return: num of tokens
 */
int token_count(char *str, char delim)
{
	int num = 0, i;
	int flag = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == delim)
		{
			flag = 0;
		}
		else if (flag == 0)
		{
			flag = 1;
			num++;
		}
	}
	return (num);
}

/**
* token_strtok - converts a string into an array of tokens
* @str: string to tokenize
* @delim: delimeter between tokens
*
* Return: pointer to the array of strings on success, or NULL on failure
*/
char **token_strtok(char *str, char delim)
{
	char *str_copy = NULL, **token_input = NULL;
	int i = 0, j = 0, len = 0, total_tokens = 0;

	if (str == 0 || *str == 0)
		return (NULL);
	total_tokens = token_count(str, delim);
	if (total_tokens == 0)
		return (NULL);
	token_input = malloc(sizeof(char *) * (total_tokens + 1));
	if (token_input == NULL)
		return (NULL);
	while (*str && i < total_tokens)
	{
		if (*str == delim)
			str++;
		else
		{
			str_copy = str;
			while (*str != delim && *str)
			{
				len++;
				str++;
			}
			token_input[i] = malloc(sizeof(char) * (len + 1));
			if (!token_input[i])
				return (NULL);
			while (*str_copy != delim && *str_copy && *str_copy != '\n')
			{
				token_input[i][j] = *str_copy;
				str_copy++;
				j++;
			}
			token_input[i][j] = '\0';
			i++;
			j = 0;
			len = 0;
		}
	}
	token_input[i] = NULL;
	return (token_input);
}
