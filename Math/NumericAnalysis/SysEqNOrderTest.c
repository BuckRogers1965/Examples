#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SysEqNOrder.h"

#define E 2.71828182845904523536

long double
f1ex (long double t, long double *u)
{
  return u[1];
}

long double
f2ex (long double t, long double *u)
{
  return powl (E, 2*t) * sinl (t) - 2 * (u[0]) + 2 * u[1];
}

long double
f2pr2a (long double t, long double *u)
{
  return t * powl(E, t) - t -  (u[0]) + 2* u[1];
}

long double
f2pr2a_actual (long double t )
{
  return 1.0/6.0 * powl(t, 3) * powl(E, t) - t * powl(E, t) + 2 * powl(E, t) - t - 2;
}

long double
f1 (long double t, long double *u)
{
  return u[0] - t * t + 1;
}


int 
main () {

   syseq * s = syseq_New(0.0, 2.0, 5, "Runge Kutta example");
   syseq_AddOrder(s, 0.5, f1);
   syseq_Calculate(s);
   syseq_Print(s);
   syseq_Dispose(s);

   s = syseq_New(0.0, 1.0, 10, "Example program from handout");
   syseq_AddOrder(s, -0.4, f1ex);
   syseq_AddOrder(s, -0.6, f2ex);
   syseq_Calculate(s);
   syseq_Print(s);
   syseq_Dispose(s);

   s = syseq_New(0.0, 1.0, 10, "Problem 2a from handout");
   syseq_AddOrder(s, 0, f1ex);
   syseq_AddOrder(s, 0, f2pr2a);
   syseq_Calculate(s);
   syseq_Print(s);
   syseq_Dispose(s);

   printf("Actual function\n\n");
   long double i;
   for (i = 0.0; i<=1.001; i += .1)
	printf("%0.4Lf  %0.10Lf\n", i, f2pr2a_actual(i));
   printf("\n");

exit (0);
}
