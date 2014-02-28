#include <stdio.h>


long double 
f(long double x){

return ((-0.00018 *x*x*x*x*x*x*x*x +0.008248 *x*x*x*x*x*x*x -0.151935 *x*x*x*x*x*x +1.44846 *x*x*x*x*x -7.64631 *x*x*x*x + 21.916592 *x*x*x - 30.136584 *x*x +14.25303 *  x + 75 ) *3600/5280);
}

void
main (){

  long double result;
  long double i;

  for (i=5.6;i<5.7; i+=.000000001)
    if (f(i)>55.0){
	printf ("Broke speed at %0.20Lf\n", i); 
        break;
    }


}
