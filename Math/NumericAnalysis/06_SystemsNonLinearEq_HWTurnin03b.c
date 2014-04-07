#include <stdio.h>
#include <math.h>
#include "06_SystemsNonLinearEq.h"

/* James M. Rogers
   03 April 2014

  compile with
    gcc matrix.c 06_SystemsNonLinearEq.c 06_SystemsNonLinearEq_HW.c -lm
*/

#define E 2.71828182845904523536

long double F1 (long double x[]) {
  return sinl(4.0 * M_PI *  x[0] * x[1]) - 2.0 *x[1] - x[0];
}

long double F2 (long double x[]) {
  return  ((4.0 * M_PI - 1.0) / (4.0 * M_PI)) * (powl(E, 2.0 * x[0]) - E)
            + 4.0 * E * x[1] * x[1] 
            - 2.0 * E * x[0];
}

long double F1X1 (long double x[]) {
  return 4.0 * M_PI * x[1] * cosl(4.0 * M_PI * x[0] * x[1])  - 1;
}

long double F1X2 (long double x[]) {
  return 4.0 * M_PI * x[0] * cosl(4.0 * M_PI * x[0] * x[1])  - 2;
}

long double F2X1 (long double x[]) {
  return  ((4.0 * M_PI - 1.0) / (4.0 * M_PI)) *  2.0 * powl(E, 2.0 * x[0])
            - 2.0 * E ;
}

long double F2X2 (long double x[]) {
  return + 8.0 * E * x[1];
}

int
main ()
{
  long double x;
  SystemNL s = System_New(2, "Section 10.2 Problem 3b");

  System_AddFunc(s, 1, 0, F1);
  System_AddFunc(s, 2, 0, F2);

  System_AddJacobian(s, 1, 1, F1X1);
  System_AddJacobian(s, 1, 2, F1X2);
  System_AddJacobian(s, 2, 1, F2X1);
  System_AddJacobian(s, 2, 2, F2X2);

  System_Solve(s);

  System_Dispose(s);
  return 0;
}
