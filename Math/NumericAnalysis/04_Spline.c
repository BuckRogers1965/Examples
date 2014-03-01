#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* James M. Rogers
   01 March 2014
*/

typedef struct Point Point;
struct Point
{
  long double x;
  long double a;
  long double h;
  long double b;
  long double c;
  long double d;
} myPoint;

void
PrintPoints (int count, Point Points[])
{
  int n = 0;

  printf ("\t");
  for (n = 0; n < count; n++)
    printf ("%4.4Lf\t", Points[n].x);
  printf ("\n");

  printf ("\t");
  for (n = 0; n < count; n++)
    printf ("%4.4Lf\t", Points[n].a);
  printf ("\n");

}

long double
F(long double x, long double xj, int pow){
  long double result=1;
  int i;
  //printf("x %Lf xj %Lf pow %d  ", x, xj, pow);
  for (i=0; i< pow; i++) {
    result *= x - xj;
    //printf("*");
  }
  //printf("\n");
  return result;
}


long double
SolveSplineDerive (int n, Point P[], long double x)
{
  long double result;

  // find the interval x is in
  if (!(P[n-1].x>x && P[0].x<x)) return NAN;
  int i=0;
  for(i=1; i<n; i++)
   if (x < P[i].x) break;
  //printf("Found interval %d\n", i);
  i--;

  // calculate sum
  result =  P[i].b + 2 * P[i].c * F(x, P[i].x, 1) + 3 * P[i].d * F(x, P[i].x, 2);
  return result;
}

long double
SolveSpline (int n, Point P[], long double x)
{
  long double result;

  // find the interval x is in
  if (!(P[n-1].x>x && P[0].x<x)) return NAN;
  int i=0;
  for(i=1; i<n; i++)
   if (x < P[i].x) break;
  //printf("Found interval %d\n", i);
  i--;

  // calculate sum
  result = P[i].a + P[i].b*F(x, P[i].x, 1) + P[i].c*F(x, P[i].x, 2) + P[i].d*F(x, P[i].x, 3);
  return result;
}

bool
FindSpline (int n, Point P[])
{
  int i, j;

  printf("h:          ");
  //calculate h for n-1 intervals
  for (i=0;i<(n-1);i++) {
    P[i].h = P[i+1].x - P[i].x;
    printf("%4.4Lf  ", P[i].h);
  }
  printf("\n");
  printf("x,a:");
  PrintPoints(n, P);

  // define the size of the matrix and create it.
  // size is n+1 points, and is square

  matrix * A = NewMatrix (n, n);
  if (A == NULL) return false;

  SetMatrix(A,   1,   1, 1);
  SetMatrix(A, n, n, 1);
  for (i=2;i<n;i++) {
    SetMatrix(A, i, i-1, P[i-2].h);
    SetMatrix(A, i,   i, 2 * (P[i-2].h + P[i-1].h));
    SetMatrix(A, i, i+1, P[i-1].h);
  }

  printf("A = ");
  PrintMatrix(A);
   
  matrix * b = NewMatrix (n, 1);
  if (b == NULL) goto fail1;

  for (i=2;i<n;i++) {
    SetMatrix(b, i, 1, (3/P[i-1].h) * (P[i].a - P[i-1].a) - (3/P[i-2].h) * (P[i-1].a - P[i-2].a));
  }

  printf("b_vector = ");
  PrintMatrix(b);

  matrix *Ai = FindInverse (A);
  if (Ai == NULL) goto fail2;

  printf("A^-1 = ");
  PrintMatrix (Ai);

  matrix * c = MultMatrix(Ai, b);
  if (c == NULL) goto fail3;

  printf("A^-1 * b_vector = c = ");
  PrintMatrix (c);
  // copy to the Points collection
  for (i=0;i<n-1;i++) { 
    P[i].c= GetMatrix(c, i+1, 1);
  }

  DisposeMatrix(c);
  DisposeMatrix(Ai);
  DisposeMatrix(b);
  DisposeMatrix(A);

  printf("b = ");
  for (j=0;j<n-1;j++) {
    P[j].b = 1/P[j].h * (P[j+1].a - P[j].a) - P[j].h/3 * (2* P[j].c + P[j+1].c);
    printf("%4.4Lf  ", P[j].b);
  }
  printf("\n");

  printf("d = ");
  for (j=0;j<n-1;j++) {
    P[j].d = (1 / (3 * P[j].h)) *  (P[j+1].c - P[j].c);
    printf("%4.4Lf  ", P[j].d);
  }
  printf("\n");

  return true;

  fail3:
  DisposeMatrix(Ai);
  fail2:
  DisposeMatrix(b);
  fail1:
  DisposeMatrix(A);
  return false;
}

void
main ()
{

  int n = 6;
  Point P[100];
  int i, j;
  long double x;

  // Define the x and y points
  // y points are called a for this interpolation

  P[0].x =  1.0;
  P[1].x =  3.0;
  P[2].x =  5.0;
  P[3].x =  7.0;
  P[4].x =  8.0;
  P[5].x = 10.0;

  P[0].a =  6.0;
  P[1].a =  2.0;
  P[2].a =  5.0;
  P[3].a = 10.0;
  P[4].a =  4.0;
  P[5].a =  1.0;

  FindSpline (n, P);

  // now that the solution values are stored in P you can call SolveSpline()
  printf("\n\nSolution test\n\n");

  for (x=0.5;x< 11; x++){
    printf("Solution for x: %Lf with %d points: %Lf \n", x, n, SolveSpline(n, P, x));
    printf("First derivative at x: %Lf \n\n", SolveSplineDerive(n, P, x));
  }
}
