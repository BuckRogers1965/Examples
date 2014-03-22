#include <stdio.h>
#include <stdlib.h>
#include "RungeKutta.h"

long double
f1 (long double t, long double y)
{
  return y - t * t + 1;
}

long double
f2 (long double t, long double y)
{
  return 1 + (t-y) * (t-y) ;
}

long double
f2a (long double t)
{
  return (t+1) / (1 - t) ;
}

void
abm ( long double alpha, long double start, long double end,
                long double step, rkf f, char *title)
{

      printf("\n%s\n\n", title);

      rk *r = rk_New (alpha, start, end, step, f);
      rk_Print (r);
      printf ("\n");

      long double  *w;
      w = calloc (sizeof (long double), rk_GetMax(r) + 10);
      if (w == NULL)
        return;
      w[0] = alpha;
      
      int i;
      for (i=1; i<4; i++) {
        w[i]= rk_GetW(r, i);
        printf("%0.4Lf   %0.10Lf\n", rk_GetT(r, i), w[i]);
      }

      long double h = rk_GetH(r);
      long double t = rk_GetStart(r);
      rk_Dispose (r);

      for (i=4; i<=10; i++) {
        w[i] = w[i-1] + h/24 * (
            55 * f(t + h*(i-1), w[i-1])
           -59 * f(t + h*(i-2), w[i-2])
           +37 * f(t + h*(i-3), w[i-3])
           - 9 * f(t + h*(i-4), w[i-4]) ); 
        printf("%0.4Lf   %0.10Lf\t", t + h*i, w[i]);
        w[i] = w[i-1] + h/24 * (
             9 * f(t + h*(i  ), w[i  ])
           +19 * f(t + h*(i-1), w[i-1])
           - 5 * f(t + h*(i-2), w[i-2])
           +     f(t + h*(i-3), w[i-3]) ); 
        printf("%0.10Lf\n", w[i]);
      }
      printf ("\n");

      free(w);
}


int
main () {

  abm (0.5, 0, 2, 5, &f1, "example from handout");
  abm (1.0, 2, 4, 5, &f2, "Problem 1b from handout");

  printf("actual - doesn't look right - y(2) is supposed to be 1\n\n");
  long double i;
  for (i=2; i<=4.1; i += 0.2)
	printf("%Lf   %Lf\n", i, f2a(i));

  exit(0);
}

