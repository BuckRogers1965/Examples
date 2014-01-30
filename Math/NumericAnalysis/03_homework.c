
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
#include "methods.h"

// the function we are using to search
long double fexp(long double x, long double p){
        return 3*x*x + 8*x*x ;
}


// the function we are using to search
long double fex(long double x, long double p){
	if (p==1) return (fexp (x, 0));
        return x*x*x + 4*x*x -10;
}

int
main ()
{

  findgraph ( 0, 10,   .1,  .0001,  0, &fex, "fex");
  newton (1, 10, .0001, 0, &fex, "fex");
}
