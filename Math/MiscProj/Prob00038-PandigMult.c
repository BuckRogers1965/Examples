#include <stdio.h>
#include <stdlib.h>

long
concat (long x, long y)
{

  long z;
  char str[1000];
  sprintf (str, "%ld%ld\0", x, y);

  sscanf (str, "%ld", &z);

  //printf ("%ld %ld %ld\n", x, y, z);
  return z;
}

int
isPandig (long x)
{

  int i, a[10];
  char str[1000];
  sprintf (str, "%ld\0", x);
  for (i = 0; i < 10; i++)
    a[i] = 0;
  for (i = 0; str[i]; i++)
    a[str[i] - '0']++;

  //printf("%s\n", str);
  if (i != 9)
    return 0;

  int res = 0;
  for (i = 1; i < 10; i++)
    if (a[i])
      res++;

  if (res != 9)
    return 0;

  return 1;
}

void
main ()
{
  long i, r = 0;
  for (i = 9400; i > 9300; i--)
    {
      r = concat (i, 2 * i);
      if (isPandig (r))
	{
	  break;
	}

    }
  printf ("Solution is %ld\n", r);

  exit (0);
}
