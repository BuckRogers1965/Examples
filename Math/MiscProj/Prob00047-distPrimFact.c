#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#define  MAXSIZE 136000
#include "prime.c"

int
factorcountdistinct (long long find)
{
  long long i;
  int factors = 0;
  
  if (find % 2 == 0)
    {
      factors++;
      find = find / 2;
      while (find % 2 == 0)
	find = find / 2;
    }

  for (i = 3; i <= find; i++, i++)
    {
      if (is_prime(find))
         return factors+1;
      if (!is_prime (i))
	  continue;
      if (find % i == 0)
	{
	  factors++;
          find = find / i;
	  while (find % i == 0)
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
  long long r = 1;

  InitSieve ();

  while (c < t)
    {
      r++;
      if (factorcountdistinct (r) == t)
	c++;
      else
	c = 0;
    }

  printf ("Solution is %lld\n", r - t +1);
  exit (0);
}
