#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10

int
main () {

  long double a, b, c, d, e, f, r, s, tot = -1;
  for (a=0; a<MAX; a++)
    for (b=0; b<MAX; b++)
      for (c=0; c<MAX; c++)
        for (d=0; d<MAX; d++)
          for (e=0; e<MAX; e++)
            for (f=0; f<MAX; f++){
              r = (((((a*10+ b)*10 + c)*10 +d)*10 + e) *10 + f);
              s = powl(a,5) + powl(b,5) + powl(c,5) + powl(d,5) + powl(e,5) + powl(f,5);
              if ( r == s)
                 tot += r;
		 //printf("%0.0Lf\n", r);
        }
  
  printf("Solution is %0.0Lf\n", tot);
  exit (0);
}

