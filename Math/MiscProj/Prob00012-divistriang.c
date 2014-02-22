#include <stdio.h>
#include <math.h>

long double 
series(long double n, int x){
   return (x*n*n-(x-2)*n)/2 ;
}

int
divides(long double first, long double second){
  unsigned long r =  remainderl(second, first);
  if (r == 0.0)
	return 1;
  else
      return 0;
}

int
findfactors (long double find){

  long double i;
  int factors = 0;
  long double max = sqrtl(find) + 1 ;
  for ( i = 1 ; i <= max;  i++){
    if (divides(i, find)) {
//        printf("%0.0Lf ", i);
        factors++;
    } 
  }

  return factors*2;
}

void
main (){
  long double i;

  printf("\n");
  for (i = 2; i<200000 ; i++) {
    long double tri = series (i, 1);
    int res = findfactors(tri);
    if (res >= 450 )
      printf("i  %0.0Lf tri %0.0Lf factors %d \n", i, tri, res);
  }
}
