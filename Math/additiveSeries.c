

#include <stdio.h>


int main () {


  int i, j, n, x;

  for (x=1; x<20; x++) {
    printf("for additive series of size %d\n", x);
    for (i = 1, j = 0, n =1 ; n<10; n++, i+=x ){
      j+=i;
      printf("%d  %d  %d  %d \n", n, i, j, (x*n*n-(x-2)*n)/2);
    }
    printf("\n\n");
  }

}
