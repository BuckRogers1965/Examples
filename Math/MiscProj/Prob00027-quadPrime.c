#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 40000
#include "prime.c"

int 
main (){

  InitSieve () ;

long ax = 0, bx = 0, nx = 0;
long a, b;

for (a = -1000; a <= 1000; a++) {
    for(b = -1000; b <= 1000; b++){
        long n = 0;
        while (is_prime(labs(n * n + a * n + b))) {
            n++;
        }
 
        if (n > nx) {
            ax = a;
            bx = b;
            nx = n;
        }
    }
}
  printf ("Solution a %ld b %ld is %ld\n", ax, bx, ax*bx );

exit(0);
 }
