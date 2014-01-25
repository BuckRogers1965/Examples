
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

long double glob_y = 0;

long double
fsqrt (long double x, long double p)
{
  return x * x - p;
}

long double
hw2p1 (long double x, long double p)
{
  return sqrtl (x) - cosl (x);
}

long double
hw2p2 (long double x, long double p)
{
  return x * x * x - 7 * x * x + 14 * x - 6;
}

long double
hw2p3 (long double x, long double p)
{
  return x * x * x - x - 1;
}

long double
hw2p4 (long double x, long double p)
{
  return -x * x * x - cosl (x);
}

long double
hw2p5 (long double x, long double p)
{
  return 230 * x * x * x * x + 18 * x * x * x + 9 * x * x - 221 * x - 9;
}

long double
hw2p6 (long double x, long double p, long double Px, long double Py)
{


  long double y = x * x;
  glob_y = y;

  long double d = sqrtl ((x - Px) * (x - Px) + (y - Py) * (y - Py));

  //printf("x %Lf y %Lf Px %Lf Py %Lf d %Lf\n", x, y, Px, Py, d);
  return d;
}

long double
hw2p7 (long double h, long double p)
{

  // trough
  // x is height of water from top of trough
  // volume is 12.4 feet.

  long double r = 1;		// radius
  long double l = 10;		// length
  long double maxVol = 3.14159265359 * r * r * l / 2 - .001;

  long double b1 = r * r - h * h;
  long double b2 = powl (b1, 0.5);
  long double b3 = h / r - h * b2;
  long double b4 = asinl (b3);


  long double result = l * (0.5 * 3.14159265359 * r * r - r * r * b4) - p;

  //printf("x %Lf L %Lf\n", x, result );
  return result;
}

long double
hw2p (long double x)
{
  return;
}

// Do the signs of the two numbers match
int
matchSign (long double n, long double m)
{
  return n * m >= 0.0f;
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

  printf ("  Starting falseposition %s with min accuricity of %Lf\n", name, error);
  printf
    ("      a             b               c             fa             f3\n");

  do
    {
      fa = f (a, p);
      fb = f (b, p);
      c  = a - ((fa * (b - a)) / (fb - fa));
      fc = f (c, p);

      if (isnan (c))
	c = a;

      printf ("  %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf\n", a, b,
	      c, fa, fb);

      if ( (a * fc) < 0) {
        b = c;
      } else {
        a = c;
      }
	
      test = fabsl (fabsl (b) - fabsl(a));
      if (isnan (test))
	{
	  test = (b - a) / 2;
	  printf
	    ("  *** encountered an illegal operation bailing out \n  *** use estimate at your own risk\n");
	}
    }
  while (test > error);

  printf ("  Best Guess:     %0.17Lf \n", c);
  printf ("  Error Estimate: %0.17Lf \n", test);

  printf ("  Stopping falseposition %s\n\n", name);

}

void
secant (long double x1, long double x2, long double error, long double p,
	long double (*f) (long double, long double), char *name)
{

  long double f1, f2, x3, test, origx1 = x1, origx2 = x2;

  printf ("  Starting secant %s with min accuricity of %Lf\n", name, error);
  printf
    ("      x1             x2             x3            f1             f2\n");

  do
    {
      f1 = f (x1, p);
      f2 = f (x2, p);
      x3 = x2 - ((f2 * (x2 - x1)) / (f2 - f1));

      if (isnan (x3))
	x3 = x1;

      printf ("  %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf   %12.6Lf\n", x1, x2,
	      x3, f1, f2);
      x1 = x2;
      x2 = x3;

      test = fabsl (fabsl (x1) - fabsl(x2));
      //test = fabsl (f2);
      if (isnan (test))
	{
	  test = (x2 - x1) / 2;
	  printf
	    ("  *** encountered an illegal operation bailing out \n  *** use estimate at your own risk\n");
	}
    }
  while (test > error);

  printf ("  Best Guess:     %0.17Lf \n", x3);
  printf ("  Error Estimate: %0.17Lf \n", test);

  printf ("  Stopping secant %s\n\n", name);

}

