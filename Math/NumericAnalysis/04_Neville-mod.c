#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
	James M. Rogers
	For this we have the concept of a list of points.
*/

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

  while (n < count)
    {
      printf ("%d  %Lf  %Lf\n", n, Points[n].x, Points[n].y);
      n++;
    }

}

long double
NevilleRecurse (int n, int depth, Point Points[], Point P[], long double x)
{
  int max = n-1;
  Point NewP[max];

  if (n < 2) {
	return Points[0].y;
  } else {
    int i = 0;
    for (; i < max; i++) {
      //printf ("\nd %d i %d x0  %Lf  x1  %Lf  P0  %Lf  P1  %Lf ", depth, i, P[i  ].x, P[i+1+depth].x, Points[i  ].y, Points[i+1].y);
      NewP[i].y = ((x - P[i+depth].x) * (Points[i  ].y)
                  - (x - P[i        ].x) * (Points[i+1].y))
                  / (P[i].x - P[i+depth].x);
      //printf("%Lf\t", NewP[i].y);
    }
  }
  //printf("\n");
  return NevilleRecurse (max, depth+1, NewP, P, x);
}

long double
FindSolution (int n, Point Points[], long double x){
  return NevilleRecurse (n, 1, Points, Points, 3);
}

void
main ()
{

  long double i;
  int n = 0;
  Point Points[200001];

  Points[0].x = 2;
  Points[0].y = 0.5;

  Points[1].x = 2.5;
  Points[1].y = 0.4;

  Points[2].x = 4;
  Points[2].y = 0.25;

  Points[3].x = 5;
  Points[3].y = 0.2;


  if (n == 0)
    for (n = 0, i = 2; i < 4; i = i + .03001, n++)
      {
	Points[n].x = i;
	Points[n].y = 1/i ;
      }

  long double y = FindSolution (n, Points, 3);
  printf ("\nResult for 1/3 with %d points is %30.20Lf\n", n, y);
}
