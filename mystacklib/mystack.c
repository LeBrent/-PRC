#include "mystack.h"
#include "logging.h"
#include <stdlib.h>
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

typedef struct stackObject* pStackObject_t;
typedef struct stackObject
{
	void* obj;
	pStackObject_t next;
} StackObject_t;

typedef struct stackMEta* pStackMeta_t;
typedef struct stackMEta
{
	pStackObject_t stack;
	size_t objsize;
	int numelem;
	int handle;
	pStackMeta_t next;
} StackMeta_t;

static pStackMeta_t gStackList = NULL;
pStackMeta_t lastElement = NULL;

 int mystack_create(size_t objsize)
 {
 	/* Hint: use gStackList */

	if (objsize <= 0)
	 {
		return -1;
	}
	pStackMeta_t newstack = malloc(sizeof(StackMeta_t));

	if(gStackList == NULL)
	{
	newstack->handle = 1;
	newstack->objsize = objsize;
	gStackList->next = newstack;
	lastElement = newstack;
  }
	else if (lastElement->next == NULL)
	{
		newstack->handle = lastElement->handle + 1;
		newstack->objsize = objsize;
		lastElement->next = newstack;
		lastElement = newstack;
	}
 	DBG_PRINTF("Created stack with handle: %d and objsize %zu bytes\n", lastElement->handle, objsize);
 	return 0;
 }

 int mystack_push(int handle, void* obj)
 {
	 if(handle <= 0 || gStackList == NULL)
	 {
		 return -1;
	 }
	pStackMeta_t tempstack = gStackList;
	pStackObject_t newObject = obj;

	while (tempstack->handle != handle)
	 {
		tempstack = tempstack->next;
	}
	//Found the stack, lets adjust the objsize
	tempstack->objsize += sizeof(obj);
	//If there is nothing in the stack, easy! put the head direcly on the newobject.
	if (tempstack->stack == NULL)
	{
		tempstack->stack = newObject;
	}
	else
	{
		//put the current head in the stack in a temp variable, then put the new object as the head of the stack, and put the temp variable as the stack->next
		pStackObject_t tempObj = tempstack->stack;
		tempstack->stack = newObject;
		newObject->next = tempObj;
	}

	tempstack->numelem++;
  DBG_PRINTF("handle: %d\n, obj: %p\n", handle, obj);
 	return 0;
 }



 int mystack_pop(int handle, void* obj)
 {
	 if (handle <=0 || gStackList == NULL)
	 {
 		return -2;
	}

 	pStackMeta_t temp = gStackList;

 	while (temp!=NULL) {
 		if (temp->handle == handle) {
 			pStackObject_t toDestroy = temp->stack;
 			temp->stack = temp->stack->next;

 			obj = toDestroy->obj;
 			free(toDestroy);
			temp->numelem--;

 			DBG_PRINTF("handle: %d, obj: %p\n", handle, obj);
 			return 0;
 		}
 		temp = temp->next;
 	}
 	return -1;
 }

 int mystack_destroy(int handle)
 {
    DBG_PRINTF("handle: %d\n", handle);

	if(handle <= 0 || gStackList == NULL)
	{
		return -1;
	}

	pStackMeta_t temp = gStackList;

	while (temp!= NULL)
	{
		if (temp->handle == handle)
			{
				pStackObject_t toDestroy = temp->stack;

				//clearing the stackobject objects
				while (toDestroy != NULL)
				{
					temp->stack = temp->stack->next;
					free(toDestroy);
				}
				//destroy the stackmeta object
				free(temp);
			}
			temp = temp->next;
	}

 	return 0;
 }

 int mystack_nofelem(int handle)
 {

	 if (handle <= 0)
	 {
	 	return -1;
	 }
	 pStackMeta_t temp = gStackList;

	 while (temp!= NULL)
	 {
		 if (temp->handle == handle)
		 {
			 return temp->numelem;
		 }
		 temp = temp->next;
	 }
    DBG_PRINTF("handle: %d\n", handle);
 	return 0;
 }
