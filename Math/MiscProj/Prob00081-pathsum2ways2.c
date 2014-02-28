#include <stdio.h>
#include "matrix.h"
#define SIZE 80

int minh = 0;
int maxh = 0;

// rising water lifts all boats and
// floods the lowest path

long 
solve(int x, int y, flooding){
}

void
main (){

  int i, j, cur;
  long long total;
   for (i=0; i< SIZE; i++)
     for (j=0; j<SIZE; j++) {
        cur = mat[i][j];
        if (cur > maxh)
          maxh = cur;
        if (cur < minh)
          minh = cur;
        total += cur;
     }
  printf("min %d  max %d tot %ld\n", minh, maxh, (long)total/(80*80) );

   printf( "Solution is %ld \n", solve(0,0,ave/2) );
}
