
/*
	Numeric Analysis Code
	Using bisection to find where functions cross the origin

	By James M. Rogers
	Began work on this on 14 Jan 2014
	Finished required homework on 

	This cannot integrate discontinuous functions.

	Work left to do, 
		With functions less than 10 iterations, pretty print
			out all the work used to find the answer.

	Notes:
*/

#include <stdio.h>
#include <math.h>

// the function we are using to search
long double fex(long double x){
	return x*x*x + 4*x*x -10;
}

// the function we are using to search
long double fex2(long double x){
	return x*x + 4*x -5;
}


// p1a
long double f1a(long double x){
	return x*cosl(x) - 2*x  + 3*x -1;
}

// p1c
long double f1c(long double x){
	return 2*x*cosl(2*x) - (x -2)*(x-2);
}

// p3b
long double f3b(long double x){
	return (x-1)*tanl(x) + x* sinl(M_PI*x);
}

// Do the signs of the two numbers match
int matchSign(long double n, long double m) {
        return n*m >= 0.0f;
}

// Have we found the required accuracy
int accurate() {
	return 0;
}

void findroot(long double a, long double b, long double error, long double (*f)(long double), char * name){

	long double p = 0; // midpoint of search

	int         n = 0; // Search depth

	printf("Starting %s\n", name);

	// test for valid search bracket
	// one must be positive and the other negative
	// the curve must cross the origin line.
	if (matchSign( f(a), f(b))){
		printf("Search must cross origin at least once.\n");
		goto hardfail;
	}

	// print the header
	printf ("\tn\t\ta\t\tb\t\tp\t\tf(a)\t\tf(b)\t\tf(p)\t\n");

	// iteratively search for solution
	// need to change this to be a function
	while (n < 30) {
		n++;

		// set the midpoint
		p = a + (b-a) / 2;

		// Print a line for logging so we can trouble shoot program 
		printf ("\t%d\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t\n", n, a, b, p,f(a), f(b), f(p));

		// Did we find solution?
		if (f(p) == 0)
			goto success;

		// Are we accurate enough?
		if (accurate())
			goto success;

		// if f(p) sign matches f(a) sign
		if ( matchSign(f(p), f(a)) ) {
                        // change beginning bracket to the previous midpoint
			a=p;
		// else signs do not match
		} else {
                        // change ending bracket to the previous midpoint
			b=p;
		}
	}

fail:
	printf("Search did not find an exact answer after %d bisections.\n", n);

success: 

	printf ("Best Guess     %0.17Lf\n", p);
	printf ("Error Range    %0.17Lf\n", b-a);

hardfail:
	;
	printf("Done %s\n", name);
}


int main (){

	findroot    (1, 2, 10, &fex, "fex");  //example from class
	findroot    (0, 5, 10, &fex2, "fex2");  //example from class

	//findinterval(0.2, 0.3, &f1a, *a, *b);
	//findinterval(1.2, 1.3, &f1a, *a, *b);
	//findinterval(2, 3, &f1c, *a, *b);
	//findinterval(3, 4, &f1c, *a, *b);

	findroot (0, 1, 10, &f3b, "p3b");

	
}
