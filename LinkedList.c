//LinkedList.c
#include "LinkedList.h"
#include <stdlib.h>
#include <memory.h>

void Create(LinkedList *linkedList)
{
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

Node* InsertBefore(LinkedList *linkedList, Node* index, void* object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	linkedList->current->next = index;
	if (linkedList->head != index)
	{
		linkedList->current->previous = index->previous;
		index->previous->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	index->previous = linkedList->current;

	linkedList->length++;

	return linkedList->current;
}

Node* InsertAfter(LinkedList *linkedList, Node* index, void* object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	linkedList->current->previous = index;
	if (linkedList->tail != index)
	{
		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;

	linkedList->length++;

	return linkedList->current;
}

Node* AppendFromHead(LinkedList *linkedList, void* object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	linkedList->current->previous = linkedList->current;

	if (linkedList->head != NULL)
	{
		linkedList->current->next = linkedList->head;
		linkedList->head->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;

	linkedList->length++;

	return linkedList->current;
}

Node* AppendFromTail(LinkedList *linkedList, void* object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	linkedList->current->next = linkedList->current;

	if (linkedList->tail != NULL)
	{
		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;

	linkedList->length++;

	return linkedList->current;
}

Node* Delete(LinkedList *linkedList, Node* index) {
	if (linkedList->head != index && linkedList->tail != index) {

		index->previous->next = index->next;
		index->next->previous = index->previous;
		linkedList->current = index->next;
	}
	else if (linkedList->head == index && linkedList->tail != index) {

		index->next->previous = index->next;
		linkedList->head = index->next;
		linkedList->current = index->next;
	}
	else if (linkedList->tail == index && linkedList->head != index) {

		index->previous->next = index->previous;
		linkedList->tail = index->previous;
		linkedList->current = index->previous;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	linkedList->length--;
	return index;
}

Node* DeleteFromHead(LinkedList *linkedList) {
	Node *index;
	index = linkedList->head;
	if (linkedList->tail != index) {

		linkedList->head->next->previous = linkedList->head->next;
		linkedList->head = linkedList->head->next;
		linkedList->current = linkedList->head;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	linkedList->length--;
	return index;
}

Node* DeleteFromTail(LinkedList *linkedList) {
	Node *index;
	index = linkedList->tail;

	if (linkedList->head != index) {
		linkedList->tail->previous->next = linkedList->tail->previous;
		linkedList->tail = linkedList->tail->previous;
		linkedList->current = linkedList->tail;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}linkedList->length--;

	return index;
}

Node* LinearSearchUnique(LinkedList *linkedList, void *key, int(*compare)(void*, void*))
{
	Node* index = NULL;
	Node* previous = NULL;

	linkedList->current = linkedList->head;
	while (linkedList->current != previous && compare(linkedList->current + 1, key) != 0)
	{
		previous = linkedList->current;
		linkedList->current = linkedList->current->next;
	}
	if (linkedList->current != previous)
	{
		index = linkedList->current;
	}

	return index;
}

void LinearSearchDuplicate(LinkedList *linkedList, void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*))
{
	Long i = 0;
	Node *previous = NULL;

	*count = 0;

	*indexes = (Node*(*))calloc(linkedList->length, sizeof(Node*)); //Ä¥ÆÇ : (Node(*)*)
	linkedList->current = linkedList->head;
	while (linkedList->current != previous)
	{
		if (compare(linkedList->current + 1, key) == 0)
		{
			(*indexes)[i] = linkedList->current;
			(*count)++;
			i++;
		}
		previous = linkedList->current;
		linkedList->current = linkedList->current->next;
	}
}


Node* Move(LinkedList *linkedList, Node *index) {
	linkedList->current = index;

	return linkedList->current;
}

Node* First(LinkedList *linkedList) {
	linkedList->current = linkedList->head;

	return linkedList->current;
}

Node* Previous(LinkedList *linkedList) {
	linkedList->current = linkedList->current->previous;

	return linkedList->current;
}

Node* Next(LinkedList *linkedList) {
	linkedList->current = linkedList->current->next;

	return linkedList->current;
}

Node* Last(LinkedList *linkedList) {
	linkedList->current = linkedList->tail;

	return linkedList->current;
}

void GetAt(LinkedList *linkedList, Node *index, void *object, size_t size)
{
	memcpy(object, index + 1, size);
}

void Destroy(LinkedList *linkedList)
{
	Node* previous = NULL;

	linkedList->current = linkedList->head;
	while (previous != linkedList->current)
	{
		previous = linkedList->current;
		linkedList->head = linkedList->current->next;
		if (linkedList->current != NULL)
		{
			free(linkedList->current);
		}
		linkedList->current = linkedList->head;
	}
}