
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

// the function we are using to search
long double fex(long double x, long double p){
        return x*x*x + 4*x*x -10;
}

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
  // h is height of water from top of trough
  // volume is 12.4 feet.
  // Got the formula for the water volume by height from here:
  // http://answers.yahoo.com/question/index?qid=20120329114323AAgspZg

  long double r = 1.0L;		// radius
  long double l = 10.0L;	// length
  long double maxVol = M_PI * r * r * 0.5L * l;

  h = 1-h;
  long double result =  l*( r*r * ( M_PI/2 -asinl((1-h)/r) ) - (r-h) * sqrtl( h*2*r - h*h) ) ;
  //long double result = maxVol - l *(  r*r* acosl((r-h)/r) - (r-h)*powl(2*r*h - h*h, 0.5L) ) ;
  //long double result = maxVol - l *( r*r * asinl(h/r - h* sqrtl(r*r - h*h))  ) ;

  //printf("h %Lf r %Lf l %Lf max %Lf result %Lf\n", h, r, l, maxVol, result );
  return result-p;
}

long double
hw2ptri (long double height, long double p)
{
  // simple version of the above.
  // Trough formed by nailing two 2 foot boards together
  long double h = 2-height;
  long double base = 2.0L * h ;
  long double l = 10; // length

  long double v =  0.5L * base * h * l ;
  //printf ("h %Lf height %Lf base %Lf p %Lf v %Lf \n", h, height, base, p, v );
  return  v - p;
}

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
  int n=0;

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
	
      test = fabsl (f(c,p));
      if (isnan (test))
	{
	  test = (b - a) ;
	  printf
	    ("  *** encountered an illegal operation bailing out \n  *** use estimate at your own risk\n");
	}

      // fail gracefully
      n++;
      if (n>20) {
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
  int n=0;

  printf ("  Starting secant %s with min accuricity of %Lf\n", name, error);
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
      a = b;
      b = c;

      test = fabsl (f(c,p));
      if (isnan (test))
	{
          test = fabsl (b - a);
	  printf
	    ("  *** encountered an illegal operation bailing out \n  *** use estimate at your own risk\n");
	}

      // fail gracefully
      n++;
      if (n>20) {
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

  printf ("  Best Guess      %24.17Lf\n", mid);
  printf ("  Error Estimate: %24.17Lf\n", b - a);

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
  //findgraph ( 2, 3, .1, .0001, 5,    &fsqrt, "Find square Root of 5");
  //findgraph (10,500, 5, .0000001,    5487, &fsqrt, "Find square Root of 5487");

  findgraph ( 0, 1,   .1,  .0001,  0, &hw2p1, "hw2p1");
  findgraph ( 1, 3.2, .1,  .0001,  0, &hw2p2, "hw2p2");
  findgraph ( 1, 2,   .1,  .0001,  0, &hw2p3, "hw2p3");
  findgraph (-1, 0,   .01, .0001,  0, &hw2p4, "hw2p4");
  findgraph (-1, 0,   .01, .00001, 0, &hw2p5, "hw2p5 from -1 to 0");
  findgraph ( 0, 1,   .01, .00001, 0, &hw2p5, "hw2p5 from 0 to 1");
  findgraph (-1 , 1,  .1,  .00001, 0, &hw2p5, "hw2p5 from 0 to 1");

  findpoint (0, 2, 0, 1, .001, 8, &hw2p6, "hw2p6");

  findgraph (0, 1, .1,  .01,  12.4,  &hw2p7, "hw2p7 trough with 12.4 volume");

/*
  printf ("finding a range of values for testing.\n");
  long double i;
  for (i=0; i< 15; i++){
    char name[40];
    sprintf(name, "hw2p7 %Lf", i);
    findgraph (0, 1, .01, .00001, i,    &hw2p7, name);
  }
*/

  //findgraph (-1, 3, .1, .001, 38, &hw2ptri, "hw2ptri full");
  //findgraph (-1, 3, .1, .001, 10, &hw2ptri, "hw2ptri half full");
  //findgraph (-1, 3, .1, .001, .1, &hw2ptri, "hw2ptri empty");

  //findgraph   ( 0, 2, .1, .00000001, 0, &fex, "fex");
}
