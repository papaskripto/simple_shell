#include "shell.h"

/**
* my_strdup - duplicates a string and allocates memory
* @str: string to duplicate
*
* Return: new string on success, NULL on failure
*/

char *my_strdup(char *str)
{
	char *dup = NULL;
	int c, i = 0;

	if (!str)
		return (NULL);

	while (str[i])
		i++;

	dup = malloc(sizeof(char) * i + 1);

	if (!dup)
		return (NULL);

	for (c = 0; c < i; c++)
		dup[c] = str[c];

	dup[c] = '\0';

	return (dup);
}

/**
 * mystr_concat - concatenates two strings,
 * @s1: string1 to concatenate
 * @s2: string2 to concatenate
 *
 * Return: ptr to the str created on success, or NULL on failure
 */
char *mystr_concat(char *s1, char *s2)
{
	char *s3 = NULL;
	unsigned int i = 0, j = 0, len1 = 0, len2 = 0;

	len1 = my_strlen(s1);
	len2 = my_strlen(s2);

	s3 = malloc(sizeof(char) * (len1 + len2 + 1));
	if (s3 == NULL)
		return (NULL);

	i = 0;
	j = 0;

	if (s1)
	{
		while (i < len1)
		{
			s3[i] = s1[i];
			i++;
		}
	}

	if (s2)
	{
		while (i < (len1 + len2))
		{
			s3[i] = s2[j];
			i++;
			j++;
		}
	}
	s3[i] = '\0';

	return (s3);
}

/**
 * my_strcmp - compares two strings
 * @s1: string2 to compare
 * @s2: string2 to compare
 *
 * Return: less than 0 if s1 < than s2, 0 if s1 == s2equal,
 * more than 0 if s1 is greater than s2
 */
int my_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
* my_strncmp - compare strings up to n bytes
* @s1: string1 to compare against
* @s2: string2 to compare from
* @n: num of bytes to compare
*
* Return: 0 if the strings are different, non-zero if they are the same
*/
int my_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i = 0;

	while (*s1 == *s2 && i < n)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
		i++;
	}
	return (i != n);
}
