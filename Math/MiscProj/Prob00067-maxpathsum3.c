#include <stdio.h>
#include "triangle.txt"

// the triangle of values is called tri
// This starts with one value and increases by 1 value per level.

#define LEVELS 100
#define TRI 1

int heatmap[5050];

// n is the index, and b is the base
//return the nth additive number from the b series.
long double
series (long double n, long double b)
{
  return (b * n * n - (b - 2) * n) / 2;
}

void printval(int level, int pos){
  printf("%d ", retval(level, pos));
}

void
setval(int level, int pos, int val){
  int start;
  pos -= 1;
  if (level>1) {
     start = series (level-1, TRI);
     tri[start+pos] = val;
  } else 
     tri[0] = val;
}


int
retval(int level, int pos){
  int start;
  pos -= 1;
  if (level>1)
     start = series (level-1, TRI);
  else 
     return tri[0];
  return tri[start+pos];
}

long long
maxlong (long long a, long long b)
{
  if (a > b)
    return a;
  return b;
}

long double
tritot (int depth, int pos) {
  int i,j;
  long double total = 0;
  for (i=0; i<LEVELS-depth+3; i++) {
    for(j=0; j<i+1; j++) {
      total += retval(depth+i-1, pos+j);
//      printval(depth+i-1,pos+j);
      }
//    printf("\n");
  }
  return total;
}

long long
search ( int depth, int level, int curr_pos)
{
  long long total = 0;

  total = retval(depth, curr_pos);
  printf("%lld+", total);
  if (depth ==  LEVELS)
	return total;

 // printf("+ d %d l %d p %d t %lld +", depth, level, curr_pos, total);

  long double maxr = tritot (depth+1, curr_pos);
  long double maxl = tritot (depth+1, curr_pos+1);

 // printf(" l %0.0Lf r %0.0Lf ", maxl, maxr);
  fflush(stdout);

  if (maxl > maxr)
    {
      curr_pos += 1;
//      printf ("l\n");
    }
    else
    {
//      printf ("r\n");
    }

  return search(depth+1, level, curr_pos) + total;
}


long long
msearch (){

 // createheatmap
}

void
main ()
{
  int i, j;
  long long tot =0;

  for (i=0; i<5050; i++) 
    tot += tri[i];

  printf ("Total is %lld \n", tot);
/*
  for (i=LEVELS; i>0; i--) {
    for (j=1; j<i+1; j++, tot++)
      printval(i,j);
    printf("\n");
  }
  printf ("\ntot  is %d\n", tot);
*/

//for (i=2; i<99; i++){
  long long result;
  result = search ( 1, 1 , 1 );

  printf ("\nSolution  is %lld\n",  result);
//}
}
