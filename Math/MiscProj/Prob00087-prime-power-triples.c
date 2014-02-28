#include <stdio.h>
#define MAXSIZE  7072
#define TARGET 50000000
#include "prime.c"

main (int argc, char *argv[])
{

  long long i, j, k;
  long count = 0;
  int acount = 0;
  char *found = calloc (1, TARGET + 1);
  long long res;

  InitSieve ();

  long long pows[3][MAXSIZE+1];
  for (i = 2; i <= MAXSIZE; i++)
    {
      if (is_prime (i))
	{
	  pows[0][acount] = i * i;
	  pows[1][acount] = i * i * i;
	  pows[2][acount] = i * i * i * i;
          acount++;
	}
    }

  for (i = 0; i < acount; i++)
    {
      for (j = 0; j < acount; j++)
	{
	  for (k = 0; k < acount; k++)
	    {
	      res = pows[0][i] + pows[1][j] + pows[2][k];
	      if (res >= TARGET)
		break;
	      if (!found[res])
		{
		  count++;
		  found[res] = 1;
		}
	    }
	}
    }
  printf ("Solution is %lu \n", count);
}
