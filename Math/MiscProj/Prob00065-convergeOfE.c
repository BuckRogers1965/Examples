#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

long double
addDigits(long double x){
  long double y = 0;
  int i;
  char digits[100];
  sprintf(digits, "%0.0Lf\0", x);
  printf("%0.0Lf\n", x);
  for (i = 0;digits[i]; i++){
    y += (digits[i] - '0') ;
  } 
  return y;
}

int
main ()
{
  long double i, result = 0;
  long double d = 1;
  long double  n = 2;
  long double c;

  for (i=2; i<=MAX; i++){
    long double x = d;
    //long double   c = (i%3==0) ? (2*i)/3 : 1;
    //long double   c = (i%3==0) ? (2*i)/3 : 1;
     c = fmodl(i, 3.0);
    if (c == 0.0 ) c = 2*(i/3) ;
    else c = 1.0;
    d = n;
    n = c * d + x;
  }
  result = addDigits(n);

  printf("Solution is %0.0Lf\n", result );
  exit (0);
}
