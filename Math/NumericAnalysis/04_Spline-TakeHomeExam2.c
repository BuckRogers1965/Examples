#include <stdio.h>
#include "SplineInterpolation.h"

/* James M. Rogers
   06 March 2014

  compile with
    gcc matrix.c SplineInterpolation.c 04_Spline-TakeHomeExam2.c -lm
*/

int
main ()
{
  long double x;
  spline s = Spline_New(21);

  Spline_AddPoint(s,  0.9, 1.3 );
  Spline_AddPoint(s,  1.3, 1.5 );
  Spline_AddPoint(s,  1.9, 1.85);
  Spline_AddPoint(s,  2.1, 2.1 );
  Spline_AddPoint(s,  2.6, 2.6 );
  Spline_AddPoint(s,  3.0, 2.7 );
  Spline_AddPoint(s,  3.9, 2.4 );
  Spline_AddPoint(s,  4.4, 2.15);
  Spline_AddPoint(s,  4.7, 2.05);
  Spline_AddPoint(s,  5.0, 2.1 );
  Spline_AddPoint(s,  6.0, 2.25);
  Spline_AddPoint(s,  7.0, 2.3 );
  Spline_AddPoint(s,  8.0, 2.25);
  Spline_AddPoint(s,  9.2, 1.95);
  Spline_AddPoint(s, 10.5, 1.4 );
  Spline_AddPoint(s, 11.3, 0.9 );
  Spline_AddPoint(s, 11.6, 0.7 );
  Spline_AddPoint(s, 12.0, 0.6 );
  Spline_AddPoint(s, 12.6, 0.5 );
  Spline_AddPoint(s, 13.0, 0.4 );
  Spline_AddPoint(s, 13.3, 0.25);

  printf ("\n\nSolution test\n\n");
  for (x = 0.5; x < 14; x++)
    {
      printf ("Solution for x: %Lf with %d points: %Lf \n", x, Spline_PointCount(s),
	      Spline_Solve (s, x));
      printf ("First derivative at x: %Lf \n\n", Spline_Derive (s, x));
    }

  printf ("\n\nGraph\n\n");
  for (x = .5; x <= 14.1; x +=.1)
    {
      printf ("%Lf %Lf %Lf\n", x, Spline_Solve (s, x), Spline_Derive (s, x));
    }

  return 0;
}
