#include <stdio.h>
#include <stdlib.h>

int
iter (int i, int coin[], int cur)
{

  int a, res = 0;

  // ending condition
  if (!i)
    return coin[i];

  // main function
  for (a = cur; a >= 0; a -= coin[i])
    res += iter (i - 1, coin, a);

  return res;
}

int
main ()
{
  int number = 7;
  int coin[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };

  printf ("Solution is %d\n", iter (number, coin, coin[number]));

  exit (0);
}
