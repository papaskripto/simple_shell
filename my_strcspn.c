#include "shell.h"

/**
 * my_strcspn - Finds the length of the initial segment of a string
 * @s: pointer to nullterminated string
 * @reject:ptr thar contains chars to match
 * Return: The length of the initial segment of str
 *
 */

size_t my_strcspn(const char *s, const char *reject)
{
	const char *p;
	const char *r;
	size_t count = 0;

	for (p = s; *p != '\0'; p++)
	{
		for (r = reject; *r != '\0'; r++)
		{
			if (*p == *r)
			{
				return (count);
			}
		}
	count++;
	}

	return (count);
}
