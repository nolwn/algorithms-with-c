#include <stdlib.h>
#include "linked-list.h"

void list_init(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
}

void list_destroy(List *list)
{
	ListElmt *elmt;
	ListElmt *next;

	next = list->head;
	list->head = NULL;
	for (int i = 0; i < list_size(list); i++)
	{
		elmt = next;
		next = elmt->next;

		list->destroy(elmt);
	}
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt *curr = list->head;
	ListElmt *next = malloc(sizeof(ListElmt));

	while (curr != element && curr != NULL)
	{
		curr = curr->next;
	}

	if (curr != element)
	{
		free(next);
		return -1;
	}

	if (curr == NULL)
	{
		next->next = list->head;
		list->head = next;
	}
	else
	{
		next->next = curr->next;
		curr->next = next;
	}

	if (next->next == NULL)
		list->tail = next;

	next->data = data;
	list->size++;

	return 0;
}
