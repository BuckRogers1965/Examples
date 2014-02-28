#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stack.h"

/*
	James M. Rogers
	For this we have the concept of a list of points.
*/

Que *Q;

typedef struct Point Point;
struct Point
{

  long double x;
  long double y;
  long double dif;

} myPoint;

void
PrintPoints (int count, Point Points[])
{

  int n = 0;

  for (n = 0; n < count; n++, n++)
    printf ("%Lf\t", Points[n].x);
  printf ("\n");

  for (n = 0; n < count; n++, n++)
    printf ("%Lf\t", Points[n].y);
  printf ("\n");

}

long double
HermiteRecurse (int n, int depth, Point Points[], Point P[])
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

	  if ((depth == 1) && (Points[i].x == Points[i + 1].x))
	    {
	      NewP[i].y = Points[i].dif;
	      printf ("*");
	    }
	  else
	    {
	      //printf ("\nd %d i %d x0  %Lf  x1  %Lf  P0  %Lf  P1  %Lf ", depth, i, P[i  ].x, P[i+1+depth].x, Points[i  ].y, Points[i+1].y);
	      NewP[i].y =
		(Points[i + 1].y - Points[i].y) / (P[i + depth].x - P[i].x);
	    }

	  if (!i)
	    {
	      Push (Q, NewP[i].y);
	    }

	  printf ("%Lf\t", NewP[i].y);
	}
    }
  printf ("\n");
  return HermiteRecurse (max, depth + 1, NewP, P);
}

long double
FindHermite (int n, Point Points[], long double x)
{

  int depth;
  int i;

  long double res;
  long double result = 0;

  Push (Q, Points[0].y);

  printf ("Starting Points:\n\n");
  PrintPoints (n, Points);

  printf ("\nCalculated table (* for derivative) :\n\n");
  HermiteRecurse (n, 1, Points, Points);

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
  int n = 6;
  long double x;
  long double y;
  Point Points[1000];

  Points[0].x = 1.3;
  Points[0].y = 0.6200860;
  Points[0].dif = -0.5220232;

  Points[1].x = 1.3;
  Points[1].y = 0.6200860;
  Points[1].dif = -0.5220232;


  Points[2].x = 1.6;
  Points[2].y = 0.4554022;
  Points[2].dif = -0.5698959;

  Points[3].x = 1.6;
  Points[3].y = 0.4554022;
  Points[3].dif = -0.5698959;


  Points[4].x = 1.9;
  Points[4].y = 0.2818186;
  Points[4].dif = -0.5811571;

  Points[5].x = 1.9;
  Points[5].y = 0.2818186;
  Points[5].dif = -0.5811571;


/*
  if (n == 0)
    for (n = 0, i = 2; i < 4; i = i + .03001, n++)
      {
	Points[n].x = i;
	Points[n].y = 1/i ;
      }
*/
  x = 1.5;
  y = FindHermite (n, Points, x);
  printf ("\nSolution for %Lf with %d points is %30.20Lf\n", x, n/2, y);

  Points[0].x   = 0;
  Points[0].y   = 0;
  Points[0].dif = 75;

  Points[1].x   = 0;
  Points[1].y   = 0;
  Points[1].dif = 75;


  Points[2].x   = 3;
  Points[2].y   = 225;
  Points[2].dif = 77;

  Points[3].x   = 3;
  Points[3].y   = 225;
  Points[3].dif = 77;


  Points[4].x   = 5;
  Points[4].y   = 383;
  Points[4].dif = 80;

  Points[5].x   = 5;
  Points[5].y   = 383;
  Points[5].dif = 80;


  Points[6].x   = 8;
  Points[6].y   = 623;
  Points[6].dif = 74;

  Points[7].x   = 8;
  Points[7].y   = 623;
  Points[7].dif = 74;


  Points[8].x   = 13;
  Points[8].y   = 993;
  Points[8].dif = 72;

  Points[9].x   = 13;
  Points[9].y   = 993;
  Points[9].dif = 72;

  n = 10;
  //  55mph is 80.6667 feet per second

  long double prev = 0;
  //long double step = .0001;
  long double step = 1;
  printf ("\nSolution\ttime\tdistance\tdist per unit\tspeed\n");
  //for (i=0; i< (13+step); i = i + step) {
  for (i=10; i< (10+step); i = i + step) {
    y = FindHermite (n, Points, i);
    printf ("\nSolution\t%Lf\t%30.20Lf\t%Lf\t%Lf\n", i, y, (y-prev), (y-prev)*(1/step)*3600/5280);
    prev = y;
  }

}
