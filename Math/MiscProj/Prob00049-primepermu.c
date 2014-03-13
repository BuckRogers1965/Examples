#include <stdio.h>
#include <stdlib.h>
#include "primes/p4.h"

int 
permu (int x, int y){
  char sx[100];
  char sy[100];

  int i, j, match = 0;

  sprintf(sx, "%d\0", x);
  sprintf(sy, "%d\0", y);
  //printf ("Matching %s and %s", sx, sy);
  for (i=0; sx[i]; i++)
    for (j=0; sy[j]; j++)
      if (sx[i] == sy[j]) {
        //printf("%c %c\n", sx[i], sy[j]);
        match++;
        sy[j] = ' ';
        break;
      }
   
  if (match == 4)
    return 1;
  return 0;
}

int 
main () {

  int i, j;
  for (i=0; i<MAX; i++)
    for (j=i; j<MAX; j++)
      if ( n[j]-n[i] == 3330  && permu(n[i], n[j]))
         printf("%d -> %d \n", n[i], n[j]);
  exit (0);
}
