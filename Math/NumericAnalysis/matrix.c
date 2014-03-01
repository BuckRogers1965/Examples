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
DisposeMatrix (matrix * m)
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
SetMatrix (matrix * m, int row, int col, long double val)
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
GetMatrix (matrix * m, int row, int col)
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
LoadMatrix (matrix * m, long double a[])
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
PrintMatrix (matrix * m)
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
CreateIdentity (int n)
{
  matrix *m = NewMatrix (n, n);
  if (m == NULL)
    return NULL;
  int r = 0, c = 0;

  while (r <= n)
    {
      SetMatrix (m, r, c, 1);
      r++;
      c++;
    }
  return m;
}

matrix *
DupMatrix (matrix * x)
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
ScalarMult (matrix * A, long double x)
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
AddMatrix (matrix * A, matrix * v)
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
MultMatrix (matrix * A, matrix * v)
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
MultAddRow (matrix * m, int row, long double x, int row1)
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
MultRow (matrix * m, int row, long double x)
{
  if (m == NULL)
    return;
  if (row > m->row || row < 1)
    return;

  int c;
  for (c = 0; c < m->col; c++)
    m->a[row - 1][c] *= x;
}

matrix *
FindInverse (matrix * x)
{
  int r, r1;
  long double mult;

  if (x == NULL)
    return NULL;
  if (x->row != x->col)
    return NULL;
  int s = x->row;

  matrix *m = DupMatrix (x);
  if (m == NULL)
    return NULL;

  matrix *z = CreateIdentity (m->row);
  if (z == NULL)
    goto fail;

  //printf("*****\n");

  // force a pivot on each row and column
  for (r = 1; r <= s; r++)
    {
      mult = 1 / GetMatrix (m, r, r);
      //printf("%0.3Lf  %0.3Lf\n", GetMatrix(m, r, r), mult);
      MultRow (m, r, mult);
      MultRow (z, r, mult);
      for (r1 = r + 1; r1 <= s; r1++)
	{
	  mult = -GetMatrix (m, r1, r);
	  //printf("%0.3Lf\t", mult);
	  MultAddRow (m, r, mult, r1);
	  MultAddRow (z, r, mult, r1);
	}
    }

  // solve from bottom to top
  for (r = s; r > 0; r--)
    {
      for (r1 = r - 1; r1 > 0; r1--)
	{
	  mult = -GetMatrix (m, r1, r);
	  //printf("* %0.3Lf\t", mult);
	  MultAddRow (m, r, mult, r1);
	  MultAddRow (z, r, mult, r1);
	}
    }

  free (m);
  return z;

fail:
  DisposeMatrix (m);
  return NULL;
}
