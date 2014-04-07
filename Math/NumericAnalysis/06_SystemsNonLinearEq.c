#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* James M. Rogers
   03 April 2014

    to build 
	gcc -04 matrix.c 06_SystemsNonLinearEq.c \
               06_SystemsNonLinearEq_HW.c -o sysnleq

    where the last .c file has a main function
*/

#define MAXORDER 100

typedef long double (*syseqf) (long double [MAXORDER]);
typedef struct SystemNL SystemNL;
struct SystemNL
{
  int OrderSize;
  syseqf **J;
  syseqf f[MAXORDER];
  long double initial[MAXORDER];
  char * title;
  int SD;
  int NI;
} mySystem;

SystemNL *
System_New (int OrderSize, char * title)
{
  if (OrderSize > MAXORDER || OrderSize < 1)
    return NULL;
  SystemNL *s = calloc (sizeof (mySystem), 1);
  if (s == NULL)
    return NULL;
  s->OrderSize = OrderSize;
  s->J = calloc (sizeof (syseqf), s->OrderSize);
  if (s->J == NULL)
    goto fail1;

  s->title = title;
  s->SD = 10;
  s->NI = 10;

  int i=0;
  for (; i < OrderSize; i++)
    {
      s->J[i] = calloc (sizeof (syseqf), s->OrderSize);
      if (s->J[i] == NULL)
	{
	  for (i--; i > 0; i--)
	    {
	      free (s->J[i]);
	    }
	  goto fail2;
	}
    }

  return s;

fail2:
  free (s->J);

fail1:
  free (s);
  return NULL;
}

SystemNL *
System_Dispose (SystemNL * s, long double x)
{
  int i;
  if (s == NULL)
    return NULL;
  for (i = s->OrderSize - 1; i > 0; i--)
    {
      free (s->J[i]);
    }
  free (s->J);
  free (s);
  return NULL;
}

void
System_SetNI (SystemNL * s, int NI)
{
  if (s == NULL)
    return;
  s->NI = NI;
}

void
System_SetSD (SystemNL * s, int SD)
{
  if (s == NULL)
    return;
  s->SD = SD;
}

bool
System_AddFunc (SystemNL * s, int index, long double initial, syseqf f)
{
  if (s == NULL)
    return false;
  if (index > s->OrderSize || index < 1)
    return false;

  s->f[index - 1] = f;
  s->initial[index - 1] = initial;

  return true;
}

bool
System_AddJacobian (SystemNL * s, int a, int b, syseqf f)
{
  if (s == NULL)
    return false;
  if (a > s->OrderSize || a < 1)
    return false;
  if (b > s->OrderSize || b < 1)
    return false;

  s->J[a-1][b-1] = f;

  return true;
}

long double
sqrf(SystemNL * s, matrix * z, long double a[], int j){

  long double u[s->OrderSize];
  int i;

  for (i=0; i<s->OrderSize; i++){
    u[i] = s->initial[i] - Mat_GetCell(z, i+1, 1) * a[j];
  }

  long double x = 0;
  long double y;
  for (i=0; i<s->OrderSize; i++) {
    y = s->f[i](u); 
    x += y*y;
  }

  return x;
}

#define QUADPT 3
void
findAlpha(SystemNL * s, matrix * z, long double a[], long double ga[]){

  int i;

  for (i=0; i<QUADPT; i++)
	a[i] = i;

  do {

    for (i=1; i<QUADPT; i++)
      a[i] /= 2.0;

    for (i=0; i<QUADPT; i++) 
      ga[i] = sqrf(s, z, a, i);

  } while ( ga[0] <= ga[QUADPT-1]);
}

