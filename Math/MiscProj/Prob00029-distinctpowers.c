#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100


int 
main () {

  long double a, b;
  for (a=2; a<=MAX; a++)
    for (b=2; b<=MAX; b++)
      printf("%0.10Lf\n", log(a)*b);

  exit (0);
}


