#include <stdio.h>
#include <stdlib.h>
#include "RungeKutta.h"

long double
f1 (long double t, long double y)
{
  return y - t * t + 1;
}

int
main ()
{
  int i;
  for (i = 0; i < 1; i++)
    {
      rk *r = rk_New (0.5, 0, 2, 50, &f1);
      rk_Print (r);
      rk_Dispose (r);

      printf("\n");

      r = rk_New (2.640823, 1, 3, 5, &f1);
      rk_Print (r);
      rk_Dispose (r);
    }
}


