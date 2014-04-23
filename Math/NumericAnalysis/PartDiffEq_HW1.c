#include <stdio.h>
#include "matrix.h"

long double FN (long double x){ return (x-2.0) * (x-2.0); }
long double FE (long double x){ return (x - 1.0) * (x - 1.0); }
long double FS (long double x){ return x*x; }
long double FW (long double x){ return x*x; }


int main (){

  matrix *m = NewMatrix (3, 3);
  matrix *v = NewMatrix (3, 1);

  Mat_SetCell (v, 1, 1, FW(1.5) + FN(.5) + FE(1.5) - 1 );
  Mat_SetCell (m, 1, 1,  4);
  Mat_SetCell (m, 1, 2, -1);

  Mat_SetCell (v, 2, 1, FW(1.0) + FE(1.0) - 1 );
  Mat_SetCell (m, 2, 2,  4);
  Mat_SetCell (m, 2, 1, -1);
  Mat_SetCell (m, 2, 3, -1);

  Mat_SetCell (v, 3, 1, FW(0.5) + FS(0.5) +  FE(0.5) - 1 );
  Mat_SetCell (m, 3, 3,  4);
  Mat_SetCell (m, 3, 2, -1);


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

  // Calculating backwards to get to the answer.

  matrix * v2 = NewMatrix (3, 1);
  Mat_SetCell (v2, 1, 1,  1.0);
  Mat_SetCell (v2, 2, 1,  0.25);
  Mat_SetCell (v2, 3, 1,  0.0);

  matrix * r2 = Mat_Mult(m, v2);
  printf("r2\n");
  Mat_Print (r2);  
  
  Mat_Dispose(m);
  Mat_Dispose(v);
  Mat_Dispose(v2);
  Mat_Dispose(i);
  Mat_Dispose(r);
  Mat_Dispose(r2);
  
  return 0;
}

