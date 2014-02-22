#include <stdio.h>


/*
A Pythagorean triplet
is a set of three natural numbers such that
a < b < c   and   a2 + b2 = c2
There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/


void
main (){

  int a, b, c;
  int max = 1000;

  for (c=max; c>-1; c-- )
    for (b=c-1; b>-1; b-- ) {
      a = 1000 - (b+c); 

      if ( a < 0 ) continue;
      if ( a > b ) continue;
      if ( (a*a + b*b) != c*c) continue;

      goto found;
    }



found:
  printf("Found a %d b %d c %d  a^2 %d + b^2 %d = c^2 %d.  Solution %d\n", a, b, c, a*a, b*b, c*c, a*b*c);
}


