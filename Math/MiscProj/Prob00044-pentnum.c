#include <stdio.h>
#include <math.h>
#define MAX 5000

long double series(long double n){ return n*(3*n-1)/2; }

int isinseries(long double s){
  long double x =(1 + sqrtl(1 + 24 * s))/6;
  if (floorl(x) == x)
    return 1;
  return 0;
}

void main (){
  int j, k;
  long long tj, tk, dp, dm; 

  for (j=1; j<MAX; j++) {
    tj = series(j);
    for (k=j+1; k<MAX; k++) {
      tk = series(k);
      dp = tk+tj;
      dm = tk-tj;
      if (isinseries(dp) & isinseries(dm))
         printf("\n%d %d %lld %lld %lld Solution is %lld\n",
            j, k,  tj, tk, dp, dm);  
    }
  }
}
