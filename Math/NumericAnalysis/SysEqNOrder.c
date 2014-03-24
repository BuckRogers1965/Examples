#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXORDER 100

typedef long double (*syseqf) (long double, long double *);
typedef struct syseq syseq;
struct syseq
{
  long double start;
  long double end;
  long double range;
  long double step;
  long double max;
  long double h;
  char * title;

  
  int dirty;
  int ordercount;
  long double u[MAXORDER];
  syseqf f[MAXORDER];
  long double **w;
  
} mysyseq;

// internal function
int
isyseq (syseq * s)
{
  int i, j, m;
  long double t = s->start;
  long double u[s->ordercount+1];

  long double k[4][s->ordercount+1];

  for (j=0; j<s->ordercount; j++)
    s->w[j][0] = s->u[j];

  for (i = 0; i <= s->max; i++)
    {
      for (j=0; j<s->ordercount; j++) {
        for (m=0; m<s->ordercount; m++) {
            u[m] = s->w[m][i];
          }
        k[0][j] = s->h * s->f[j] (t, u);
      }

      for (j=0; j<s->ordercount; j++) {
        for (m=0; m<s->ordercount; m++) {
            u[m] = s->w[m][i] + 0.5 * k[0][m];
          }
        k[1][j] = s->h * s->f[j] (t + s->h / 2.0, u);
      }

      for (j=0; j<s->ordercount; j++) {
        for (m=0; m<s->ordercount; m++) {
            u[m] = s->w[m][i] + 0.5 * k[1][m];
          }
        k[2][j] = s->h * s->f[j] (t + s->h / 2.0, u);
      }

      t += s->h;
      for (j=0; j<s->ordercount; j++) {
        for (m=0; m<s->ordercount; m++) {
            u[m] = s->w[m][i] + k[2][m];
          }
        k[3][j] = s->h * s->f[j] (t, u);
      }

      for (j=0; j<s->ordercount; j++)
        s->w[j][i + 1] = s->w[j][i] + 1.0 / 6.0 * (k[0][j] + 2 * k[1][j] + 2 * k[2][j] + k[3][j]);
    }

  return 1;
}

syseq *
syseq_New (long double start, long double end,
		long double step, char * title)
{
  syseq *s = calloc (sizeof (mysyseq), 1);
  if (s == NULL)
    return NULL;
  s->start = start;
  s->end   = end;
  s->range = fabsl (end - start);
  s->step  = step;
  s->max   = s->range * step;
  s->h     = s->range / s->max;
  s->title = title;
  s->dirty = 1;
  s->ordercount = 0;
  s->w = NULL;
  return s;
}

void
freemem(syseq * s)
{
  if (s == NULL)
    return ;

  if (s->w == NULL)
    return;

  int i;
  for (i=1; i<s->max; i++)
    free (s->w[i]);
  free (s->w);
  s->w = NULL;
}

int 
syseq_AddOrder (syseq * s, long double u, syseqf f)
{
  if (s == NULL)
    return 0;

  if (!s->dirty) 
	freemem(s);

  if (s->ordercount > MAXORDER)
	return 0;

  s->dirty = 1;
  s->u[s->ordercount] = u;
  s->f[s->ordercount] = f;
  s->ordercount++;
  return 1;
}

syseq *
syseq_Dispose (syseq * s)
{
  if (s == NULL)
    return;
  freemem(s);
  free (s);
  s = NULL;
  return NULL;
}

int
syseq_Calculate(syseq * s)
{
  if (s == NULL)
    return;
  // need at least one order to perform calculations
  if (s->ordercount < 1)
    return 0;
  // if we have already calculated the results return good
  if (!s->dirty)
    return 1;

  //allocate memory
  int i;
  s->w = calloc (sizeof (long double), s->ordercount + 4);
  if (s->w == NULL)
    return 0;

  for (i=0; i<s->ordercount + 1; i++)
    s->w[i] = calloc (sizeof (long double), s->max +2);

  // perform calculation
  if (isyseq (s)) {
    s->dirty = 0;
    return 1;
  }
  
  freemem(s);
  return 0;
}

long double syseq_GetOrderCount (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->ordercount;
}

long double syseq_GetU (syseq * s, int ordercount)
{
  if (s == NULL)
    return NAN;

  if (ordercount < 0 || ordercount > s->ordercount)
    return NAN;

  return s->u[ordercount];
}

long double syseq_GetStart (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->start;
}

long double syseq_GetEnd (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->end;
}

long double syseq_GetRange (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->range;
}

long double syseq_GetStep (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->step;
}

long double syseq_GetMax (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->max;
}

long double syseq_GetT (syseq * s, int i)
{
  if (s == NULL)
    return NAN;
  if (i < 0 || i > s->max)
    return NAN;
    
  return s->start + i*s->h;
}

long double syseq_GetH (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->h;
}

long double syseq_GetW (syseq * s, int j, int i)
{
  if (s == NULL)
    return NAN;
  if (s->dirty)
	return NAN;

  if (i < 0 || i > s->max)
    return NAN;
  if (j < 1 || i > 2)
    return NAN;
  
  return s->w[j][i];
}

void syseq_Print (syseq * s) {
  int i,j;
  if (s == NULL)
    return;
  if (s->dirty)
	return;

  printf("%s\n\n", s->title);
  for (i = 0; i <= s->max; i++) {
    printf ("%0.4Lf  ", s->start + s->h * i);
    for (j = 0; j < s->ordercount; j++)
      printf ("%0.10Lf  ", s->w[j][i]);
    printf("\n");
  }
  printf("\n");
}

