#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE  100000000
#include "prime.c"

#define LIMIT 100000

int
main (int argc, char *argv[])
{

  long i, j;
  long total = 2;

  InitSieve ();
  printf("Initialized Prime Sieve\n");

  for (i = 3; i <= LIMIT; i++, i++)
    {
      if (is_prime (i))
	{
	  total += i;
          printf("%ld %ld ", i, total);
          if (is_prime(total))
            printf("prime\n");
          else
            printf("\n");
          fflush(stdout);
	}
    }

reverse:
  printf("\n\n           reverse\n\n");
  //reverse directions  
  
  for (j = i; j > 2; j--, j--)
    {
      if (is_prime (j))
	{
	  total -= j;
          printf("%ld %ld\n", j, total);
	  if (is_prime (total))
	    goto done;

	}
    }

  printf ("Something went wrong\n");
  exit (0);

done:
  printf ("Solution is %lu \n", total);
  exit (0);

}
