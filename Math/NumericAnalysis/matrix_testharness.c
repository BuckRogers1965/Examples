
#include <stdio.h>
#include "matrix.h"

void
main ()
{

  matrix *m = NewMatrix (5, 5);
  printMatrix (m);
  SetMatrix (m, 3, 3, 5.23);
  SetMatrix (m, 2, 1, .23);
  SetMatrix (m, 1, 2, 7.23);
  SetMatrix (m, 4, 3, 2.23);
  printf ("%0.8Lf\n", GetMatrix (m, 3, 3));
  printf ("%0.8Lf\n", GetMatrix (m, 2, 1));
  SetMatrix (m, 1, 1, 9999);
  printf ("%0.8Lf\n", GetMatrix (m, 1, 1));
  printMatrix (m);

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

  LoadMatrix (m, a);
  matrix *i = findInverse (m);

  printMatrix (m);
  printMatrix (i);

  printf ("inverse * m = Identity *** *** ***\n");
  matrix * v = MultMatrix(m,i);
  printMatrix (i);
  printMatrix (m);
  printMatrix (v);

  
  printf ("Identity * m = m*** *** ***\n");
  matrix *z = createIdentity (5);
  SetMatrix (z, 1, 5, 5);
  printMatrix (z);
  printMatrix (m);

  DisposeMatrix(v);
  v = MultMatrix(z,m);
  printMatrix (v);

  
  printf ("Add:  A+A = 2A *** *** ***\n");
  matrix *add = AddMatrix (m,m);
  printMatrix (add);

  
  printf ("scalar mult:  A+A = 2A *** *** ***\n");
  matrix *sca = ScalarMult (m,3);
  printMatrix (sca);
  
}
