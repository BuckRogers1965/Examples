#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "stack.h"

Que *
QCreate ()
{
  //printf("Create Q\n");
  Que *Head = malloc (sizeof (myQue));
  Head->x = 0;
  Head->depth = 0;
  Head->next = NULL;
  return Head;
}

void
Push (Que * queue, long double value)
{
  // printf("Push $Lf\n", value);
  Que *newQ = malloc (sizeof (myQue));
  newQ->next = queue->next;
  newQ->x = value;
  queue->next = newQ;
  queue->depth++;

}

long double
Pop (Que * queue)
{

  long double result = 0;

  if (queue->depth)
    {
      result = queue->next->x;
      queue->depth--;
      Que *temp = queue->next;
      queue->next = queue->next->next;
      free (temp);
    }

  //printf("Pop $Lf\n", result);
  return result;
}

int
QDepth (Que * queue)
{

  return (queue->depth);
}

