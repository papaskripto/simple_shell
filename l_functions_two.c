#include "shell.h"

/**
 * arr_2_lst - transforms the environ variable into a linked list
 * @head: double pointer to the env_t list to fill
 * @env: array of strings containing the environment variables
 * Return: num of nodes
 */

int arr_2_lst(env_t **head, char **env)
{
	int i = 0;

	if (head)
		fr_lst(head);

	while (env[i])
	{
		add_node_at_end(head, env[i]);
		i++;
	}
	return (i);
}

/**
 * lst_2_arr - transforms a linked list in an array of strings
 * @head: pointer to the env_t list
 * Return:array address
 */
char **lst_2_arr(env_t *head)
{
	env_t *temp = head;
	char **arr = NULL, *s = NULL;
	size_t size = 0;
	int i;

	size = list_length(head);

	if (!head || !size)
		return (NULL);

	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);

	for (i = 0; temp; temp = temp->next, i++)
	{
		s = malloc(sizeof(char) * (my_strlen(temp->str) + 1));
		if (!s)
		{
			free_ptr(arr);
			return (NULL);
		}
		s = my_strcpy(s, temp->str);
		arr[i] = s;
	}
	arr[i] = NULL;

	return (arr);
}
/**
 * prt_lst - prints all the nodes of a linked list
 * @h: pointer to the list_t list to print
 *
 * Return:  num of nodes printed
 */
size_t prt_lst(env_t *h)
{
	size_t s = 0;

	while (h)
	{
		if (!h->str)
			my_puts("(nil)");
		else
			my_puts(h->str);
		h = h->next;
		s++;
	}

	return (s);
}
/**
 * fr_lst - frees all the nodes of a linked list
 * @head: list_t list to be freed
 * Return:0
 */

void fr_lst(env_t **head)
{
	env_t *temp = NULL;

	if (head == NULL)
		return;

	while (*head)
	{
		temp = (*head)->next;
		free((*head)->str);
		free(*head);
		*head = temp;
	}

	*head = NULL;
}

/**
 * list_length - returns the num of elements in a linked list
 * @h: pointer to the env_t list
 *
 * Return: num of elements in h
 */
size_t list_length(const env_t *h)
{
	size_t n = 0;

	while (h)
	{
		n++;
		h = h->next;
	}
	return (n);
}
