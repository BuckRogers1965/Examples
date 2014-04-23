#include <stdio.h>
#include "matrix.h"

long double FN (long double x){ return 200 * x; }
long double FE (long double x){ return 200 * x; }
long double FS (long double x){ return 0; }
long double FW (long double x){ return 0; }


int main (){

  matrix *m = NewMatrix (9, 9);
  matrix *v = NewMatrix (9, 1);

  Mat_SetCell (v, 1, 1,  FW(.5 * .75) + FN(.5 * .25));
  Mat_SetCell (m, 1, 1,  4);
  Mat_SetCell (m, 1, 2, -1);
  Mat_SetCell (m, 1, 4, -1);

  Mat_SetCell (v, 2, 1,  FN(.5 * .5));
  Mat_SetCell (m, 2, 2, 4);
  Mat_SetCell (m, 2, 1, -1);
  Mat_SetCell (m, 2, 3, -1);
  Mat_SetCell (m, 2, 5, -1);

  Mat_SetCell (v, 3, 1,  FE(.5 * .75) + FN(.5 * .75));
  Mat_SetCell (m, 3, 3, 4);
  Mat_SetCell (m, 3, 2, -1);
  Mat_SetCell (m, 3, 6, -1);

  Mat_SetCell (v, 4, 1,  FW(.5 * .5) );
  Mat_SetCell (m, 4, 4, 4);
  Mat_SetCell (m, 4, 1, -1);
  Mat_SetCell (m, 4, 5, -1);
  Mat_SetCell (m, 4, 7, -1);

  Mat_SetCell (v, 5, 1, 0);
  Mat_SetCell (m, 5, 5, 4);
  Mat_SetCell (m, 5, 2, -1);
  Mat_SetCell (m, 5, 4, -1);
  Mat_SetCell (m, 5, 6, -1);
  Mat_SetCell (m, 5, 8, -1);

  Mat_SetCell (v, 6, 1, FE(.5 * .5));
  Mat_SetCell (m, 6, 6, 4);
  Mat_SetCell (m, 6, 3, -1);
  Mat_SetCell (m, 6, 5, -1);
  Mat_SetCell (m, 6, 9, -1);

  Mat_SetCell (v, 7, 1, FW(.5 * .25) + FS(.5 * .25));
  Mat_SetCell (m, 7, 7, 4);
  Mat_SetCell (m, 7, 4, -1);
  Mat_SetCell (m, 7, 8, -1);

  Mat_SetCell (v, 8, 1, FS(.5 * .5));
  Mat_SetCell (m, 8, 8, 4);
  Mat_SetCell (m, 8, 7, -1);
  Mat_SetCell (m, 8, 5, -1);
  Mat_SetCell (m, 8, 9, -1);

  Mat_SetCell (v, 9, 1, FE(.5 * .25) + FS(.5 * .75));
  Mat_SetCell (m, 9, 9, 4);
  Mat_SetCell (m, 9, 6, -1);
  Mat_SetCell (m, 9, 8, -1);

  printf("m\n");
  Mat_Print (m);

  printf("v\n");
  Mat_Print (v);  

  matrix *i = Mat_FindInverse (m);

  printf("i\n");
  Mat_Print (i);

  matrix *r = Mat_Mult(i, v);

  printf("r\n");
  Mat_Print (r);  

  Mat_Dispose(m);
  Mat_Dispose(i);
  Mat_Dispose(v);
  return 0;
}

