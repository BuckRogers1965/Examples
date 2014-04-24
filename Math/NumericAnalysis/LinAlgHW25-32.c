
#include <stdio.h>
#include "matrix.h"

void
main ()
{

  printf ("Home Work PRoblem 2\n");
  matrix * hw2 = NewMatrix(3, 3);

  Mat_SetCell (hw2, 1, 1, 2);
  Mat_SetCell (hw2, 1, 2, -6);
  Mat_SetCell (hw2, 1, 3, 4);

  Mat_SetCell (hw2, 2, 1, -4);
  Mat_SetCell (hw2, 2, 2, 8);
  Mat_SetCell (hw2, 2, 3, 0);

  Mat_SetCell (hw2, 3, 1, 0);
  Mat_SetCell (hw2, 3, 2, -4);
  Mat_SetCell (hw2, 3, 3, 6);

  printf ("A=\n");
  Mat_Print (hw2);

  matrix * hw2b = NewMatrix (3, 1);
  Mat_SetCell (hw2b, 1, 1, 2);
  Mat_SetCell (hw2b, 2, 1, -4);
  Mat_SetCell (hw2b, 3, 1, 6);

  printf ("b=\n");
  Mat_Print (hw2b);

  matrix * hw2Ainv = Mat_FindInverse (hw2);
  printf ("Ainv = \n");
  Mat_Print (hw2Ainv);

  matrix * hw2sol = Mat_Mult(hw2Ainv, hw2b);
  printf ("Ainv * b = \n");
  Mat_Print (hw2sol);

  Mat_Dispose(hw2);
  Mat_Dispose(hw2b);
  Mat_Dispose(hw2Ainv);
  Mat_Dispose(hw2sol);

  
  printf ("Home Work PRoblem 4\n");

  matrix * hw4 = NewMatrix(3, 3);

  Mat_SetCell (hw4, 1, 1, 1);
  Mat_SetCell (hw4, 1, 2, -1);
  Mat_SetCell (hw4, 1, 3, 2);

  Mat_SetCell (hw4, 2, 1, 1);
  Mat_SetCell (hw4, 2, 2, -3);
  Mat_SetCell (hw4, 2, 3, 1);

  Mat_SetCell (hw4, 3, 1, 3);
  Mat_SetCell (hw4, 3, 2, 7);
  Mat_SetCell (hw4, 3, 3, 5);

  printf ("A=\n");
  Mat_Print (hw4);

  matrix * hw4b = NewMatrix (3, 1);
  Mat_SetCell (hw4b, 1, 1, 0);
  Mat_SetCell (hw4b, 2, 1, -5);
  Mat_SetCell (hw4b, 3, 1, 7);

  printf ("b=\n");
  Mat_Print (hw4b);

  matrix * hw4Ainv = Mat_FindInverse (hw4);
  printf ("Ainv = \n");
  Mat_Print (hw4Ainv);

  matrix * hw4sol = Mat_Mult(hw4Ainv, hw4b);
  printf ("Ainv * b = \n");
  Mat_Print (hw4sol);

  Mat_Dispose(hw4);
  Mat_Dispose(hw4b);
  Mat_Dispose(hw4Ainv);
  Mat_Dispose(hw4sol);
  
}
