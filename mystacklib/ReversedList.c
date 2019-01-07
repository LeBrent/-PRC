#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mystack.h"

#define LIST_SIZE 1500

typedef struct Node* plistnode_t;
typedef struct Node
{
  int data;
  plistnode_t next;
} listnode_t;


void print_list( plistnode_t node)
{
    while (node != NULL)
    {
       printf(" %d ", node->data);
       node = node->next;
    }

   printf("\n");
}

int main()
{
  int handle = mystack_create(sizeof(listnode_t));
  plistnode_t head = malloc(sizeof(listnode_t));
  plistnode_t temp = head;

  for (size_t i = 0; i < LIST_SIZE; i++) {
    mystack_push(handle, &temp->data);

    temp = temp->next;
    // free(temp);
  }
  printf("original list:\n");

  print_list(head);

  temp = head;
  for (int i = 0; i < LIST_SIZE; i++) {
    mystack_pop(handle, &temp->data);
    temp = temp->next;
  }
  printf("\nswitching it!\n\n");

  print_list(head);
}
