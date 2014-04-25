#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

#define LM_PI	3.14159265358979323846264338327950288419716939937510L
#define LM_E	2.71828182845904523536028747135266249775724709369995L

long double f (long double x)
{ return sinl (LM_PI / 4.0 * x) * (1 + 2.0 * cosl (LM_PI / 4.0 * x));}

int main () {

  long double h = 0.2;
  long double k = 0.04;

  long double i;
  long double t;
  long double t_min = 0;
  long double t_max = 0.4;

  long double x_min = 0;
  long double x_max = 4.0;

  long double alpha = 4 / (LM_PI * LM_PI);
  long double lambda = alpha * (k / (h * h));

  int j = (x_max - x_min) / h;
  int p = (t_max - t_min) / k;

  int d;

  long double xa = -lambda / 2.0;
  long double xb = 1 + lambda;
  long double xc = -xa;
  long double xd = 1 - lambda;

  matrix *A = NewMatrix (j, j);
  matrix *B = NewMatrix (j, j);
  matrix *w = NewMatrix (j, 1);

  for (d = 1; d <= j; d++)
    {

      Mat_SetCell (A, d, d - 1, xa);
      Mat_SetCell (A, d, d, xb);
      Mat_SetCell (A, d, d + 1, xa);

      Mat_SetCell (B, d, d - 1, xc);
      Mat_SetCell (B, d, d, xd);
      Mat_SetCell (B, d, d + 1, xc);

      Mat_SetCell (w, d, 1, f ((d) * h));
    }

  printf ("A \n");
  Mat_Print (A);

  printf ("B \n");
  Mat_Print (B);

  matrix *Ai = Mat_FindInverse (A);
  printf ("Ai \n");
  Mat_Print (Ai);

  matrix *Temp = Mat_Mult (Ai, B);

  matrix *w1;

  long double results[j + 1][p];
  int q = 0;
  int s;
  int u;

  for (t = k; t <= t_max; t += k)
    {

      for (s = 0; s <= j; s++)
	    results[s][q] = Mat_GetCell (w, s + 1, 1);
      q++;

      w1 = Mat_Mult (Temp, w);
      Mat_Dispose (w);
      w = w1;
    }

  for (s = 0; s <= j; s++)
    results[s][q] = Mat_GetCell (w, s + 1, 1);

  printf ("Estimated Answer:\n\n       t ");

  for (t = t_min; t <= t_max; t += k)
    printf ("%8.5Lf ", t);
  printf ("\n");

  printf ("i\n");
  for (s = 0; s < j; s++)
    {
      printf ("%8.5Lf ", (s + 1) * h);
      for (u = 0; u <= p; u++)
	{
	  printf ("%8.5Lf ", results[s][u]);
	}
      printf ("\n");
    }

  printf ("\nExact Answer:\n\n       t ");

  for (t = .4; t <= t_max; t += k)
    printf ("%8.5Lf ", t);
  printf ("\n");

  printf ("i\n");
  for (i = x_min + h; i < x_max; i += h)
    {
      printf ("%Lf ", i);
      for (t = .4; t <= t_max; t += k)
	{
	  printf ("%8.5Lf ",
		  powl (LM_E, -t) * sinl (LM_PI / 2.0 * i) + 
		    powl (LM_E, -t / 4.0) *
		    sinl (LM_PI / 4.0 * i));
	}
      printf ("\n");
    }

  return 0;

}
