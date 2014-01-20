

#include <stdio.h>


int main () {


  int i, j, n, x;

  for (x=1; x<20; x++) {
    printf("\tFor additive series of size %d\n", x);
    printf("\tn\tadd\tseries\tformula\t\tnext\tf(n-1)\tf(n)\toffset\n");
    for (i = 1, j = 0, n =1 ; n<10; n++, i+=x ){
      j+=i;
      printf("\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", n, i, j, (x*n*n-(x-2)*n)/2,
      (x*(n-1)*(n-1)-(x-2)*(n-1))/2 + (x*n*n-(x-2)*n)/2 +(-x*n*n +3*x*n +n*n -3*n -2*x +2)/2,
      (x*(n-1)*(n-1)-(x-2)*(n-1))/2, (x*n*n-(x-2)*n)/2, (-x*n*n +3*x*n +n*n -3*n -2*x +2)/2 );
    }
    printf("\n\n");
  }

}
