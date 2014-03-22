#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.71828182845904523536

long double
f1 (long double t, long double u1, long double u2)
{
  return u2;
}

long double
f2 (long double t, long double u1, long double u2)
{
  return powl (E, 2*t) * sinl (t) - 2 * (u1) + 2 * u2;
}

int
main ()
{

  long double k1_1, k1_2, k2_1, k2_2, k3_1, k3_2, k4_1, k4_2;
  long double t = 0.0;		// set to start
  long double h = 0.1;		// interval between steps
  long double max = 10;		// number of steps

  long double w[3][100];
  // y (0) = u1(0) =
  w[1][0] = -0.4;
  // y'(0) = u2(0) =
  w[2][0] = -0.6;

  int i;
  for (i = 0; i <= max; i++)
    {
      k1_1 = h * f1 (t, w[1][i], w[2][i]);
      k1_2 = h * f2 (t, w[1][i], w[2][i]);

      k2_1 = h * f1 (t + h / 2.0, w[1][i] + 0.5 * k1_1, w[2][i] + 0.5 * k1_2);
      k2_2 = h * f2 (t + h / 2.0, w[1][i] + 0.5 * k1_1, w[2][i] + 0.5 * k1_2);

      k3_1 = h * f1 (t + h / 2.0, w[1][i] + 0.5 * k2_1, w[2][i] + 0.5 * k2_2);
      k3_2 = h * f2 (t + h / 2.0, w[1][i] + 0.5 * k2_1, w[2][i] + 0.5 * k2_2);

      t += h;
      k4_1 = h * f1 (t, w[1][i] + k3_1, w[2][i] + k3_2);
      k4_2 = h * f2 (t, w[1][i] + k3_1, w[2][i] + k3_2);

      w[1][i + 1] = w[1][i] + 1.0 / 6.0 * (k1_1 + 2 * k2_1 + 2 * k3_1 + k4_1);
      w[2][i + 1] = w[2][i] + 1.0 / 6.0 * (k1_2 + 2 * k2_2 + 2 * k3_2 + k4_2);

      //printf
	//("%3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf\n",
	 //k1_1, k1_2, k2_1, k2_2, k3_1, k3_2, k4_1, k4_2);
      printf ("%0.4Lf  %0.10Lf  %0.10Lf\n", t - h, w[1][i], w[2][i]);
    }
  //printf ("%0.4Lf  %0.10Lf  %0.10Lf\n", t - h, w[1][i], w[2][i]);

  exit (0);
}
