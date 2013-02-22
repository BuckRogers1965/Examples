#include <stdio.h>

/* This program calculates PI 

     1   1   1   1   1   1 
PI = _ - _ + _ - _ + _ - _ ...
     1   3   5   7   9   13

  alternatively add and subtract the reciprocal
  of all the odd numbers and you converge to 
  PI, before computers this must have been very 
  tedious.
*/


main(){

long double i,j,k,m;

  for (i=0,j=1,k=1,m=1;j<1000000000000.0;j++, j++){
    i = i + k/j;
    k = k * -1;

    if (j>m){
      printf("iterations, %.0Lf\tvalue %.30Lf\n", m, 4.0*i);
      m = m * 10;
    }

  }


}
