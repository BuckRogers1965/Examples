#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double (*rkf) (long double, long double);
typedef struct rk rk;
struct rk
{
  long double alpha;
  long double start;
  long double end;
  long double range;
  long double step;
  long double max;
  long double t;
  long double h;
  rkf f;
  long double *w;
} myrk;


// internal function
void
irk (rk * r)
{
  long long i = 0;
  long double k1, k2, k3, k4;
  r->w[0] = r->alpha;
  for (i = 0; i < r->max; i++)
    {
      k1 = r->h * r->f (r->t * i, r->w[i]);
      k2 = r->h * r->f (r->t * i + r->h / 2, r->w[i] + 1.0 / 2.0 * k1);
      k3 = r->h * r->f (r->t * i + r->h / 2, r->w[i] + 1.0 / 2.0 * k2);
      k4 = r->h * r->f (r->t * (i + 1), r->w[i] + k3);
      r->w[i + 1] = r->w[i] + 1.0 / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
    }
}

rk *
rk_New (long double alpha, long double start, long double end,
		long double step, rkf f)
{
  rk *r = calloc (sizeof (myrk), 1);
  if (r == NULL)
    return NULL;
  r->alpha = alpha;
  r->start = start;
  r->end = end;
  r->range = fabsl (end - start);
  r->step = step;
  r->max = r->range * step;
  r->h = r->range / r->max;
  r->t = r->h;
  r->f = f;
  r->w = calloc (sizeof (long double), r->max + 1);
  if (r->w == NULL)
    goto fail1;

  irk (r);
  return r;

fail1:
  free (r);
  return NULL;
}

rk *
rk_Dispose (rk * r)
{
  if (r == NULL)
    return;
  free (r->w);
  free (r);
  r = NULL;
  return NULL;
}

long double rk_GetAlpha (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->alpha;
}

long double rk_GetStart (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->start;
}

long double rk_GetEnd (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->end;
}

long double rk_GetRange (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->range;
}

long double rk_GetStep (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->step;
}

long double rk_GetMax (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->max;
}

long double rk_GetT (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->t;
}

long double rk_GetH (rk * r)
{
  if (r == NULL)
    return NAN;

  return r->h;
}

long double rk_GetW (rk * r, int i)
{
  if (r == NULL)
    return NAN;
  if (i < 0 || i > r->max)
    return NAN;

  return r->w[i];
}

void rk_Print (rk * r) {
  int i;
  if (r == NULL)
    return;

  for (i = 0; i <= r->max; i++)
    printf ("%Lf\t %Lf\n", r->t * i, r->w[i]);
}
