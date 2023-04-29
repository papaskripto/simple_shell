#include "shell.h"

/**
 * add_node_at_end - adds a new node at the end of a linked list
 * @head: double pointer to the env_t list
 * @str: string to put in the new node
 * Return:address of new element
 */

env_t *add_node_at_end(env_t **head, char *str)
{
	env_t *new = NULL;
	env_t *temp = *head;

	new = malloc(sizeof(env_t));
	if (!new)
		return (NULL);

	new->str = my_strdup(str);
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	while (temp->next)
		temp = temp->next;

	temp->next = new;

	return (new);
}

/**
 * delete_index_node - deletes a node in a linked list at a certain index
 * @head: pointer to the first element in the list
 * @index: index of the node to delete
 * Return:1
 */
int delete_index_node(env_t **head, unsigned int index)
{
	env_t *temp = *head;
	env_t *current = NULL;
	unsigned int i = 0;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	while (i < index - 1)
	{
		if (!temp || !(temp->next))
			return (-1);
		temp = temp->next;
		i++;
	}

	current = temp->next;
	temp->next = current->next;
	free(current->str);
	free(current);

	return (1);
}
/**
 * node_at_index - adds a new node in a linked list at a given index
 * @head: double pointer to the en_t list
 * @str: string to put in the new node
 * @idx: index where to insert the node
 * Return:0
 */

int node_at_index(env_t **head, char *str, int idx)
{
	int i;
	env_t *new = NULL;
	env_t *temp = *head;

	new = malloc(sizeof(env_t));
	if (!new || !head)
		return (-1);

	new->str = my_strdup(str);
	new->next = NULL;

	if (idx == 0)
	{
		new->next = *head;
		*head = new;
		return (0);
	}

	for (i = 0; temp && i < idx; i++)
	{
		if (i == idx - 1)
		{
			new->next = temp->next;
			temp->next = new;
			return (0);
		}
		else
			temp = temp->next;
	}

	return (-1);
}

/**
 * index_list_fnd - finds the index of a given element in a list
 * @head: pointer to the env_t list
 * @name: string of the node to find
 * Return:index of node
 */
int index_list_fnd(env_t *head, char *name)
{
	int index = 0;
	int c = 0;

	while (head)
	{
		c = my_strncmp(head->str, name, my_strlen(name));
		if (c == 0)
			return (index);
		index++;
		head = head->next;
	}

	return (0);
}
