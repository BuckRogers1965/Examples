#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
from here: http://www.mathblog.dk/
project-euler-36-palindromic-base-10-2/
*/
int isPal(long long n, long long b){
    long long  r = 0;
    long long k = n;
 
    while (k > 0) {
        r = b * r + k % b;
        k /= b;
    }
    return n == r;
}

long long Lychrel(long long n) {
    long long r = 0;
    long long k = n;
    long long b = 10;
 
    while (k > 0) {
        r = b * r + k % b;
        k /= b;
    }
    return n + r;
}

#define MAX 10000
#define MAXTRY 50

int
main ()
{

  long long  i, j, y;
  long long r = 3;

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
  printf ("Solution is %lld\n",  r);
  exit (0);
}
