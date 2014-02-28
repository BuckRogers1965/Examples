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
FindSolution (int n, Point Points[], long double x)
{

  long double p1;
  long double p2;
  long double p3;

  if (n < 2)
    {
      return Points[0].y;
    }
  else
    {
      p1 = (x - Points[n - 1].x) * (FindSolution (n-1, Points, x));
      p2 = (x - Points[    0].x) * (FindSolution (n-1, Points+1 , x));
      p3 = Points[0].x - Points[n - 1].x;
    }
  return ((p1 - p2) / p3);
}

void
main ()
{

  long double i;
  int n = 0;
  Point Points[2001];

  printf("Homework Set 3 Problem 1  - Neville's method\n");
  
  Points[n].x = 0.0;
  Points[n].y = -2;
  n++;
  
  Points[n].x = 1;
  Points[n].y = -1;
  n++;
  
  Points[n].x = 2;
  Points[n].y = 0;
  n++;
  
  Points[n].x = 3;
  Points[n].y = 1;
  n++;
  
  Points[n].x = 4;
  Points[n].y = 2;
  

/*
  if (n == 0)
    for (n = 0, i = 1; i < 10; i = i + .4, n++)
      {
	Points[n].x = i;
	Points[n].y = i*i ;
      }
*/

  long double y = FindSolution (n, Points, 3);
  printf ("\nResult for 3^2 with %d points is %30.20Lf\n", n, y);
}
