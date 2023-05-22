#include "stack.h"
#include <stdlib.h>

/*
 * This class is imported from CSCI 2122 course from
 * Fall 2022, provided by the TA's
 */

Stack* stack_initialize(int typeSize, char* typeName)
{
	// Create a linked list using its initialize function.
	LinkedList* list = llist_initialize(typeSize, typeName);

	// If the list couldn't be initialized, return NULL.
	if(list == NULL)
		return NULL;

	// Allocate memory for holding a stack.
	Stack* stack = malloc(sizeof(*stack));

	// If we couldn't allocate memory, destroy the
	// list and return NULL.
	if(stack == NULL)
	{
		llist_destroy(list);
		return NULL;
	}
	
	// Set the stack's underlying list as our linked list.
	stack->stack = list;

	// Return a pointer to the stack.
	return stack;	
}

bool stack_push(Stack* stack, void* element)
{
	// If the stack is null, return false.
	// Checking whether the element is null will
	// be handled by the add_first function.
	if(stack == NULL)
		return false;
	
	// Attempt to add the element to the front of
	// the list and return the outcome.
	return llist_add_first(stack->stack, element);
}

void* stack_pop(Stack* stack)
{
	// If the stack is null, we return NULL.
	if(stack == NULL)
		return NULL;
	
	// Attempt to remove the first element of the
	// underlying list and return it.
	return llist_remove_first(stack->stack);
}

void* stack_peek(Stack* stack)
{
	// Return the value at the start of the list.
	return llist_get(stack->stack, 0);
}

int stack_size(Stack* stack)
{
	// If the stack is null, we return -1.
	if(stack == NULL)
		return -1;
	
	// Return the recorded size of the underlying list.
	return stack->stack->size;
}

bool stack_contains(Stack* stack, void* element)
{
	// If the stack is null, we return NULL. The
	// index_of function checks if the element is NULL.
	if(stack == NULL)
		return NULL;
	
	// Retrieve the index of the element in the list.
	int index = llist_index_of(stack->stack, element);

	// If the elmement's index is >= 0, then it must exist
	// in the list, so we return true. Otherwise we return false.
	return (index >= 0 ? true : false);
}

bool stack_destroy(Stack* stack)
{
	// If the stack is null, we return false.
	if(stack == NULL)
		return false;

	// Destroy the underlying linked list.
	llist_destroy(stack->stack);

	// Free the stack.
	free(stack);

	// Return successfully as true.
	return true;
}