void
SteepestDescent (SystemNL * s, matrix * m, matrix * F)
{
  if (s == NULL)
    return;

  // find beginning points using method of steepist descent

  int i, j;
  for (i=0; i<s->OrderSize; i++)
	Mat_SetCell(F, i+1,1, s->f[i](s->initial) );
  //Mat_Print(F);
    
  for (i=0; i<s->OrderSize; i++)
    for (j=0; j<s->OrderSize; j++)
      Mat_SetCell(m, i+1, j+1, s->J[i][j](s->initial));
  //Mat_Print(m);

  matrix *n = Mat_Transpose (m);
  //Mat_Print(n);

  matrix *g = Mat_Mult (n, F);
  //Mat_Print(g);

  matrix *g2 = Mat_ScalarMult(g,2.0);
  //Mat_Print(g2);

  matrix * z = Mat_2Norm(g2);
  //Mat_Print(z);

  Mat_Dispose (n);
  Mat_Dispose (g);
  Mat_Dispose (g2);

  long double  a[QUADPT];
  long double ga[QUADPT];

  findAlpha(s, z, a, ga);

//  for (i=0; i<s->OrderSize; i++) {
//     printf("%d  %Lf  %Lf  %Lf\n", i+1, Mat_GetCell(z, i+1, 1), a[i], ga[i]);
//  }

  long double h[s->OrderSize];
  h[0] = (ga[1] - ga[0] ) / (a[1] - a[0]);
  h[1] = (ga[2] - ga[1] ) / (a[2] - a[1]);
  h[2] = ( h[1] -  h[0] ) / (a[2] - a[0]);

 // for (i=0; i<s->OrderSize; i++) 
  //   printf("h%d  %Lf  ", i+1, h[i]);
 // printf("\n");

  //long double P = -(-h[2]*0.5 + h[0] )/ (2.0*h[2]);
  long double P = -(-h[2]*a[1] + h[0] )/ (2.0*h[2]);

//  printf("P is %Lf \\ %Lf  = %Lf\n", (-h[2]*a[1] + h[0] ), 2.0*h[2], P);

  for (i=0; i<s->OrderSize; i++) 
    s->initial[i] -= P * Mat_GetCell(z, i+1, 1);

  for (i=0; i<s->OrderSize; i++) 
    printf("%14.10Lf  ", s->initial[i] );
  printf("\n");

  Mat_Dispose (z);
  return;
}

void
NewtonsMethod (SystemNL * s, matrix * m, matrix * F)
{
  if (s == NULL)
    return;

  int i, j;
  for (i=0; i<s->OrderSize; i++)
	Mat_SetCell(F, i+1,1, s->f[i](s->initial) );
//  Mat_Print(F);

  for (i=0; i<s->OrderSize; i++)
    for (j=0; j<s->OrderSize; j++)
      Mat_SetCell(m, i+1, j+1, s->J[i][j](s->initial));
//  Mat_Print(m);

  matrix * ji = Mat_FindInverse(m);
//  Mat_Print(ji);

  matrix * y = Mat_Mult(ji, F);
//  Mat_Print(y);

  matrix * ny = Mat_ScalarMult(y, -1);
//  Mat_Print(ny);

  for (i=0; i<s->OrderSize; i++) {
     s->initial[i] += Mat_GetCell(ny, i+1, 1); 
     printf ("%14.10Lf  ", s->initial[i]);
  }
  printf("\n");

  Mat_Dispose (ny);
  Mat_Dispose (y);
  Mat_Dispose (ji);

  return;
}

void
System_Solve (SystemNL * s)
{
  if (s == NULL)
    return;

  int i, x=s->SD;
  // double check to see if we are lacking any Jacobain entries

  printf ("Solving for: %s", s->title);

  matrix *m = NewMatrix (s->OrderSize, s->OrderSize);
  matrix *F = NewMatrix (s->OrderSize, 1);

  printf("\nInitial Values:  \n0  ");
  for (i=0; i<s->OrderSize; i++) 
    printf("%14.10Lf  ", s->initial[i] );
  printf("\n x is %d\n", x);

  printf("\nSteepest Descent:  \n  ");
  for (i=1; i<x; i++)  {
    printf("%d  ", i);
    SteepestDescent(s, m, F);
  }
  if (i==1)
	printf("Skipping.\n");

  printf("\nNewton's Method:  \n");
  for (; i<x+s->NI; i++)  {
    printf("%d  ", i);
    NewtonsMethod(s, m, F);
  }

  Mat_Dispose (m);
  Mat_Dispose (F);

  printf ("\nUltimate solution is:\n");
  for (i=0; i<s->OrderSize; i++) 
    printf ("x(%d) = %24.20Lf\n", i+1, s->initial[i]);
  printf("\n");

  printf ("Testing solution, should be all zeros:\n");
  for (i=0; i<s->OrderSize; i++) 
    printf ("F%d = %24.20Lf\n", i+1, s->f[i](s->initial));
  printf("\n");

  return;
}
