#include "shell.h"

int arr_2_lst(env_t **head, char **env)
{
	int i = 0;

	if (head)
		fr_lst(head);

	while (env[i])
	{
		add_node_end(head, env[i]);
		i++;
	}
	return (i);
}

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
		s = malloc(sizeof(char) * (_strlen(temp->str) + 1));
		if (!s)
		{
			free_ptr(arr);
			return (NULL);
		}
		s = _strcpy(s, temp->str);
		arr[i] = s;
	}
	arr[i] = NULL;

	return (arr);
}

size_t prt_lst(env_t *h)
{
	size_t s = 0;

	while (h)
	{
		if (!h->str)
			_puts("(nil)");
		else
			_puts(h->str);
		h = h->next;
		s++;
	}

	return (s);
}

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
