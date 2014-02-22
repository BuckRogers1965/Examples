#include <stdio.h>

void
main (){

  int i, j, k;
  
  long long sum = 1;
  long long cc = 1; 

  for ( i = 2; i < 1002; i++, i++ ) {
    for ( j = 0; j < 4; j++) {
       cc += i;
       //printf("%lld\n", cc );
       sum +=cc;
    }
  }
  printf("\nSolution is %lld\n", sum );
}
