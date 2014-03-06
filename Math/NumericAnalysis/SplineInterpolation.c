#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* James M. Rogers
   01 March 2014

   Compline with:
    gcc matrix.c SplineInterpolation.c 04_Spline_ClassExample.c -lm

    where the last .c file has a man function
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
  if (!(P[n - 1].x >= x && P[0].x <= x))
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
  if (!(P[n - 1].x >= x && P[0].x <= x))
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

typedef struct spline spline;
struct spline
{
  int pointCount;
  int maxCount;
  bool Dirty;
  Point *P;

} mySpline;

spline *
Spline_New(int max_point_count){
  spline * s = calloc (sizeof(mySpline), 1);
  if (s == NULL)
    return NULL;
  s->pointCount = 0;
  s->maxCount   = max_point_count;
  s->Dirty      = true;
  s->P = calloc (sizeof(myPoint), s->maxCount);
  return s;
}

bool 
Spline_AddPoint(spline * s, long double x, long double y){
  if (s == NULL)
    return false;
  if (s->pointCount >= s->maxCount)
    return false;
  s->Dirty = true;
  s->P[s->pointCount].x=x;
  s->P[s->pointCount].a=y;
  s->pointCount++;

  return true;
}

long double
Spline_Solve(spline * s, long double x) {
  if (s == NULL)
    return NAN;
  if (s->Dirty == true) {
    FindSpline (s->pointCount, s->P);
    s->Dirty = false;
  }
  return ( SolveSpline (s->pointCount, s->P, x) );
}

long double
Spline_Derive(spline * s, long double x) {
  if (s == NULL)
    return NAN;
  if (s->Dirty == true) {
    FindSpline (s->pointCount, s->P);
    s->Dirty = false;
  }
  return ( SolveSplineDerive (s->pointCount, s->P, x) );
}


int
Spline_PointCount(spline * s){
  if (s == NULL)
    return -1;
  return s->pointCount;
}
