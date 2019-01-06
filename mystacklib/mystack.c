#include "mystack.h"
#include "logging.h"
#include <stdlib.h>
#include <string.h>
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
int handle = 1;

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
		newstack->handle = handle;
		newstack->objsize = objsize;
		gStackList = newstack;
	}
	else
	{
		newstack->handle = handle;
		newstack->objsize = objsize;
		newstack->next = gStackList;
		gStackList = newstack;
		handle++;
	}
	DBG_PRINTF("Created stack with handle: %d and objsize %zu bytes\n", gStackList->handle, objsize);
	return gStackList->handle;
}

int mystack_push(int handle, void* obj)
{
	if(handle <= 0 || gStackList == NULL || obj == NULL)
	{
		return -1;
	}
	pStackMeta_t tempstack = gStackList;



	while (tempstack->handle != handle)
	{
		tempstack = tempstack->next;
	}

	pStackObject_t newObject = (pStackObject_t)malloc(sizeof(StackObject_t));
	newObject->obj = malloc(sizeof(tempstack->objsize));
	newObject->next = tempstack->stack;  //malloc sizeof van obj
	memcpy(newObject->obj, obj, tempstack->objsize);

	//put the current head in the stack in a temp variable, then put the new object as the head of the stack, and put the temp variable as the stack->next
	tempstack->stack = newObject;
 	tempstack->numelem++;
	//newobject->obj = malloc(tempstack->objsize)
	//tempstack->stack = tempobj;


	//DBG_PRINTF("handle: %d\n, obj: %p\n", handle, obj);
	return 0;
}

int mystack_pop(int handle, void* obj)
{
	pStackMeta_t current = gStackList;

	while (current != NULL)
	{
		if (current->handle == handle)
		{
			pStackObject_t currentObj = current->stack;
			pStackObject_t prevObj = NULL;

			if (currentObj == NULL)
			{
				return -1;
			}
			else
			{
				while (currentObj->next != NULL)
				{
					prevObj = currentObj;
					currentObj = currentObj->next;
				}

				memcpy(obj, currentObj->obj, current->objsize);

				if (prevObj != NULL)
				{
					prevObj->next = NULL;
				}
				else
				{
					current->stack = NULL;
				}

				free(currentObj->obj);
				free(currentObj);
			}

			current->numelem -= 1;
			return 0;
		}

		current = current->next;
	}

    DBG_PRINTF("handle: %d\n, obj: %p\n", handle, obj);
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
			pStackObject_t currentobject = temp->stack;
			pStackObject_t next;

			//clearing the stackobject objects
			while (currentobject != NULL)
			{
				next = currentobject->next;
				free(currentobject->next);
				free(currentobject);
				currentobject = next;
			}
			//destroy the stackmeta object
			free(temp);
			return 0;
		}
		temp = temp->next;
	}

	return -2;
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
