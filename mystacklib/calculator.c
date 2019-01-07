#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"
#include <math.h>
#include <ctype.h>

int main()
{
  char exp[20];
  char *e;
  float* n1 = malloc(sizeof(*n1));
  float* n2 = malloc(sizeof(*n2));
  float* n3 = malloc(sizeof(*n3));
  float * result = malloc(sizeof(*result));
  float num;
  printf("Enter the expression :: ");
  e = exp;

  scanf("%s",exp);

  mystack_create(sizeof(float));

  while(*e != '\0')
  {
    if(isdigit(*e))
    {
      num = *e - 48;
      mystack_push(1, &num);
    }
    else
    {
      mystack_pop(1, n1);
      mystack_pop(1, n2);

      switch(*e)
      {
        case '+':
        {
          *n3 = *n1 + *n2;
          break;
        }
        case '-':
        {
          *n3 = *n2 - *n1;
          break;
        }
        case '*':
        {
          *n3 = *n1 * *n2;
          break;
        }
        case '/':
        {
          *n3 = *n2 / *n1;
          break;
        }
        case 'p':
        {
          mystack_push(1, n2);
          *n3 = pow(*n1, 2);
          break;
        }
        case 'r':
        {
          mystack_push(1, n2);
          *n3 =  sqrt(*n1);
          break;
        }
        default:
        printf("Met deze operator werk ik nog niet\n");
        break;
      }

      mystack_push(1, n3);
    }

    e++;
  }

  mystack_pop(1, result);
  printf("\nThe result of expression %s  =  %.3f\n\n",exp, *result);

  free(n1);
  free(n2);
  free(n3);
  free(result);
  mystack_destroy(1);
  return 0;

}
