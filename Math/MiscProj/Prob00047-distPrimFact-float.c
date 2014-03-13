#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  MAXSIZE 136000
#include "prime.c"

int
factorcountdistinct (long double find)
{
  long double i;
  int factors = 0;
  
  if (remainderl (find, 2) == 0)
    {
      factors++;
      find = find / 2;
      while (remainderl (find, 2) == 0)
	find = find / 2;
    }

  for (i = 3; i <= find; i++, i++)
    {
      if (is_prime(find))
         return factors+1;

      if (!is_prime (i))
	  continue;
      if (remainderl (find, i) == 0)
	{
	  factors++;
          if (factors > 4) return factors;
          find = find / i;
	  while (remainderl (find, i) == 0)
	    {
	      find = find / i;
	    }
	}
    }
  return factors;
}

int
main ()
{
  int t = 4;
  int c = 1;
  long r = 2*3*5*7;

  InitSieve ();

  while (c < t)
    {
      r++;
      if (factorcountdistinct (r) == t)
	c++;
      else
	c = 0;
    }

  printf ("Solution is %ld\n", r - 3);
  exit (0);
}
