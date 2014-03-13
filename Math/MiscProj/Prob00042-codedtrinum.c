#include <stdio.h>
#include <stdlib.h>
#include "series.c"
#include "words.h"

int
main () {

  int i,j, r, total = 0;

  for (i=0; i<WORDS; i++) {
    r = 0;
    for (j=0; words[i][j]; j++)
      r += words[i][j] - 'A'+1;
    if (isinseries(r, 1))
       total++;
  }

  printf("Solution is %d\n", total);
  exit (0);
}
