#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SysEqNOrder.h"

#define E 2.71828182845904523536

long double
f1ex (long double t, long double u1, long double u2)
{
  return u2;
}

long double
f2ex (long double t, long double u1, long double u2)
{
  return powl (E, 2*t) * sinl (t) - 2 * (u1) + 2 * u2;
}

long double
f2pr2a (long double t, long double u1, long double u2)
{
  return t * powl(E, t) - t -  (u1) + 2* u2;
}

long double
f2pr2a_actual (long double t )
{
  return 1.0/6.0 * powl(t, 3) * powl(E, t) - t * powl(E, t) + 2 * powl(E, t) - t - 2;
}

int 
main () {

   syseq * s = syseq_New(-0.4, -0.6, 0.0, 1.0, 10, f1ex, f2ex,
		"Example program from handout");
   syseq_Print(s);
   syseq_Dispose(s);

   s = syseq_New(0, 0, 0.0, 1.0, 10, f1ex, f2pr2a,
		"Problem 2a from handout");
   syseq_Print(s);
   syseq_Dispose(s);

   printf("Actual function\n\n");
   long double i;
   for (i = 0.0; i<=1.001; i += .1)
	printf("%0.4Lf  %0.10Lf\n", i, f2pr2a_actual(i));
   printf("\n");

exit (0);
}
