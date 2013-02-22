#include "stdio.h"

int
main ()
{
  int i;
  for (i = 1; i< 101; i++)
    {
      if (i % 3 == 0)
	printf ("Fizz");
      if (i % 5 == 0)
	printf ("Buzz");
      if (i % 3 && i % 5)
	printf ("%d", i);
      printf ("\n");
    }
  return (0);
}
