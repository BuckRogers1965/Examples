
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main () {


  long n;

  long double i, j, r, t, x, z;

	z=25; t=0;



  for (j=2; j<101; j+=2) {

	t=x=j/2+.5;
  for (i=1; i < z; i++) {
	r = (x-1)/powl(j, i);
	t += r;

	//printf("die %Lg	Res %Lg	Total  %Lg \n", x, r, t);
  }

 	printf("Res %Lg	Average %Lg \n", r, t);


  }
 
}



