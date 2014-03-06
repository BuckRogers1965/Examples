#include <stdio.h>
#include "SplineInterpolation.h"

/* James M. Rogers
   06 March 2014
*/

int
main ()
{
  long double x;

  spline * s = Spline_New(6);

  Spline_AddPoint(s,  1.0,  6.0);
  Spline_AddPoint(s,  3.0,  2.0);
  Spline_AddPoint(s,  5.0,  5.0);
  Spline_AddPoint(s,  7.0, 10.0);
  Spline_AddPoint(s,  8.0,  4.0);
  Spline_AddPoint(s, 10.0,  1.0);

  // now that the solution values are stored in P you can call SolveSpline()
  printf ("\n\nSolution test\n\n");
  for (x = 0.5; x < 11; x++)
    {
      printf ("Solution for x: %Lf with %d points: %Lf \n", x, Spline_PointCount(s),
	      Spline_Solve (s, x));
      printf ("First derivative at x: %Lf \n\n", Spline_Derive (s, x));
    }

/*
  printf ("\n\nGraph\n\n");
  for (x = 1; x <= 10.1; x +=.1)
    {
      printf ("%Lf %Lf\n", x, SolveSpline (n, P, x));
    }
*/

  return 0;
}
