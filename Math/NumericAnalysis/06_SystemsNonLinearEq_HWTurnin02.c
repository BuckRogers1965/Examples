#include <stdio.h>
#include <math.h>
#include "06_SystemsNonLinearEq.h"

/* James M. Rogers
   03 April 2014

  compile with
    gcc matrix.c 06_SystemsNonLinearEq.c 06_SystemsNonLinearEq_HWTurnin02.c -lm
*/

#define E 2.71828182845904523536

long double F1 (long double x[]) {
  return 4.0 * x[0] * x[0]
            - 20.0 * x[0]
            + 1.0/4.0 * x[1] * x[1]
            + 8.0;
}

long double F2 (long double x[]) {
  return 0.5 * x[0] * x[1] * x[1]
            + 2.0 * x[0]
            - 5.0 * x[1] 
            + 8.0 ;
}

long double F1X1 (long double x[]) {
  return  4.0 * 2 * x[0] - 20.0 ;
}

long double F1X2 (long double x[]) {
  return 1.0/2.0 * x[1];
}


long double F2X1 (long double x[]) {
  return  0.5 * x[1] * x[1] + 2.0;
}

long double F2X2 (long double x[]) {
  return x[0] * x[1] - 5.0 ;
}


int
main ()
{
  long double x;
  SystemNL s = System_New(2, "Homework 10.4 1a");

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
