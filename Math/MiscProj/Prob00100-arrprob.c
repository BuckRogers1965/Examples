#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define START 1000000000000
#define START 1000000000000

int
main () {

  long double i, j, t, t2, sr;

  sr = sqrtl(.5);

  for (i=START; ; i++) {
    t=floorl(sr*i) - 2.0;
    t2 = t + 4.0;
    for (j = t; j < t2 ;j++ ) {
      printf ("%Lf %Lf = %Lf\n", i, j, 10*j/i * (j-1)/(i-1));
      if ( (j/i) * (j-1)/(i-1) == 0.5)
        goto found;
    }
  }
  
    printf("Did not find solution %0.0Lf %0.0Lf \n", i, j);
    exit (0);
found:
    printf("Solution is %0.0Lf %0.0Lf\n",i ,j);
}
