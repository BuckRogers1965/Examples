#include <stdio.h>

long
sumofsquares(long long size){
 int i;
 long res = 0;
 for (i=1; i <= size; i++)
   res += i*i;
 printf(" %ld ", res);
 return res;
}

long
sumsquared(long long n, long long x){
   long res= (x*n*n-(x-2)*n)/2 ;
   res*=res;
 printf(" %ld ", res);
   return res;
}

long 
diff(long long size) {
  return (sumsquared(size,1) - sumofsquares(size) );
}


void 
main (){
  int i;

  for (i=5 ; i < 101 ; i = i+5)
    printf("Solution %ld for size %d \n", diff(i), i);
}
