#include <stdbool.h>

typedef void * matrix;

matrix * NewMatrix (int row, int col);

matrix * DisposeMatrix (matrix * m);

bool SetMatrix (matrix * m, int row, int col, long double val);

long double GetMatrix (matrix * m, int row, int col);

void LoadMatrix (matrix * m, long double a[]);

void printMatrix (matrix * m);

matrix * createIdentity (int n);

matrix * dupMatrix (matrix * x);

matrix * ScalarMult (matrix * A, long double x);

matrix * AddMatrix (matrix * A, matrix * v);

matrix * MultMatrix (matrix * A, matrix * v);

void MultAddRow(matrix * m, int row, long double x, int row1);

void MultRow(matrix * m, int row, long double x);

matrix * findInverse (matrix * x);

