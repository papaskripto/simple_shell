#include "shell.h"

/**
 * atoi_ - converts a string to an integer
 * @s: string to be converted
 * Return:converted strings
 */

long int atoi_(char *s)
{
	int m, len, f, digit;
	long int n;

	m = 0;
	n = 0;
	len = my_strlen(s);
	f = 0;
	digit = 0;

	if (s[m] == '+')
		m++;

	while (m < len && f == 0)
	{
		if (s[m] == '-')
			return (-1);

		if (s[m] >= '0' && s[m] <= '9')
		{
			digit = s[m] - '0';
			n = n * 10 + digit;
			f = 1;
			if (s[m + 1] < '0' || s[m + 1] > '9')
				break;
			f = 0;
		}
		m++;
	}

	if (f == 0)
		return (0);

	if (n > INT_MAX || n < 0)
		return (-1);

	return (n);
}

/**
 * convert_num_str - converts number and base into string
 * @num: input number
 * @base: input base
 * Return: string results
 */
char *convert_num_str(int num, int base)
{
	static char *rep = "0123456789";
	static char buffer[50];
	char *ptr = NULL;

	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);

	return (ptr);
}
