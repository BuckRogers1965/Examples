#include <stdio.h>

// the function we are using to search
long double f(long double x){
	return x*x*x + 4*x*x -10;
}

// Do the signs of the two numbers match
int matchSign(long double n, long double m) {
        return n*m >= 0.0f;
}

// Have we found the required accuracy
int accurate() {
	return 0;
}

int main(){

	long double a = 1, // start of search bracket
	            b = 2, // end of search bracket
		    p = 0; // midpoint of search

	int         n = 0; // Search depth

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


}
