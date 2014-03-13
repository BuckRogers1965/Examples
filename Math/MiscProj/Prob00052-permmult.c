#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
matchp (long x, long y)
{
  char sx[100];
  char sy[100];

  int i, j, match = 0;
  int sxlen, sylen;

  sprintf (sx, "%ld\0", x);
  sprintf (sy, "%ld\0", y);

  sxlen = strlen (sx);
  sylen = strlen (sy);
  if (sxlen != sylen)
    return 0;

//  printf ("Matching %s and %s\n", sx, sy);
  for (i = 0; sx[i]; i++)
    for (j = 0; sy[j]; j++)
      if (sx[i] == sy[j])
	{
	  //       printf("%c %c\n", sx[i], sy[j]);
	  match++;
	  sy[j] = ' ';
	  break;
	}

  if (match == sxlen)
    return 1;
  return 0;
}

int
checkp (long i)
{
  long j, x;

  x = 2 * i;

  for (j = 3; j < 7; j++)
    if (!matchp (x, j * i))
      return 0;

  return 1;
}

int
main ()
{
  long i;

  for (i = 100; i < 200000; i++)
    if (checkp (i))
      goto found;

  printf ("No Solution found\n");
  exit (0);
found:
  printf ("Solution is %ld\n", i);
  exit (0);
}
