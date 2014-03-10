#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "base_exp.h"

int
main ()
{

  long double x;
  long double max = 0;
  int isave;
  int i;

  for (i = 0; i < MAX; i++)
    {
      x = logl (a[i][0]) * a[i][1];
      if (x > max)
	{
	  max = x;
	  isave = i;
	}
    }

  printf ("Solution is %d\n", isave + 1);

  exit (0);
}
