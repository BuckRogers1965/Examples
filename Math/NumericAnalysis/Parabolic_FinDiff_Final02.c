#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


int main (){

  long double h = 0.2;
  long double k = 0.04;

  long double i;
  long double t;
  long double t_min = 0;
  long double t_max = 0.4;

  long double x_min = 0;
  long double x_max = 4.0;

  long double alpha = 1 / (M_PI * M_PI) ;

  printf ("Exact Answer:\n\ni\t");

  for (t=t_min; t<=t_max; t+=k)
      printf("%Lf ", t);
  printf ("\n");

  for (i=x_min; i<=x_max; i+=h) {
      printf("%Lf ", i );
    for (t=t_min; t<=t_max; t+=k) {
      printf("%Lf ", powl (M_E, -t) * sinl(M_PI/2.0) * i + powl (M_E, -t/4.0) * sinl(M_PI/4.0) * i );
    }
    printf ("\n");
  }
  
  return 0;

}
