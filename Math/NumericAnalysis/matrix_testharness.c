
#include <stdio.h>
#include "matrix.h"

void
main ()
{

  matrix *m = NewMatrix (5, 5);
  Mat_Print (m);
  Mat_SetCell (m, 3, 3, 5.23);
  Mat_SetCell (m, 2, 1, .23);
  Mat_SetCell (m, 1, 2, 7.23);
  Mat_SetCell (m, 4, 3, 2.23);
  printf ("%0.8Lf\n", Mat_GetCell (m, 3, 3));
  printf ("%0.8Lf\n", Mat_GetCell (m, 2, 1));
  Mat_SetCell (m, 1, 1, 9999);
  printf ("%0.8Lf\n", Mat_GetCell (m, 1, 1));
  Mat_Print (m);

  long double ab[] = {
    1.0, 2.0, 3.0, 4.0, 5.0,
    6.5, 7.2, 8.5, 9.0, 10.0,
    6.3, 7.4, 8.7, 9.0, 10.0,
    11.0, 12.0, 13.9, 14.0, 15.0,
    16.0, 17.0, 18.8, 1.0, 2.0
  };

  long double a[] = {
    1.000, 2.000, 3.000, 10.000, 11.000,
    4.000, 5.000, 11.000, 12.000, 13.000,
    7.000, 8.000, 9.000, 12.000, 34.000,
    1.000, 1.000, 1.000, 1.000, 1.000,
    12.593, 37.000, 17.00, 3.333, 15.23
  };

  Mat_Load (m, a);
  matrix *i = Mat_FindInverse (m);

  Mat_Print (m);
  Mat_Print (i);

  printf ("inverse * m = Identity *** *** ***\n");
  matrix * v = Mat_Mult(m,i);
  Mat_Print (i);
  Mat_Print (m);
  Mat_Print (v);

  
  printf ("Identity * m = m*** *** ***\n");
  matrix *z = Mat_CreateIdentity (5);
  Mat_SetCell (z, 1, 5, 5);
  Mat_Print (z);
  Mat_Print (m);

  Mat_Dispose(v);
  v = Mat_Mult(z,m);
  Mat_Print (v);

  
  printf ("Add:  A+A = 2A *** *** ***\n");
  matrix *add = Mat_Add (m,m);
  Mat_Print (add);

  
  printf ("scalar mult:  A+A+A = 3A *** *** ***\n");
  matrix *sca = Mat_ScalarMult (m,3);
  Mat_Print (sca);

  matrix * two = NewMatrix(2,2);
  Mat_SetCell (two, 1, 1, 1);
  Mat_SetCell (two, 1, 2, 2);
  Mat_SetCell (two, 2, 1, 3);
  Mat_SetCell (two, 2, 2, 4);
  Mat_Print (two);
  printf ("Determinate is: %0.6Lf\n", Mat_Determinate(two));

  matrix * three = NewMatrix(3,3);
  Mat_SetCell (three, 1, 1, 1);
  Mat_SetCell (three, 1, 2, 5);
  Mat_SetCell (three, 1, 3, 0);
  Mat_SetCell (three, 2, 1, 2);
  Mat_SetCell (three, 2, 2, 4);
  Mat_SetCell (three, 2, 3, -1);
  Mat_SetCell (three, 3, 1, 0);
  Mat_SetCell (three, 3, 2, -2);
  Mat_SetCell (three, 3, 3, 0);
  Mat_Print (three);
  printf ("Determinate is: %0.6Lf\n", Mat_Determinate(three));
  
  Mat_SetCell (three, 1, 1, 1);
  Mat_SetCell (three, 1, 2, 2);
  Mat_SetCell (three, 1, 3, 3);
  Mat_SetCell (three, 2, 1, 1);
  Mat_SetCell (three, 2, 2, 2);
  Mat_SetCell (three, 2, 3, 3);
  Mat_SetCell (three, 3, 1, 11);
  Mat_SetCell (three, 3, 2, 21);
  Mat_SetCell (three, 3, 3, 31);
  Mat_Print (three);
  printf ("Determinate  with repeating rows is: %0.6Lf\n", Mat_Determinate(three));
  
  Mat_SetCell (three, 1, 1, 1);
  Mat_SetCell (three, 1, 2, 2);
  Mat_SetCell (three, 1, 3, 11);
  Mat_SetCell (three, 2, 1, 2);
  Mat_SetCell (three, 2, 2, 4);
  Mat_SetCell (three, 2, 3, 21);
  Mat_SetCell (three, 3, 1, 3);
  Mat_SetCell (three, 3, 2, 6);
  Mat_SetCell (three, 3, 3, 31);
  Mat_Print (three);
  printf ("Determinate  with repeating cols is: %0.6Lf\n", Mat_Determinate(three));

  matrix * five = NewMatrix(5,5);
  Mat_SetCell (five, 1, 1, 1);
  Mat_SetCell (five, 1, 2, 2);
  Mat_SetCell (five, 1, 3, 5);
  Mat_SetCell (five, 1, 4, 0);
  Mat_SetCell (five, 1, 5, 1);

  Mat_SetCell (five, 2, 1, 2);
  Mat_SetCell (five, 2, 2, 3);
  Mat_SetCell (five, 2, 3, 7);
  Mat_SetCell (five, 2, 4, 1);
  Mat_SetCell (five, 2, 5, 9);

  Mat_SetCell (five, 3, 1, 1);
  Mat_SetCell (five, 3, 2, 2);
  Mat_SetCell (five, 3, 3, 3);
  Mat_SetCell (five, 3, 4, 0);
  Mat_SetCell (five, 3, 5, 3);

  Mat_SetCell (five, 4, 1, 0);
  Mat_SetCell (five, 4, 2, 0);
  Mat_SetCell (five, 4, 3, 1);
  Mat_SetCell (five, 4, 4, 0);
  Mat_SetCell (five, 4, 5, 0);

  Mat_SetCell (five, 5, 1, 3);
  Mat_SetCell (five, 5, 2, 2);
  Mat_SetCell (five, 5, 3, -4);
  Mat_SetCell (five, 5, 4, 0);
  Mat_SetCell (five, 5, 5, 1);
  Mat_Print (five);
  printf ("Determinate  with repeating cols is: %0.6Lf\n", Mat_Determinate(five));


  Mat_SetCell (five, 1, 1, 7);
  Mat_SetCell (five, 1, 2, 2);
  Mat_SetCell (five, 1, 3, -8);
  Mat_SetCell (five, 1, 4, 4);
  Mat_SetCell (five, 1, 5, 6);

  Mat_SetCell (five, 2, 1, -3);
  Mat_SetCell (five, 2, 2, -1);
  Mat_SetCell (five, 2, 3,  4);
  Mat_SetCell (five, 2, 4, -2);
  Mat_SetCell (five, 2, 5, -3);

  Mat_SetCell (five, 3, 1, 6);
  Mat_SetCell (five, 3, 2, 2);
  Mat_SetCell (five, 3, 3, 2);
  Mat_SetCell (five, 3, 4, 4);
  Mat_SetCell (five, 3, 5, 7);

  Mat_SetCell (five, 4, 1, 1);
  Mat_SetCell (five, 4, 2, 3);
  Mat_SetCell (five, 4, 3, 7);
  Mat_SetCell (five, 4, 4, 5);
  Mat_SetCell (five, 4, 5, 1);

  Mat_SetCell (five, 5, 1, -2);
  Mat_SetCell (five, 5, 2, 2);
  Mat_SetCell (five, 5, 3, 3);
  Mat_SetCell (five, 5, 4, 4);
  Mat_SetCell (five, 5, 5, 7);
  Mat_Print (five);
  printf ("Determinate  with repeating cols is: %0.6Lf\n", Mat_Determinate(five));

}
