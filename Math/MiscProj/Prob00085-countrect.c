#include <stdio.h>
#include <stdlib.h>
#define TARGET 2000000

long
series (long n, long b)
{
  return (b * n * n - (b - 2) * n) / 2;
}

void
main ()
{
  int x, y;
  long close, result, solx, soly;
  for (x = 35; x < 50; x++)
    for (y = x; y < 80; y++)
      {
	result = series (y, 1) * series (x, 1);
	if (labs (result - TARGET) < labs (close - TARGET))
	  {
	    close = result;
	    solx = x;
	    soly = y;
	  }
      }
  printf ("Solution is %ld at %ld %ld %ld\n",
      solx * soly, solx, soly, close);
}
