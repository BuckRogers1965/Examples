#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct matrix matrix;
struct matrix
{
  int row;
  int col;
  long double **a;

} myMatrix;

matrix *
NewMatrix (int row, int col)
{
  int i = 0;
  matrix *m = (matrix *) calloc (sizeof (myMatrix), 1);
  if (m == NULL)
    return NULL;
  m->a = calloc (sizeof (long double), row);
  if (m->a == NULL)
    {
      goto fail2;
    }
  for (; i < row; i++)
    {
      m->a[i] = calloc (sizeof (long double), col);
      if (m->a[i] == NULL)
	{
	  for (i--; i > 0; i--)
	    {
	      free (m->a[i]);
	    }
	  goto fail1;
	}
    }
  m->row = row;
  m->col = col;
  return m;

fail1:
  free (m->a);
fail2:
  free (m);
  return NULL;
}

matrix *
Mat_Dispose (matrix * m)
{
  int i = 0;
  if (m == NULL)
    return NULL;
  for (i = m->row - 1; i > 0; i--)
    {
      free (m->a[i]);
    }
  free (m->a);
  free (m);
  return NULL;
}

bool
Mat_SetCell (matrix * m, int row, int col, long double val)
{
  if (m == NULL)
    return false;
  if (row > m->row || row < 1)
    return false;
  if (col > m->col || col < 1)
    return false;
  m->a[row - 1][col - 1] = val;
  return true;
}

long double
Mat_GetCell (matrix * m, int row, int col)
{
  if (m == NULL)
    return NAN;
  if (row > m->row || row < 1)
    return NAN;
  if (col > m->col || col < 1)
    return NAN;
  return m->a[row - 1][col - 1];
}

void
Mat_Load (matrix * m, long double a[])
{
  int r, c;
  for (r = 0; r < m->row; r++)
    {
      for (c = 0; c < m->col; c++)
	{
	  m->a[r][c] = a[r * m->col + c];
	  //printf("<%d  %d>\t", r*m->col , c);
	}
      //printf("\n");
    }
}

void
Mat_Print (matrix * m)
{
  int r, c;
  if (m == NULL)
    {
      printf ("\nprintMatrix: matrix does not exist.\n");
      return;
    }
  printf ("\n");
  for (r = 0; r < m->row; r++)
    {
      for (c = 0; c < m->col; c++)
	printf ("%15.9Lf ", m->a[r][c]);
      printf ("\n");
    }
  printf ("\n");
}

matrix *
Mat_CreateIdentity (int n)
{
  matrix *m = NewMatrix (n, n);
  if (m == NULL)
    return NULL;
  int r = 0, c = 0;

  while (r <= n)
    {
      Mat_SetCell (m, r, c, 1);
      r++;
      c++;
    }
  return m;
}

matrix *
Mat_Dup (matrix * x)
{
  if (x == NULL)
    return NULL;
  matrix *m = NewMatrix (x->row, x->col);
  if (m == NULL)
    return NULL;

  int r, c;
  for (r = 0; r < m->row; r++)
    {
      for (c = 0; c < m->col; c++)
	{
	  m->a[r][c] = x->a[r][c];
	}
    }
  return m;
}

// x * A = b
matrix *
Mat_ScalarMult (matrix * A, long double x)
{
  if (A == NULL)
    return NULL;

  matrix *b = NewMatrix (A->row, A->col);
  if (b == NULL)
    return NULL;

  int r, c;
  for (r = 0; r < b->row; r++)
    for (c = 0; c < b->col; c++)
      b->a[r][c] = A->a[r][c] * x;

  return b;
}

// Av=b
matrix *
Mat_Add (matrix * A, matrix * v)
{
  if (A == NULL || v == NULL)
    return NULL;

  if ((A->col != v->col) && (A->row != v->row))
    return NULL;

  matrix *b = NewMatrix (A->row, v->col);
  if (b == NULL)
    return NULL;

  int r, c;
  for (r = 0; r < b->row; r++)
    for (c = 0; c < b->col; c++)
      b->a[r][c] = A->a[r][c] + v->a[r][c];

  return b;
}

// internal only
long double
RxC (matrix * A, int row, matrix * v, int col)
{
  long double results = 0.0;
  int b;

  // skip tests, already done.
  for (b = 0; b < A->col; b++)
    results += A->a[row][b] * v->a[b][col];
  return results;
}

// Av=b
matrix *
Mat_Mult (matrix * A, matrix * v)
{
  if (A == NULL || v == NULL)
    return NULL;

  if (A->col != v->row)
    return NULL;

  matrix *b = NewMatrix (A->row, v->col);
  if (b == NULL)
    return NULL;

  int r, c;
  for (r = 0; r < b->row; r++)
    for (c = 0; c < b->col; c++)
      b->a[r][c] = RxC (A, r, v, c);
  return b;
}

