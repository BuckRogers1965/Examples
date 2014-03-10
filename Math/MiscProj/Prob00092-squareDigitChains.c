#include <stdio.h>
#include <stdlib.h>
#define MAX 10000000

long
chain(long x){
  long y = 0;
  int i;
  char digits[100];
  sprintf(digits, "%ld\0", x);
  for (i = 0;digits[i]; i++){
    y += (digits[i] - '0') * (digits[i] - '0') ;
  } 
  return y;
}

int
main ()
{
  long i, x, result = 0;

  for (i=1; i<MAX; i++){
    x = i;
    while (1) {
      //printf("--> %ld ", x);
      if (x==1)
        goto next;
      if (x==89) {
        result++;
        goto next;
      }
      x = chain(x);
    }
next:
  //printf ("\n");
  ;
  }

  printf("Solution is %ld\n", result );
  exit (0);
}
