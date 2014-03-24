#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double (*syseqf) (long double, long double, long double);
typedef struct syseq syseq;
struct syseq
{
  long double u1;
  long double u2;
  long double start;
  long double end;
  long double range;
  long double step;
  long double max;
  long double h;
  syseqf f1;
  syseqf f2;
  long double **w;
} mysyseq;


#include <math.h>

#define E 2.71828182845904523536

long double
f1a (long double t, long double u1, long double u2)
{
  return u2;
}

long double
f2a (long double t, long double u1, long double u2)
{
  return powl (E, 2*t) * sinl (t) - 2 * (u1) + 2 * u2;
}

// internal function
void
isyseq (syseq * s)
{
  long double k1_1, k1_2, k2_1, k2_2, k3_1, k3_2, k4_1, k4_2;
  long double t = s->start;		// set to start
  // y (0) = u1(0) =
  s->w[1][0] = -0.4;
  // y'(0) = u2(0) =
  s->w[2][0] = -0.6;

  int i;
  for (i = 0; i <= s->max; i++)
    {
      k1_1 = s->h * s->f1 (t, s->w[1][i], s->w[2][i]);
      k1_2 = s->h * s->f2 (t, s->w[1][i], s->w[2][i]);

      k2_1 = s->h * s->f1 (t + s->h / 2.0, s->w[1][i] + 0.5 * k1_1, s->w[2][i] + 0.5 * k1_2);
      k2_2 = s->h * s->f2 (t + s->h / 2.0, s->w[1][i] + 0.5 * k1_1, s->w[2][i] + 0.5 * k1_2);

      k3_1 = s->h * s->f1 (t + s->h / 2.0, s->w[1][i] + 0.5 * k2_1, s->w[2][i] + 0.5 * k2_2);
      k3_2 = s->h * s->f2 (t + s->h / 2.0, s->w[1][i] + 0.5 * k2_1, s->w[2][i] + 0.5 * k2_2);

      t += s->h;
      k4_1 = s->h * s->f1 (t, s->w[1][i] + k3_1, s->w[2][i] + k3_2);
      k4_2 = s->h * s->f2 (t, s->w[1][i] + k3_1, s->w[2][i] + k3_2);

      s->w[1][i + 1] = s->w[1][i] + 1.0 / 6.0 * (k1_1 + 2 * k2_1 + 2 * k3_1 + k4_1);
      s->w[2][i + 1] = s->w[2][i] + 1.0 / 6.0 * (k1_2 + 2 * k2_2 + 2 * k3_2 + k4_2);

      //printf ("%3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf %3.5Lf\n",
	 //k1_1, k1_2, k2_1, k2_2, k3_1, k3_2, k4_1, k4_2);
    }
}

syseq *
syseq_New (long double u1, long double u2, long double start, long double end,
		long double step, syseqf f1, syseqf f2)
{
  syseq *s = calloc (sizeof (mysyseq), 1);
  if (s == NULL)
    return NULL;
  s->u1    = u1;
  s->u2    = u2;
  s->start = start;
  s->end   = end;
  s->range = fabsl (end - start);
  s->step  = step;
  s->max   = s->range * step;
  s->h     = s->range / s->max;
  s->f1    = f1;
  s->f2    = f2;  
  s->w     = calloc (sizeof (long double), 3);
  if (s->w == NULL)
    goto fail1;
  
  int i;
  for (i = 1; i < 3; i++)
    {
      s->w[i] = calloc (sizeof (long double), s->max+1);
      if (s->w[i] == NULL)
	{
	  for (i--; i > 0; i--)
	    {
	      free (s->w[i]);
	    }
	  goto fail2;
	}
    }

  isyseq (s);
  return s;

fail2:
  free(s->w);

fail1:
  free(s);
  return NULL;
}

syseq *
syseq_Dispose (syseq * s)
{
  if (s == NULL)
    return;
  free (s->w);
  free (s);
  s = NULL;
  return NULL;
}

long double syseq_GetU1 (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->u1;
}

long double syseq_GetU2 (syseq * s)
{
  if (s == NULL)
    return NAN;

  return s->u2;
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
  if (i < 0 || i > s->max)
    return NAN;
  if (j < 1 || i > 2)
    return NAN;
  
  return s->w[j][i];
}

void syseq_Print (syseq * s) {
  int i;
  if (s == NULL)
    return;

  for (i = 0; i <= s->max; i++)
    printf ("%0.4Lf  %0.10Lf  %0.10Lf\n", s->start + s->h * i, s->w[1][i], s->w[2][i]);
}


int 
main () {

   syseq * s = syseq_New(-0.4, -0.6, 0.0, 1.0, 10, f1a, f2a);
   syseq_Print(s);

exit (0);
}
