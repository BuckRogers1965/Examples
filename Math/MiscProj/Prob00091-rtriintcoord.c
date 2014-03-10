#include <stdio.h>

#define SIZE 50

/*  0 0     0
    1 3     3  3
    2 14   11  8
    3 

   ...
   50  14234
*/

long
gcd (long a, long b)
{
  long y, x;

  if (a > b)
    {
      x = a;
      y = b;
    }
  else
    {
      x = b;
      y = a;
    }

  while (x % y != 0)
    {
      long temp = x;
      x = y;
      y = temp % x;
    }

  return y;
}


void
main ()
{

  int i, j, k, x, y;
  int result;
  int presult = 0;
  int diff = 0;
  int pdiff = 0;
  int size = 50;
  int interval = 1;

  for (i = interval; i <= size; i += interval)
    {
      result = i * i * 3;
      for (x = 1; x <= i; x++)
	{
	  for (y = 1; y <= i; y++)
	    {
	      int fact = gcd (x, y);
	      result +=
		(y * fact / x < (i - x) * fact / y)
                  ? (y * fact / x) * 2
                  : ((i - x) * fact / y) * 2;
	    }
	}
        diff = result - presult;
        printf ("Solution at\t%d\tis\t%d\tdiff\t%d\tpdiff\t%d\n", i, result, diff, diff-pdiff);
        presult = result;
        pdiff = diff;
        result = 0;
    }
}
