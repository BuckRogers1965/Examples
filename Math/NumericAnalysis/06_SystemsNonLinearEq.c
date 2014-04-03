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

typedef long double (*syseqf) (long double *);
typedef struct SystemNL SystemNL;
struct SystemNL
{
  int OrderSize;
  syseqf **J;
  syseqf f[MAXORDER];
  long double initial[MAXORDER];
} mySystem;

SystemNL *
System_New (int OrderSize)
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

void
System_Solve (SystemNL * s)
{
  if (s == NULL)
    return;

  // double check to see if we are lacking any Jacobain entries


  // find beginning points using method of steepist descent

  matrix *m = NewMatrix (s->OrderSize, s->OrderSize);

  Mat_Dispose (m);
  return;
}
