#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
from here: http://www.mathblog.dk/
project-euler-36-palindromic-base-10-2/
*/
int isPal(long double n, long double b){
    long double  r = 0;
    long double k = n;
 
    while (k > 0) {
        r = b * r + fmodl(k,b);
        k = floorl(k/b);
    }
    return n == r;
}

long double Lychrel(long double n) {
    long double r = 0;
    long double k = n;
    long double b = 10;
 
    while (k > 0) {
        r = b * r + fmodl(k,b);
        k = floorl(k/b);
    }
    return n + r;
}

#define MAX 10000
#define MAXTRY 50

int
main ()
{

  long double  i, j, y;
  long double r = 3;

  for (i = 180; i < MAX; i++) {
    y = i;
    for (j = 0; j < MAXTRY; j++)
    {
//      printf("%d -> ", y);
      if (isPal (y, 10) )
	{
//          printf(" Not ");
          break;
	}
       y = Lychrel(y);      
    }
    if (j==MAXTRY) {
//      printf(" Yes ");
      r++;
    }
//    printf("\n");
  }
  printf ("Solution is %0.0Lf\n",  r);
  exit (0);
}
