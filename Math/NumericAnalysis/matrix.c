#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct matrix matrix;
struct matrix
{
  int row;
  int col;
  long double **a;

} myMatrix;

matrix * 
NewMatrix (int row, int col) {
  int i=0;
  matrix * m = (matrix *) calloc (sizeof(myMatrix), 1);
  if (m == NULL) return NULL;
  m->a =  calloc (sizeof(long double), row);
  if (m->a == NULL){
    free(m);
    return NULL;
  }
  for(;i<row;i++) {
    m->a[i] =  calloc (sizeof(long double), col);
    if (m->a[i] == NULL) {
      for(i--;i>0;i--) {
        free(m->a[i]);
      }
      free (m);
      return NULL;
    }
  }
  m->row = row;
  m->col = col;
  return m;
}

bool
SetMatrix (matrix * m, int row, int col, long double val){
  if (m == NULL) return false;
  if(row>m->row || row<1) return false;
  if(col>m->col || col<1) return false;
  m->a[row-1][col-1] = val;
  return true;
}

#define NAN 1.0/0.0
long double
GetMatrix (matrix * m, int row, int col){
  if (m == NULL) return NAN;
  if(row>m->row || row<1) return NAN;
  if(col>m->col || col<1) return NAN;
  return m->a[row-1][col-1];
}

void
LoadMatrix (matrix * m, long double a[]){
  int r,c;
  for (r=0;r<m->row;r++) {
    for (c=0;c<m->col;c++){
        m->a[r][c]=a[r*m->col + c];
        //printf("<%d  %d>\t", r*m->col , c);
    }
  //printf("\n");
  }
}

void
printMatrix (matrix * m){
  int r,c;
  printf("\n");
  for (r=0;r<m->row;r++) {
    for (c=0;c<m->col;c++)
      printf("%10.5Lf ", m->a[r][c]);
    printf("\n");
  }
  printf("\n");
}

void
main (){

  matrix * m = NewMatrix (4,5);
  printMatrix(m);
  SetMatrix(m, 3,3, 5.23);
  SetMatrix(m, 2,1, .23);
  SetMatrix(m, 1,2, 7.23);
  SetMatrix(m, 4,3, 2.23);
  printf("%0.8Lf\n", GetMatrix(m, 3,3));
  printf("%0.8Lf\n", GetMatrix(m, 2,1));
  SetMatrix(m, 1,1, 9999);
  printf("%0.8Lf\n", GetMatrix(m, 1,1));
  printMatrix(m);

  long double a[]= {
      1.0,   2.0,  3.0,  4.0,  5.0,
      6.0,   7.0,  8.0,  9.0, 10.0,
      11.0, 12.0, 13.0, 14.0, 15.0,
      16.0, 17.0, 18.0, 19.0, 20.0 };

  LoadMatrix(m, a);
  printf("%0.8Lf\n", GetMatrix(m, 1,1));
  printMatrix(m);
}



