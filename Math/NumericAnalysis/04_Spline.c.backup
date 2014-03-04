#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "matrix.h"

/* James M. Rogers
   01 March 2014
*/

typedef struct Point Point;
struct Point
{

  long double x;
  long double a;
  long double h;
  long double b;
  long double c;
  long double d;
  

} myPoint;

void
PrintPoints (int count, Point Points[])
{

  int n = 0;

  printf ("\t");
  for (n = 0; n < count; n++)
    printf ("%4.4Lf\t", Points[n].x);
  printf ("\n");

  printf ("\t");
  for (n = 0; n < count; n++)
    printf ("%4.4Lf\t", Points[n].a);
  printf ("\n");

}

long double
Find (int n, Point Points[], long double x)
{

}

void
main ()
{

  int n = 6;
  Point P[100];
  int i, j;

  // Define the x and y points
  // y points are called a for this interpolation

  P[0].x =  1.0;
  P[1].x =  3.0;
  P[2].x =  5.0;
  P[3].x =  7.0;
  P[4].x =  8.0;
  P[5].x = 10.0;

  P[0].a =  6.0;
  P[1].a =  2.0;
  P[2].a =  5.0;
  P[3].a = 10.0;
  P[4].a =  4.0;
  P[5].a =  1.0;

  printf("h:          ");
  //calculate h for n-1 intervals
  for (i=0;i<(n-1);i++) {
    P[i].h = P[i+1].x - P[i].x;
    printf("%4.4Lf  ", P[i].h);
  }
  printf("\n");
  printf("x,a:");
  PrintPoints(n, P);

  // define the size of the matrix and create it.
  // size is n+1 points, and is square

  matrix * A = NewMatrix (n, n);
  SetMatrix(A,   1,   1, 1);
  SetMatrix(A, n, n, 1);
  for (i=2;i<n;i++) {
    SetMatrix(A, i, i-1, P[i-2].h);
    SetMatrix(A, i,   i, 2 * (P[i-2].h + P[i-1].h));
    SetMatrix(A, i, i+1, P[i-1].h);
  }

  printf("A = ");
  PrintMatrix(A);
   
  matrix * b = NewMatrix (n, 1);
  for (i=2;i<n;i++) {
    SetMatrix(b, i, 1, (3/P[i-1].h) * (P[i].a - P[i-1].a) - (3/P[i-2].h) * (P[i-1].a - P[i-2].a));
  }

  printf("b_vector = ");
  PrintMatrix(b);


  matrix *Ai = FindInverse (A);
  printf("A^-1 = ");
  PrintMatrix (Ai);

  matrix * c = MultMatrix(Ai, b);
  printf("A^-1 * b_vector = c = ");
  PrintMatrix (c);
  // copy to the Points collection
  for (i=0;i<n-1;i++) { 
    P[i].c= GetMatrix(c, i+1, 1);
  }

  
  printf("b = ");
  for (j=0;j<n-1;j++) {
    P[j].b = 1/P[j].h * (P[j+1].a - P[j].a) - P[j].h/3 * (2* P[j].c + P[j+1].c);
    printf("%4.4Lf  ", P[j].b);
  }
  printf("\n");

  
  printf("d = ");
  for (j=0;j<n-1;j++) {
    P[j].d = (1 / (3 * P[j].h)) *  (P[j+1].c - P[j].c);
    printf("%4.4Lf  ", P[j].d);
  }
  printf("\n");

  
  
}
