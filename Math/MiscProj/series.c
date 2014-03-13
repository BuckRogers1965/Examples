#include <stdio.h>
#include <math.h>

#define TRIANGLE    1
#define PENTAGONAL  3
#define HEXAGONAL   4

// n is the index, and b is the base
//return the nth additive number from the b series.
long double
series(long double n, long double b) {
    return (b*n*n-(b-2)*n)/2;
}

// b>0, get the additive series index n 
// given a number from an additive series 
// and a base to check
// n is the index, and b is the base
//
// return value is 0 if there was no exact match
// or the nth index integer number otherwise
inline long long
isinseries(long double y, long double b){
  long double n = (sqrtl(b*b+8*b*y-4*b+4)+b-2)/(2*b);
  //printf("%Lf %Lf %Lf \n", y, b, n);
  if (floorl(n) == n)
    return n;
  return 0;
}

