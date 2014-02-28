#include <stdio.h>
#include <math.h>

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

long
f (long limit)
{
  long a, b, c;
  long m, n, p, inc;
  long count = 0;
  int triangles[limit+1];
  for (a=0; a<limit+1; a++)
    triangles[a] = 0;

  for (m = 2; m < sqrt (limit); m++)
    for (n = 1; n < m; n++)
      if (((n + m) % 2) == 1 && gcd (n,m) == 1)
	{
	  a = m * m + n * n;
	  b = m * m - n * n;
	  c = 2 * m * n;
	  p = a + b + c;
	  inc = p;
	  while (p <= limit)
	    {
	      triangles[p]++;
	      if (triangles[p] == 1)
		count++;
	      if (triangles[p] == 2)
		count--;
	      p += inc;
	    }
	}

  return count;
}

void
main ()
{
  printf ("\nSolution is %ld \n", f (15));
  printf ("\nSolution is %ld \n", f (1500000));
}