void
bisect (long double a, long double b, long double error, long double p,
	long double (*f) (long double, long double), char *name)
{

  long double mid = 0;		// midpoint of search

  int n = 0;			// Search depth

  printf ("  Starting bisect %s with min accuricity of %Lf\n", name, error);

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
  // need to change this to be a function
  while ((b - a) > error)
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

  printf ("  Best Guess  %24.17Lf\n", mid);
  printf ("  Error Range %24.17Lf\n", b - a);

hardfail:
  ;
  printf ("  Done bisect %s after %d tries\n\n", name, n);
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
printgraph (long double a, long double b, long double i, long double p,
	    long double (*f) (long double, long double), char *name)
{

  long double previous = f (a, p);
  long double current = f (a, p);
  unsigned long count = 0;

  printf ("Starting printgraph %s\n", name);
  for (; a < b; a += i)
    {
      current = f (a, p);
      if (matchSign (previous, current))
	{
	}
      else
	{
	  printf ("Found sign change from %Lf to %Lf\n", a - i, a);
	}
      previous = current;
      count++;
    }

  printf ("Done printgraph %s after %lu iterations\n\n", name, count);
}

unsigned long
findpointfunc (long double a, long double b, long double Px, long double Py,
	       long double i, long double p,
               long double (*f) (long double, long double, long double, long double),
	       char *name)
{


  // this will get closer and closer and then start moving away. 
  // the two points where it changes is the new interval.
  // track if we are increasing or decreasing

  long double previous = f (a, p, Px, Py);
  long double current = f (a, p, Px, Py);
  unsigned long count = 0;

  long double prevDirect = previous - current;
  long double currDirect = previous - current;

  for (; a < b; a += i)
    {
      current = f (a, p, Px, Py);
      currDirect = previous - current;

      if (matchSign (prevDirect, currDirect))
	{
	}
      else
	{
	  printf ("Found direction change at x %Lf at a y of %Lf\n", a - i,
		  glob_y);
	  if (p < 1)
	    {
	      printf ("Best Guess  x %0.17Lf  y %0.17Lf\n", a + i / 2,
		      glob_y);
	      printf ("Error Range    %0.17Lf\n", i);
	      goto done;
	    }
	  else
	    {
	      return (findpointfunc
		      (a - i * 2, a, Px, Py, i / 10, p - 1, f, name) + count);
	    }

	}
      previous = current;
      prevDirect = currDirect;

      count++;
    }

done:

  printf ("Best Guess  x %0.17Lf  y %0.17Lf\n", a + i / 2, glob_y);
  printf ("Error Range   %0.17Lf\n", i);
  return count;
}

void
findpoint (long double a, long double b, long double Px, long double Py,
	   long double i, long double p,
           long double (*f) (long double, long double, long double, long double),
	   char *name)
{

  // stub function so header is only printed once
  unsigned long count;

  printf ("Starting findpoint %s with min accuricity of %Lf\n", name, 0.0L);
  count = findpointfunc (a, b, Px, Py, i, p, f, name);

  printf ("Done findpoint %s after %lu iterations\n\n", name, count);
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

int
main ()
{
  findgraph ( 2, 3, .1, .0001, 5,    &fsqrt, "Find square Root of 5");
  findgraph (10,500, 5, .0000001,    5487, &fsqrt, "Find square Root of 5487");

  findgraph ( 0, 1,   .1,  .0001,  0, &hw2p1, "hw2p1");
  findgraph ( 1, 3.2, .1,  .0001,  0, &hw2p2, "hw2p2");
  findgraph ( 1, 2,   .1,  .0001,  0, &hw2p3, "hw2p3");
  findgraph (-1, 0,   .01, .0001,  0, &hw2p4, "hw2p4");
  findgraph (-1, 0,   .01, .00001, 0, &hw2p5, "hw2p5 from -1 to 0");
  findgraph ( 0, 1,   .01, .00001, 0, &hw2p5, "hw2p5 from 0 to 1");
  findgraph (-1 , 1,  .1,  .00001, 0, &hw2p5, "hw2p5 from 0 to 1");

  findpoint (0, 2, 0, 1, .001, 8, &hw2p6, "hw2p6");

  findgraph (0, 1, .001, .0001, 12.4, &hw2p7, "hw2p7");
//  findgraph (0, 1, .001, .0001, 15.7, &hw2p7, "hw2p7full");
  findgraph (0, 1, .001, .0001, 7.5, &hw2p7, "hw2p7half");
  findgraph (0, 1, .001, .0001, 1, &hw2p7, "hw2p7empty");
}
