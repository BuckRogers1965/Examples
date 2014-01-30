
/*
	Numeric Analysis Code
	find point

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
hw2p6 (long double x, long double p, long double Px, long double Py)
{
  long double y = x * x;
  glob_y = y;

  long double d = sqrtl ((x - Px) * (x - Px) + (y - Py) * (y - Py));

  //printf("x %Lf y %Lf Px %Lf Py %Lf d %Lf\n", x, y, Px, Py, d);
  return d;
}


long double
hw2p6ex2 (long double x, long double p, long double Px, long double Py)
{
  long double y = 4- x * x;
  glob_y = y;

  long double d = sqrtl ((x - Px) * (x - Px) + (y - Py) * (y - Py));

  //printf("x %Lf y %Lf Px %Lf Py %Lf d %Lf\n", x, y, Px, Py, d);
  return d;
}


//------------------------------

// Do the signs of the two numbers match
int
matchSign (long double n, long double m)
{
  return n * m >= 0.0L;
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


int
main ()
{

  findpoint (0, 2, 0, 1, .001, 8, &hw2p6, "hw2p6");

  // testing the point function
  //findpoint (0, 2, 1, 1, .001, 8, &hw2p6, "hw2p6");
  //findpoint (1, 3, 2, 4, .001, 8, &hw2p6, "hw2p6");
  //findpoint (1, 4, 0, 2, .001, 8, &hw2p6, "hw2p6");
  //findpoint (1, 8, 18, 0, .001, 8, &hw2p6, "hw2p6");

}
