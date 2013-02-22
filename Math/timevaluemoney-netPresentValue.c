#include <stdio.h>
#include <math.h>

int
main ()
{

  int timelength = 40;
  int t = 1;
  double r;

  printf ("Net Present Value.\n");
  for (t = 4; t < 26; t++)
    printf ("\t%d%%", t);
  printf ("\n");

  for (t = 1; t <= timelength; t++)
    {
      printf ("%d\t", t);
      for (r = 4; r < 26; r++)
	printf ("%f\t", 1 / pow (1.0 + r / 100, t));
      printf ("\n");
    }
}
