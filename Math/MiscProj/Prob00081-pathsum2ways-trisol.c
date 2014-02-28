#include <stdio.h>
#include "triangle81.h"
#define LEVELS 159

int series (int n, int b) { return (b * n * n - (b - 2) * n) / 2; }

void
main ()
{
  int i, j;

  for (i = LEVELS - 2; i >= 0; i--)
    {
      int l0 = series (i, 1);
      int l1 = series (i + 1, 1);
      for (j = 0; j <= i; j++)
	{
          //printf ("%d", tri[l0 + j]);
	  if (tri[l1 + j] < tri[l1 + j + 1])
	    tri[l0 + j] += tri[l1 + j];
	  else
	    tri[l0 + j] += tri[l1 + j + 1];
	}
      //printf ("\n");
    }

  printf ("\nSolution is %d\n", tri[0]);
}