void
Mat_MultAddRow (matrix * m, int row, long double x, int row1)
{
  if (m == NULL)
    return;
  if (row > m->row || row < 1)
    return;
  if (row1 > m->row || row1 < 1)
    return;

  int c;
  for (c = 0; c < m->col; c++)
    m->a[row1 - 1][c] += m->a[row - 1][c] * x;
}

void
Mat_MultRow (matrix * m, int row, long double x)
{
  if (m == NULL)
    return;
  if (row > m->row || row < 1)
    return;

  int c;
  for (c = 0; c < m->col; c++)
    m->a[row - 1][c] *= x;
}


//internal
long double
FUD(matrix * x){
  int size = x->row-1;
  int offset=0;
  int r=size, c, os;
  long double d1=1;
  long double d=0;
  //printf("\nFUD\n");
  for (os=0; os<=size; os++ ){
      for (c=os; c <= (size+os); c++, r--){
          d1 *= x->a[r][c>size?c-(size+1):c];
          //printf("r %d c %d x %0.0Lf\td %0.0Lf\td1 %0.0Lf \n",
            //r, c>size?c-(size+1):c, x->a[r][c>size?c-(size+1):c], d, d1);
      }
    d += d1;
    d1=1;
    r=size;
  }
  //printf("***r %d c %d x %0.0Lf\td %0.0Lf\td1 %0.0Lf \n",
            //r, c>size?c-(size+1):c, x->a[r][c>size?c-(size+1):c], d, d1);
    
  return d;
}

//internal
long double
FDD(matrix * x){
  int size = x->row-1;
  int offset=0;
  int r=0, c, os;
  long double d1=1;
  long double d=0;
  //printf("\nFDD\n");
  for (os=0; os<=size; os++){
      for (c=os; c<=(size+os); c++, r++){
          d1 *= x->a[r][c>size?c-(size+1):c];
          //printf("r %d c %d x %0.0Lf\td %0.0Lf\td1 %0.0Lf \n",
            //r, c>size?c-(size+1):c, x->a[r][c>size?c-(size+1):c], d, d1);
      }
    d += d1;
    d1=1;
    r=0;
  }
    
//  printf("***r %d c %d x %0.0Lf\td %0.0Lf\td1 %0.0Lf \n",
//            r, c>size?c-(size+1):c, x->a[r][c>size?c-(size+1):c], d, d1);
  return d;
}

long double 
Mat_Determinate (matrix * x){
  if (x == NULL)
    return 0;
  if (x->row != x->col)
    return 0; 
  // a b  ad - cb
  // c d
  if (x->row == 2) {
    //printf("%0.0Lf * %0.0Lf - %0.0Lf * %0.0Lf\n", x->a[0][0], x->a[1][1], x->a[1][0], x->a[0][1]);
    return x->a[0][0]*x->a[1][1] - x->a[1][0]*x->a[0][1]; 
  }
  int size = x->row - 1;
  return FDD(x) - FUD(x);
}

matrix *
Mat_FindInverse (matrix * x)
{
  int r, r1;
  long double mult;

  if (x == NULL)
    return NULL;
  // no det = no inverse
  if (Mat_Determinate(x) == 0)
    return NULL;
  int s = x->row;

  matrix *m = Mat_Dup (x);
  if (m == NULL)
    return NULL;

  matrix *z = Mat_CreateIdentity (m->row);
  if (z == NULL)
    goto fail;

  //printf("*****\n");

  // force a pivot on each row and column
  for (r = 1; r <= s; r++)
    {
      mult = 1 / Mat_GetCell (m, r, r);
      //printf("%0.3Lf  %0.3Lf\n", GetMatrix(m, r, r), mult);
      Mat_MultRow (m, r, mult);
      Mat_MultRow (z, r, mult);
      for (r1 = r + 1; r1 <= s; r1++)
	{
	  mult = -Mat_GetCell (m, r1, r);
	  //printf("%0.3Lf\t", mult);
	  Mat_MultAddRow (m, r, mult, r1);
	  Mat_MultAddRow (z, r, mult, r1);
	}
    }

  // solve from bottom to top
  for (r = s; r > 0; r--)
    {
      for (r1 = r - 1; r1 > 0; r1--)
	{
	  mult = -Mat_GetCell (m, r1, r);
	  //printf("* %0.3Lf\t", mult);
	  Mat_MultAddRow (m, r, mult, r1);
	  Mat_MultAddRow (z, r, mult, r1);
	}
    }

  Mat_Dispose (m);
  return z;

fail:
  Mat_Dispose (m);
  return NULL;
}
