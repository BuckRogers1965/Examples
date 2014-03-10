#include <stdio.h>
#include <stdlib.h>
#include "names.sorted.h"

int
main (){
  int i, j;
  long sub, tot = 0;
  for (i=0; i<COUNT; i++) {
    sub = 0;
    for(j=0;names[i][j];j++)
         sub += names[i][j]-'A'+1;

    tot += (i+1)*sub;
  }

  printf("Solution is %ld\n", tot);
  exit (0);
}

