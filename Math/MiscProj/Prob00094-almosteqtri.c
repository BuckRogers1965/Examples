#include <stdio.h>
#include <math.h>
#define LIMIT 1000000000


inline long double 
A(long double a, long double b, long double c, long double p){
  return sqrtl( p*(p-a)*(p-b)*(p-c) );
}

long double
C (long double s, long double h) {

  long double p = s*2+h;
  if (p >=  LIMIT) 
    return 0;

  long double a = A(s,s,h,p/2);

  //printf ("%0.0Lf\t%0.0Lf\t%0.2Lf\t%Lf\n", s, h, p, a);
  if (floorl(a) == a) 
    return p;

  return 0;
}


void
main (){

   long double  i;
   long double p = 0;
   long double temp;

  //printf ("s\th\tp\ta\n");
  for (i=2; i<=LIMIT/3; i++) {
     p += C(i, i+1);
     p += C(i, i-1);
    // printf("\n");
    //printf("%0.0Lf %Lf\n", i, (i*i*(i+1)));
  }
  printf("Solution is %0.0Lf\n", p);
}
