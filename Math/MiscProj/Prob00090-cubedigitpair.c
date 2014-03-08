#include <stdio.h>

#define MAX 10
#define DICE 6
#define ASIZE 9

int array[ASIZE][2] = { {0, 1}, {0, 4}, {0, 6}, {1, 6},
                {2, 5}, {3, 6}, {4, 6}, {6, 4}, {8, 1} };

void
Test (int t[], int d1[], int d2[])
{
  int i, j, k;

  for (i = 0; i < DICE; i++)
    for (j = 0; j < DICE; j++)
      for (k = 0; k < ASIZE; k++)
	  if (((d1[i] == array[k][0]) && (d2[j] == array[k][1]))
	      || ((d1[i] == array[k][1]) && (d2[j] == array[k][0])))
	      t[k] = 1;
}

void
Generate (int d1[], int a, int b, int c, int d)
{
  int i = -1;
  int pos = 0;
  while (pos < DICE)
    {
      i++;
      if (i == a || i == b || i == c || i == d)
	continue;
      if (i == 9)
	d1[pos] = 6;
      else
	d1[pos] = i;
      pos++;
    }
}

int t[ASIZE];
int
isvalid (int d1[], int d2[])
{
  int i, res = 0;

  Test (t, d1, d2);

  for (i = 0; i < ASIZE; i++)
      if (t[i])
	{
	  res++;
	  t[i] = 0;
	}

  if (res < 9)
    return 0;

  return 1;
}

void
main ()
{
  int i, j, k, l, m, n, o, p;
  int valid = 0;
  int d1[DICE];
  int d2[DICE];

  for (i = 0; i < ASIZE; i++)
    t[i] = 0;

  //permutate dice one
  for (i = 0; i < MAX - 3; i++)
    for (j = i + 1; j < MAX - 2; j++)
      for (k = j + 1; k < MAX - 1; k++)
	for (l = k + 1; l < MAX; l++)
	  {
	    Generate (d1, i, j, k, l);

	    // permutate dice two
	    for (m = i + 1; m < MAX - 3; m++)
	      for (n = m + 1; n < MAX - 2; n++)
		for (o = n + 1; o < MAX - 1; o++)
		  for (p = o + 1; p < MAX; p++)
		    {
		      Generate (d2, m, n, o, p);
		      valid += isvalid (d1, d2);
		    }
	  }
  printf ("count %d \n", valid);
}
