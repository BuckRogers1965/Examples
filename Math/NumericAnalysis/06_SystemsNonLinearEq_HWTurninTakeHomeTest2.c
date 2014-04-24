#include <stdio.h>
#include <math.h>
#include "06_SystemsNonLinearEq.h"

/* James M. Rogers
   09 April 2014

  compile with
    gcc matrix.c 06_SystemsNonLinearEq.c \
       06_SystemsNonLinearEq_HWTurninTakehomeTest2.c -lm
*/

long double F1 (long double x[]) {
  return x[0] + cosl(x[0]*x[1]*x[2]) - 1.0;
}

long double F2 (long double x[]) {
  return powl(1-x[0],1.0/4.0)+x[1]+0.05*x[2]*x[2]-0.15*x[2]-1.0;
}

long double F3 (long double x[]) {
  return -x[0]*x[0] -0.1*x[1]*x[1] + 0.01*x[1] + x[2] - 1.0;
}

long double F1X1 (long double x[]) {
  return 1 - x[1] * x[2] * sinl(x[0]*x[1]*x[2]) ;
}

long double F1X2 (long double x[]) {
  return - x[0] * x[2] * sinl(x[0]*x[1]*x[2]) ;
}

long double F1X3 (long double x[]) {
  return - x[0] * x[1] * sinl(x[0]*x[1]*x[2]) ;
}

long double F2X1 (long double x[]) {
  return  - (1.0/ 4.0 *(powl (1-x[0], 3.0/4.0)));
}

long double F2X2 (long double x[]) {
  return 1.0;
}

long double F2X3 (long double x[]) {
  return .01 * x[2] -0.15;
}

long double F3X1 (long double x[]) {
  return  -2.0 * x[0];
}

long double F3X2 (long double x[]) {
  return  0.01 - 0.2 * x[1];
}

long double F3X3 (long double x[]) {
  return  1.0;
}

int
main ()
{
  SystemNL s = System_New(3, "TakeHomeTest");

  System_AddFunc(s, 1, 0, F1);
  System_AddFunc(s, 2, 0, F2);
  System_AddFunc(s, 3, 0, F3);

  System_SetSD(s, 5);
  System_SetNI(s, 10);

  System_AddJacobian(s, 1, 1, F1X1);
  System_AddJacobian(s, 1, 2, F1X2);
  System_AddJacobian(s, 1, 3, F1X3);
  System_AddJacobian(s, 2, 1, F2X1);
  System_AddJacobian(s, 2, 2, F2X2);
  System_AddJacobian(s, 2, 3, F2X3);
  System_AddJacobian(s, 3, 1, F3X1);
  System_AddJacobian(s, 3, 2, F3X2);
  System_AddJacobian(s, 3, 3, F3X3);

  System_Solve(s);

  System_Dispose(s);
  return 0;
}
