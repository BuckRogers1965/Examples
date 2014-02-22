#include <stdio.h>

// This is for a lattice that is 20x20
// but the paths can go 21 x 21
#define LSIZE 21

void
main (){

  int i, j;
  long long lattic [LSIZE][LSIZE];

  // set the limited paths to 1
  for (i=0; i< LSIZE; i++) {
    lattic [0][i] = 1;
    lattic [i][0] = 1;
  }

  // walk the table, adding up and to the left
  // these are the only directions we can come from
  for (i=1; i< LSIZE; i++)
    for (j=1; j<LSIZE; j++) {
      lattic[i][j] = lattic[i-1][j] + lattic[i][j-1];
    }

/*
  for (i=0; i< LSIZE; i++) {
    for (j=0; j<LSIZE; j++) {
      //lattic[i][j] = lattic[i-1][j] + lattic[i][j-1];
      printf("%lld ", lattic[j][i]);
    }
    printf("\n");
  }
  printf("\n");
*/

  printf("Numer of paths for a size %d matrix is %lld \n", LSIZE-1, lattic[LSIZE-1][LSIZE-1]);
}
