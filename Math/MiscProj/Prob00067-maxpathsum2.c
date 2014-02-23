#include <stdio.h>
#include "triangle.txt"

// the triangle of values is called tri
// This starts with one value and increases by 1 value per level.

#define LEVELS 100
#define TRI 1

// n is the index, and b is the base
//return the nth additive number from the b series.
long double
series (long double n, long double b)
{
  return (b * n * n - (b - 2) * n) / 2;
}

int
retval(int level, int pos){
  int start;
  if (level>1)
     start = series (level-1, TRI);
  else 
     start = 0;
  return tri[start+pos];
}

long long
maxlong (long long a, long long b)
{
  if (a > b)
    return a;
  return b;
}

long long
findmax (int depth, int level, int pos)
{
  int curr_width = depth;
  int curr_start = series (depth - 1, TRI);
  int current = retval(depth, pos);

  // reached the end of this search
  if (level == 1)
    return current;

  // top of the pyramid
  if (depth < 2)
    return tri[0];

  // far left edge
  if (pos == 1)
    return (findmax (depth - 1, level - 1, pos) + current);

  // far right edge
  if (pos == curr_width)
    return (findmax (depth - 1, level - 1, pos - 1) + current);

  // find the maximum value and return it
  current += maxlong (
		       // look left
		       findmax (depth - 1, level - 1, pos-1),
		       // look right
		       findmax (depth - 1, level - 1, pos));
  return current;
}

long long
search (int level)
{
  int depth;
  int max = 0;
  int pos = 0;
  long total = 0;
  int curr;

  depth = LEVELS;
  // find the maximum value in bottom row
  // by totally up the maximum for levels high
  int srch;
  for (srch = 1; srch <= depth; srch++)
    {
      fflush (stdout);
      int current = findmax (depth, level+10, srch);

      //printf ("s %d c %d \n", srch, current);
      if (current > max)
	{
	  max = current;
	  pos = srch;
	}
    }

  //report where we are
  total += retval(depth, pos);
  printf ("%d+", retval(depth,pos));

  for (depth-- ; depth >0 ; depth--) {
    long maxl, maxr;

    // which path do we travel?
    //search left
    if (pos == 1){
      maxl = 0;
      // position stays the same
      goto report;
    } else
      maxl = findmax (depth, level, pos-1);

    //search right
    if (pos == depth) {
      maxr = 0;
      pos -= 1;
      goto report;
    } else
      maxr = findmax (depth, level, pos);

    // now that we have a path, switch to it
    // stay in same position to travel right
    if (maxl > maxr ) 
      pos -= 1;

  report:
    //report where we are
    total += retval(depth, pos);
    printf ("%d+", retval(depth,pos));
    fflush (stdout);
  }

  return total;
}

void printval(int level, int pos){
  printf("%d ", retval(level, pos));
}

void
main ()
{
  int i, j;

/*
  for (i=LEVELS; i>0; i--) {
    for (j=0; j<i; j++)
      printval(i,j);
    printf("\n");
  }
*/

for (i=1; i<10; i++){
  long long result;
  result = search (i);
  printf ("\nSolution at level %d is %lld\n", i, result);
}
}
