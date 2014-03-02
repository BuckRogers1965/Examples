#include <stdbool.h>

typedef void *matrix;

matrix *NewMatrix (int row, int col);

matrix *Mat_Dispose (matrix * m);

bool Mat_SetCell (matrix * m, int row, int col, long double val);

long double Mat_GetCell (matrix * m, int row, int col);

void Mat_Load (matrix * m, long double a[]);

void Mat_Print (matrix * m);

matrix *Mat_CreateIdentity (int n);

matrix *Mat_Dup (matrix * x);

matrix *Mat_ScalarMult (matrix * A, long double x);

matrix *Mat_Add (matrix * A, matrix * v);

matrix *Mat_Mult (matrix * A, matrix * v);

void Mat_MultAddRow (matrix * m, int row, long double x, int row1);

void Mat_MultRow (matrix * m, int row, long double x);

long double Mat_Determinate (matrix * x);

matrix *Mat_FindInverse (matrix * x);
