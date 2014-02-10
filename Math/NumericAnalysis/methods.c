
/*
	Numeric Analysis Code
	Using bisection to find where functions cross the origin

	By James M. Rogers
	Began work on this on 23 Jan 2014
	Finished required homework on 

	This cannot integrate discontinuous functions.

	Work left to do, 

	Notes:
*/

#include <stdio.h>
#include <math.h>

// Do the signs of the two numbers match
int
matchSign (long double n, long double m)
{
  return n * m >= 0.0L;
}

void
falseposition (long double a, long double b, long double error, long double p,
	       long double (*f) (long double, long double), char *name)
{

/*
https://ece.uwaterloo.ca/~dwharder/NumericalAnalysis/10RootFinding/falseposition/#howto
Given the interval [a, b], define c = (a f(b) − b f(a))/(f(b) − f(a)). Then
if f(c) = 0 (unlikely in practice), then halt, as we have found a root,
if f(c) and f(a) have opposite signs,
    then a root must lie on [a, c], 
    so assign step = b - c and 
       assign b = c,
else f(c) and f(b) must have opposite signs, and thus a root must lie on [c, b],
  so assign step = c - a and assign a = c.
*/

  long double fa, fb, fc, c, test;
  int n = 0;

  printf ("  Starting falseposition %s with min accuracy of %Lf\n", name,
	  error);
  printf
    ("      a             b               c             fa             f3\n");

  do
    {

      fa = f (a, p);
      fb = f (b, p);
      c = a - ((fa * (b - a)) / (fb - fa));
      fc = f (c, p);

      if (isnan (c))
	c = a;

      printf ("  %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf\n", a, b,
	      c, fa, fb);

      if ((a * fc) < 0)
	{
	  test = fabsl (c - b);
	  b = c;
	}
      else
	{
	  test = fabsl (a - c);
	  a = c;
	}

      //test = fabsl (b - a);
      if (isnan (test))
	{
	  printf
	    ("  *** encountered an illegal operation bailing out \n  *** use estimate at your own risk\n");
	}

      // fail gracefully
      n++;
      if (n > 20)
	{
	  printf ("  *** This method is failing, use another technique \n");
	  break;
	}
    }
  while (test > error);

  printf ("  Best Guess:     %0.17Lf \n", c);
  printf ("  Error Estimate: %0.17Lf \n", test);

  printf ("  Stopping falseposition %s\n\n", name);

}

void
secant (long double a, long double b, long double error, long double p,
	long double (*f) (long double, long double), char *name)
{

  long double fa, fb, c, test;
  int n = 0;

  printf ("  Starting secant %s with min accuracy of %Lf\n", name, error);
  printf
    ("       a             b             c             fa             fb\n");

  do
    {
      fa = f (a, p);
      fb = f (b, p);
      c = b - ((fb * (b - a)) / (fb - fa));

      if (isnan (c))
	c = a;

      printf ("  %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf\n", a, b,
	      c, fa, fb);
      //a = b;
      //b = c;
        test = fabsl (c - a);

	a = c;

      if (isnan (test))
	{
	  test = fabsl (b - a);
	  printf
	    ("  *** encountered an illegal operation bailing out \n  *** use estimate at your own risk\n");
	}

      // fail gracefully
      n++;
      if (n > 20)
	{
	  printf ("  *** This method is failing, use another technique \n");
	  break;
	}
    }
  while (test > error);

  printf ("  Best Guess:     %0.17Lf \n", c);
  printf ("  Error Estimate: %0.17Lf \n", test);

  printf ("  Stopping secant %s\n\n", name);

}

