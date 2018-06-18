
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main () {


  long j, n, x;

  long double i, r, t, z;

	z=10; t=0;

	t=3.5;

  for (i=1; i < z; i++) {
	r = 2.5/powl(6, i);
	t += r;

	printf("Res %Lg	Total  %Lg \n", r, t);



  }

 	printf("Total  %Lf \n", t);
 
}



