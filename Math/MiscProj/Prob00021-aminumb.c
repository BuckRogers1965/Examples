#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

long a[MAX + 1];

long
D (long n)
{
  long i, r = 0;
  for (i = 1; i < n / 2 + 1; i++)
    {
      if (n % i == 0)
	r += i;
    }
  return r;
}

int
main ()
{
  int i;
  for (i = 1; i <= MAX; i++)
    {
      a[i] = D (i);
    }
  // printf("220 is %ld  %ld\n", a[220], a[a[220]] );

  long r = 0;
  for (i = 1; i <= MAX; i++)
    {
      if (a[i] < MAX && a[a[i]] < MAX)
	if (i == a[a[i]] && i != a[i])
	  r += a[i];
    }
  printf ("Solution is %ld\n", r);
  exit (0);
}
