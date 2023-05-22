#ifndef __STACK_HEADER
#define __STACK_HEADER

#include "linked_list.h"
#include <stdbool.h>

/*
 * This class is imported from CSCI 2122 course from
 * Fall 2022, provided by the TA's
 */

typedef struct _Stack
{
	LinkedList* stack;
} Stack;

Stack* stack_initialize(int, char*);
bool   stack_push(Stack*, void*);
void*  stack_pop(Stack*);
void*  stack_peek(Stack*);
int    stack_size(Stack*);
bool   stack_contains(Stack*, void*);
bool   stack_destroy(Stack*);

#endif
