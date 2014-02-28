#include <stdio.h>
#include "matrix.h"
#define SIZE 80

int minh = 0;
int maxh = 0;

// rising water lifts all boats and
// floods the lowest path

void
main (){

  int i, j, k, l, m, x, y, cur;
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


// convert to a triangular

    for (k=0; k<160; k++){
       for (i=0; i<=k; i++){
         printf("{%d, %d} ", k-i, i);
       }
       printf("\n");
    }
        

/*
  0,0
  1,0, 0,1, 
  2,0, 1,1, 0,2 
  3,0  2,1, 1,2, 0,3


*/

    for (k=0; k<159; k++){
       for (i=0; i<=k; i++){
         x = k-i;
         y = i;
         if (x>=80 || y>= 80)
           printf("9999, ");
         else
           printf("%d, ", mat[x][y]);
         //printf("{%d, %d} ", k-i, i);
       }
       printf("\n");
    }
        
}
