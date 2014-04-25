#include <stdio.h>
#include "matrix.h"
#include <math.h>

// u(x, max-y)
long double FN (long double x, long double y)
	{ return (logl (x * x + 1.0)); }

// u(x, min-y)
long double FS (long double x, long double y)
	{ return (2.0 * logl (x)); }

// u(max-x, y)
long double FE (long double x, long double y)
	{ return (logl (y * y + 4.0)); }

// u(min-x, y)
long double FW (long double x, long double y)
	{ return (logl (y * y + 1.0)); }

long double exact (long double x, long double y)
	{ return (logl (x * x + y * y)); }

int main () {

  long double h = 1.0 / 3.0;
  long double k = h;

  long double init = 2.0 * (h / k * h / k + 1.0);

  long double offset = -(h * h) * 0;
  printf ("h %Lf  k %Lf  init %Lf  offset %Lf \n\n", h, k, init, offset);

  matrix *m = NewMatrix (4, 4);
  matrix *v = NewMatrix (4, 1);

  Mat_SetCell (v, 1, 1, FW (1.0 + h, h*2.0)
		      + FN (1.0 + h, h*2.0) + offset);
  Mat_SetCell (m, 1, 1, init);
  Mat_SetCell (m, 1, 2, -1);
  Mat_SetCell (m, 1, 3, -1);

  Mat_SetCell (v, 2, 1, FN (1.0 + h * 2.0, h * 2.0)
		      + FE (1.0 + h * 2.0, h * 2.0) + offset);
  Mat_SetCell (m, 2, 2, init);
  Mat_SetCell (m, 2, 1, -1);
  Mat_SetCell (m, 2, 4, -1);

  Mat_SetCell (v, 3, 1, FW (1.0 + h, h)
                      + FS (1.0 + h, h) + offset);
  Mat_SetCell (m, 3, 3, init);
  Mat_SetCell (m, 3, 1, -1);
  Mat_SetCell (m, 3, 4, -1);

  Mat_SetCell (v, 4, 1, FE (1.0 + h * 2.0, h)
                      + FS (1.0 + h * 2.0, h) + offset);
  Mat_SetCell (m, 4, 4, init);
  Mat_SetCell (m, 4, 2, -1);
  Mat_SetCell (m, 4, 3, -1);

  printf ("matrix\n");
  Mat_Print (m);

  printf ("vector\n");
  Mat_Print (v);

  matrix *i = Mat_FindInverse (m);

  printf ("inverse\n");
  Mat_Print (i);

  matrix *r = Mat_Mult (i, v);

  printf ("result\n");
  Mat_Print (r);

  printf ("The exact answer\n");
  matrix *r2 = NewMatrix (4, 1);
  Mat_SetCell (r2, 1, 1, exact (1.0 + h * 1.0, h * 2.0));
  Mat_SetCell (r2, 2, 1, exact (1.0 + h * 2.0, h * 2.0));
  Mat_SetCell (r2, 3, 1, exact (1.0 + h * 1.0, h * 1.0));
  Mat_SetCell (r2, 4, 1, exact (1.0 + h * 2.0, h * 1.0));
  Mat_Print (r2);

  printf ("Working Backwards back to v for trouble shooting.\n");
  matrix *v2 = Mat_Mult (m, r2);
  Mat_Print (v2);

  Mat_Dispose (m);
  Mat_Dispose (v);
  Mat_Dispose (v2);
  Mat_Dispose (i);
  Mat_Dispose (r);
  Mat_Dispose (r2);

  return 0;
}