void
bisect (long double a, long double b, long double error, long double p,
	long double (*f) (long double, long double), char *name)
{

  long double mid = 0;		// midpoint of search

  int n = 0;			// Search depth

  printf ("  Starting bisect %s with min accuracy of %Lf\n", name, error);

  // test for valid search bracket
  // one must be positive and the other negative
  // the curve must cross the origin line.
  if (matchSign (f (a, p), f (b, p)))
    {
      printf ("  *** Search must cross origin at least once.\n");
      goto hardfail;
    }

  // print the header
  printf ("   n\t    a\t\t  b\t\t  p\t\t  f(a)\t\tf(b)\t\tf(p)\n");

  // iteratively search for solution
  while (fabsl(b - a) > error)
    {
      n++;

      // set the midpoint
      mid = a + (b - a) / 2;

      // Print a line for logging so we can trouble shoot program 
      printf ("  %3d%15.6Lf%15.6Lf%15.6Lf% 15.6Lf%15.6Lf%15.6Lf\t\n", n, a, b,
	      mid, f (a, p), f (b, p), f (mid, p));

      // Did we find solution?
      if (f (mid, p) == 0)
	goto success;

      // if f(p,p) sign matches f(a,p) sign
      if (matchSign (f (mid, p), f (a, p)))
	{
	  // change beginning bracket to the previous midpoint
	  a = mid;
	  // else signs do not match
	}
      else
	{
	  // change ending bracket to the previous midpoint
	  b = mid;
	}
    }

  goto success;
fail:
  printf ("  *** encountered an error, use at own risk\n");

success:

  printf ("  Best Guess      %24.17Lf\n", mid);
  printf ("  Error Estimate: %24.17Lf\n", b - a);

hardfail:
  ;
  printf ("  Done bisect %s after %d tries\n\n", name, n);
}


void
newton (long double p0, long double b, long double error, long double p,
	long double (*f) (long double, long double), char *name)
{
  long double p1, fb, fc, c, test;
  int n = 0;

  printf ("  Starting newton %s with min accuracy of %Lf\n", name, error);
  printf ("      p0            p1               test \n");

  do
    {
      p1 = p0 - f (p0, 0) / f (p0, 1);

      if (isnan (p1))
	goto fail;

      test = fabsl (p0 - p1);

      printf ("  %12.6Lf   %12.6Lf   %12.6Lf   \n", p0, p1, test);
      p0 = p1;

      // fail gracefully
      n++;
      if (n > 20)
	{
	  printf ("  *** This method is failing, use another technique \n");
	  break;
	}

    }
  while (test > error);

fail:
  printf ("  Best Guess:     %0.17Lf \n", p1);
  printf ("  Error Estimate: %0.17Lf \n", test);

  printf ("  Stopping newton %s\n\n", name);

}


void
findinterval (long double a, long double b, long double p,
	      long double (*f) (long double, long double), char *name)
{
  printf ("Starting  findinterval %s\n", name);
  // test for valid search bracket
  // one must be positive and the other negative
  // the curve must cross the origin line.
  printf ("f(a, p): f(%Lf) is %Lf.\n", a, f (a, p));
  printf ("f(b, p): f(%Lf) is %Lf.\n", b, f (b, p));
  if (matchSign (f (a, p), f (b, p)))
    {
      printf ("Interval must cross origin at least once.\n");
    }
  else
    {
      printf ("There is at least one solution between %Lf and %Lf.\n", a, b);
    }

  printf ("Done findinterval %s\n\n", name);
}


void
findgraph (long double a, long double b, long double i, long double error,
	   long double p, long double (*f) (long double, long double),
	   char *name)
{

  long double previous = f (a, p);
  long double current = f (a, p);
  unsigned long count = 0;

  printf
    ("Starting scan of %s on interval %Lf to %Lf with increment of %Lf\n\n",
     name, a, b, i);
  for (; a < b; a += i)
    {

      current = f (a, p);
      if (matchSign (previous, current))
	{
	}
      else
	{
	  printf ("  Found sign change from %Lf to %Lf\n\n", a - i, a);
	  bisect (a - i, a, error, p, f, name);
	  secant (a - i, a, error, p, f, name);
	  falseposition (a - i, a, error, p, f, name);
	}
      previous = current;
      count++;
    }

  printf ("Done scanning %s after %lu iterations\n\n", name, count);
}
