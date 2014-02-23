#include <stdio.h>
#include "triangle.txt"

// the triangle of values is called tri
// This starts with one value and increases by 1 value per level.

#define LEVELS 100
#define TRI 1

long double heat [5050];


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


long double
retheat(int level, int pos){
  int start;
  pos -= 1;
  if (level>1) 
     start = series (level-1, TRI);
  else 
     return heat[0];
  return heat[start+pos];
}

long long
search(int level, int pos){

  long long total = retval(level,pos);

  printf("%lld +", total);

  if (level == LEVELS)
	return total;

  if (retheat(level+1, pos+1) > retheat(level+1, pos))
    pos++;

  return search (level+1, pos) + total;
}

void
main ()
{
  int i, j, k=0;
  int start=0;
  int lev=0;

  for (i=0; i<(LEVELS+1); i++) {
    lev++;
    for (j=0; j<i; j++) {
      long double val;
      val = tri[start+j];
//      printf("%lld ", val);
      heat[start+j]   = val;
      k++;
    }
    start = k;
//    printf("\n");
  }
  
  k=0;
  start=0;
  lev=0;
  int pstart;

  for (i=LEVELS; i>1; i--) {
    start = series(i-1, TRI);
    pstart = series(i-2, TRI);
    for (j=i; j>0; j--) {
      long double val;
      int cpos = start+j-1;
      val = heat[cpos];
      //printf("***< %0.0Lf s %d j %d l %d > ", val, start, j, lev);
      printf("%0.0Lf ", val);
      if (heat[cpos-i+1]> heat[cpos-i+1+1])
        heat[cpos-i+1]   +=val;
      else
        heat[cpos-i+1+1] +=val;
    }
    printf("\n");
  }

 printf("Solution is %lld\n ", search(1,1));
  
}
