#include <stdio.h>
#include "stack.h"

/* James M. Rogers
	For this we have the concept of a list of points.  */

Que *Q;

typedef struct Point Point;
struct Point
{

  long double x;
  long double y;

} myPoint;

void
PrintPoints (int count, Point Points[])
{

  int n = 0;

  for (n = 0; n < count; n++)
    printf ("%Lf\t", Points[n].x);
  printf ("\n");

  for (n = 0; n < count; n++)
    printf ("%Lf\t", Points[n].y);
  printf ("\n");

}

long double
DivDiffRecurse (int n, int depth, Point Points[], Point P[])
{
  int max = n - 1;
  Point NewP[max];

  if (n < 2)
    {
      return Points[0].y;
    }
  else
    {
      int i = 0;
      for (; i < max; i++)
	{

	      //printf ("\nd %d i %d x0  %Lf  x1  %Lf  P0  %Lf  P1  %Lf ", depth, i, P[i  ].x, P[i+1+depth].x, Points[i  ].y, Points[i+1].y);
	      NewP[i].y =
		(Points[i + 1].y - Points[i].y) / (P[i + depth].x - P[i].x);

	  if (!i)
	    {
	      Push (Q, NewP[i].y);
	    }

	  printf ("%Lf\t", NewP[i].y);
	}
    }
  printf ("\n");
  return DivDiffRecurse (max, depth + 1, NewP, P);
}

long double
FindDivDiff (int n, Point Points[], long double x)
{

  int depth;
  int i;

  long double res;
  long double result = 0;

  Push (Q, Points[0].y);

  printf ("Starting Points:\n\n");
  PrintPoints (n, Points);

  printf ("\nCalculated table :\n\n");
  DivDiffRecurse (n, 1, Points, Points);

  printf ("\nFormula for calculation: \n\n");
  while (depth = QDepth (Q))
    {
      res = Pop (Q);
      printf ("+ %Lf ", res);
      for (i = 0; i < (depth - 1); i++)
	{
	  printf ("(%Lf - %Lf)", x, Points[i].x);
	  res *= (x - Points[i].x);
	}
      printf ("\n");
      result += res;
    }
  return result;
}

void
main ()
{

  Q = QCreate ();
  long double i;
  int n;
  long double x;
  long double y;
  Point Points[1000];


  printf("\nExample 1 from Div Diff\n\n");

  Points[0].x = 1;
  Points[0].y = 0.7651977;

  Points[1].x = 1.3;
  Points[1].y = 0.620086;

  Points[2].x = 1.6;
  Points[2].y = 0.4554022;

  Points[3].x = 1.9;
  Points[3].y = 0.2818186;

  Points[4].x = 2.2;
  Points[4].y = 0.1103623;

  n = 5;
  x = 1.5;
  y = FindDivDiff (n, Points, x);
  printf ("\nSolution for %Lf with %d points is %30.20Lf\n", x, n/2, y);


  printf("\nHomework Problem 1a from Div Diff\n\n");

  Points[0].x = 8.1;
  Points[0].y = 16.94410;

  Points[1].x = 8.3;
  Points[1].y = 17.56492;

  Points[2].x = 8.6;
  Points[2].y = 18.50515;

  Points[3].x = 8.7;
  Points[3].y = 18.82091;

  n=4;
  x=8.4;
  y = FindDivDiff (n, Points, x);
  printf ("\nSolution for %Lf with %d points is %30.20Lf\n", x, n/2, y);


  printf("\nHomework Problem 1b from Div Diff\n\n");

  Points[0].x = 0.6;
  Points[0].y = -0.17694460;

  Points[1].x = 0.7;
  Points[1].y = 0.01375227;

  Points[2].x = 0.8;
  Points[2].y = 0.22363362;

  Points[3].x = 1.0;
  Points[3].y = 0.65809197;

  n=4;
  x=.9;
  y = FindDivDiff (n, Points, x);
  printf ("\nSolution for %Lf with %d points is %30.20Lf\n", x, n/2, y);


  printf("\nHomework Problem d from Div Diff\n\n");

  Points[0].x = 1960;
  Points[0].y = 179323;

  Points[1].x = 1970;
  Points[1].y = 203302;

  Points[2].x = 1980;
  Points[2].y = 226542;

  Points[3].x = 1990;
  Points[3].y = 249633;

  Points[4].x = 2000;
  Points[4].y = 281442;

  Points[5].x = 2010;
  Points[5].y = 307746;

  n=6;
  x=2005;
  y = FindDivDiff (n, Points, x);
  printf ("\nSolution for %Lf with %d points is %30.20Lf\n", x, n/2, y);

}
