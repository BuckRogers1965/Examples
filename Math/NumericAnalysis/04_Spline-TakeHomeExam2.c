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
F (long double x, long double xj, int pow)
{
  long double result = 1;
  int i;
  //printf("x %Lf xj %Lf pow %d  ", x, xj, pow);
  for (i = 0; i < pow; i++)
    {
      result *= x - xj;
      //printf("*");
    }
  //printf("\n");
  return result;
}

long double
SolveSplineDerive (int n, Point P[], long double x)
{
  // find the interval x is in
  if (!(P[n - 1].x > x && P[0].x < x))
    return NAN;
  int i = 0;
  for (i = 1; i < n; i++)
    if (x < P[i].x)
      break;
  //printf("Found interval %d\n", i);
  i--;

  return P[i].b + 2 * P[i].c * F (x, P[i].x, 1)
                + 3 * P[i].d * F (x, P[i].x, 2);
}

long double
SolveSpline (int n, Point P[], long double x)
{
  // find the interval x is in
  if (!(P[n - 1].x > x && P[0].x < x))
    return NAN;
  int i = 0;
  for (i = 1; i < n; i++)
    if (x < P[i].x)
      break;
  //printf("Found interval %d\n", i);
  i--;

  return P[i].a + P[i].b * F (x, P[i].x, 1)
                + P[i].c * F (x, P[i].x, 2)
                + P[i].d * F (x, P[i].x, 3);
}

bool
FindSpline (int n, Point P[])
{
  int i, j;

  printf ("h:          ");
  //calculate h for n-1 intervals
  for (i = 0; i < (n - 1); i++)
    {
      P[i].h = P[i + 1].x - P[i].x;
      printf ("%4.4Lf  ", P[i].h);
    }
  printf ("\n");
  printf ("x,a:");
  PrintPoints (n, P);

  // define the size of the matrix and create it.
  // size is n+1 points, and is square

  matrix *A = NewMatrix (n, n);
  if (A == NULL)
    return false;

  Mat_SetCell (A, 1, 1, 1);
  Mat_SetCell (A, n, n, 1);
  for (i = 2; i < n; i++)
    {
      Mat_SetCell (A, i, i - 1, P[i - 2].h);
      Mat_SetCell (A, i, i, 2 * (P[i - 2].h + P[i - 1].h));
      Mat_SetCell (A, i, i + 1, P[i - 1].h);
    }

  printf ("A = ");
  Mat_Print (A);

  matrix *b = NewMatrix (n, 1);
  if (b == NULL)
    goto fail1;

  for (i = 2; i < n; i++)
    {
      Mat_SetCell (b, i, 1,
		 (3 / P[i - 1].h) * (P[i].a - P[i - 1].a) -
		 (3 / P[i - 2].h) * (P[i - 1].a - P[i - 2].a));
    }

  printf ("b_vector = ");
  Mat_Print (b);

  matrix *Ai = Mat_FindInverse (A);
  if (Ai == NULL)
    goto fail2;

  printf ("A^-1 = ");
  Mat_Print (Ai);

  matrix *c = Mat_Mult (Ai, b);
  if (c == NULL)
    goto fail3;

  printf ("A^-1 * b_vector = c = ");
  Mat_Print (c);
  // copy to the Points collection
  for (i = 0; i < n - 1; i++)
    {
      P[i].c = Mat_GetCell (c, i + 1, 1);
    }

  printf ("Determinate of A    is : %Lf \n\n", Mat_Determinate(A));
  printf ("Determinate of A^-1 is : %0.30Lf \n\n", Mat_Determinate(Ai));

  Mat_Dispose (c);
  Mat_Dispose (Ai);
  Mat_Dispose (b);
  Mat_Dispose (A);

  printf ("b = ");
  for (j = 0; j < n - 1; j++)
    {
      P[j].b =
	1 / P[j].h * (P[j + 1].a - P[j].a) - P[j].h / 3 * (2 * P[j].c +
							   P[j + 1].c);
      printf ("%4.4Lf  ", P[j].b);
    }
  printf ("\n");

  printf ("d = ");
  for (j = 0; j < n - 1; j++)
    {
      P[j].d = (1 / (3 * P[j].h)) * (P[j + 1].c - P[j].c);
      printf ("%4.4Lf  ", P[j].d);
    }
  printf ("\n");

  return true;

fail3:
  Mat_Dispose (Ai);
fail2:
  Mat_Dispose (b);
fail1:
  Mat_Dispose (A);
  return false;
}

int
main ()
{
  int n = 21;
  Point P[100];
  long double x;

  // Define the x and y points
  // y points are called a for this interpolation

  P[ 0].x =  0.9;
  P[ 1].x =  1.3;
  P[ 2].x =  1.9;
  P[ 3].x =  2.1;
  P[ 4].x =  2.6;
  P[ 5].x =  3.0;
  P[ 6].x =  3.9;
  P[ 7].x =  4.4;
  P[ 8].x =  4.7;
  P[ 9].x =  5.0;
  P[10].x =  6.0;
  P[11].x =  7.0;
  P[12].x =  8.0;
  P[13].x =  9.2;
  P[14].x = 10.5;
  P[15].x = 11.3;
  P[16].x = 11.6;
  P[17].x = 12.0;
  P[18].x = 12.6;
  P[19].x = 13.0;
  P[20].x = 13.3;

  P[ 0].a = 1.3;
  P[ 1].a = 1.5;
  P[ 2].a = 1.85;
  P[ 3].a = 2.1;
  P[ 4].a = 2.6;
  P[ 5].a = 2.7;
  P[ 6].a = 2.4;
  P[ 7].a = 2.15;
  P[ 8].a = 2.05;
  P[ 9].a = 2.1;
  P[10].a = 2.25;
  P[11].a = 2.3;
  P[12].a = 2.25;
  P[13].a = 1.95;
  P[14].a = 1.4;
  P[15].a = 0.9;
  P[16].a = 0.7;
  P[17].a = 0.6;
  P[18].a = 0.5;
  P[19].a = 0.4;
  P[20].a = 0.25;

  FindSpline (n, P);


  // now that the solution values are stored in P you can call SolveSpline()
  printf ("\n\nSolution test\n\n");
  for (x = 0.5; x < 14; x++)
    {
      printf ("Solution for x: %Lf with %d points: %Lf \n", x, n,
	      SolveSpline (n, P, x));
      printf ("First derivative at x: %Lf \n\n", SolveSplineDerive (n, P, x));
    }

/*
  printf ("\n\nGraph\n\n");
  for (x = .5; x <= 14.1; x +=.1)
    {
      printf ("%Lf %Lf %Lf\n", x, SolveSpline (n, P, x), SolveSplineDerive (n, P, x));
    }
*/

  return 0;
}
