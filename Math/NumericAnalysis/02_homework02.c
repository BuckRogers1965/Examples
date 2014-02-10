
/*
	Numeric Analysis Code
	Homework 02

	By James M. Rogers
	Began work on this on 23 Jan 2014
	Finished required homework on 

	This cannot integrate discontinuous functions.

	Work left to do, 

	Notes:
*/

#include <stdio.h>
#include <math.h>
#include "methods.h"

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
  long double result = l * ( 0.5L *M_PI * r*r- r*r * asinl( h/r - h * sqrtl( r*r-h*h) ) );

 // printf("  h %Lf r %Lf l %Lf max %Lf result %Lf p %Lf\n", h, r, l, maxVol, result, p );
  return result - p;
}

long double
hw2p7a (long double h, long double p)
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

  //printf("a h %Lf r %Lf l %Lf max %Lf result %Lf p %Lf\n", h, r, l, maxVol, result, p );
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

int
main ()
{

  findgraph ( 0, 1,   .1,  .0001,  0, &hw2p1, "hw2p1");
  findgraph ( 1, 3.2, .1,  .0001,  0, &hw2p2, "hw2p2");
  findgraph ( 1, 2,   .1,  .0001,  0, &hw2p3, "hw2p3");
 
  printf("---------------------------------\n\n");

  //findgraph (-1, 0,   .01, .001,  0, &hw2p4, "hw2p4");
  secant (-1, 0, .001,  0, &hw2p4, "hw2p4");
  falseposition (-1, 0, .001,  0, &hw2p4, "hw2p4");

  printf("---------------------------------\n\n");

  findgraph (-1, 0,   .01, .00001, 0, &hw2p5, "hw2p5 from -1 to 0");
  findgraph ( 0, 1,   .01, .00001, 0, &hw2p5, "hw2p5 from 0 to 1");
  //findgraph (-1 , 1,  .1,  .00001, 0, &hw2p5, "hw2p5 from -1 to 1");

  printf("---------------------------------\n\n");

  findgraph (0, 1, .1,  .01,  12.4,  &hw2p7, "hw2p7 trough with 12.4 volume");
  //findgraph (0, 1, .1,  .01,  12.4,  &hw2p7a, "hw2p7a modified formula for trough with 12.4 volume");
}
