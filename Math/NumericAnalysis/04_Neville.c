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

      int mid = (n + 1) / 2;

      // this corrects for when n =2 so that the above section
      // will return the proper value
      int of1 = 0;
      if (mid == 1)
	of1 = 1;

      // this corrects for when n/2 is has no remainder
      // so that we span the middle value
      int of2 = 0;
      if (((2 * mid) != n) && (n > 3))
	of2 = 1;

      p1 = (x - Points[n - 1].x) * (FindSolution (mid + of2, Points, x));
      p2 =
	(x -
	 Points[0].x) * (FindSolution (mid + of2,
				       Points + (mid - (1 + of2)) + of1, x));
      p3 = Points[0].x - Points[n - 1].x;
    }
  return ((p1 - p2) / p3);
}

void
main ()
{

  long double i;
  int n = 0;
  Point Points[200001];

  if (n == 0)
    for (n = 0, i = 1; i < 10; i = i + 0.0100001, n++)
      {
	Points[n].x = i;
	Points[n].y = i * i;
      }

  long double y = FindSolution (n, Points, 3);
  printf ("\nResult for 3^2 with %d points is %30.20Lf\n", n, y);



}
