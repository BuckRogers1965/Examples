/*  Numeric Analysis Code

	By James M. Rogers
	Began work on this on 23 Jan 2014
	This cannot integrate discontinuous functions.
*/

// returns a 1 if the two signs match, or a 0 otherwise
int
matchSign (long double, 	// first number to match against
           long double );	// the second number.
           
void
falseposition 
( long double,	// beginning of the interval to search
		long double,	// end of the interval
		long double,	// precision to find
                long double,	// value to pass into the second parameter of the function
				// the function to call 
	long double (*f) (long double, long double),		
		char *);	// the name of the operation for logging 
		
void
secant 		( long double,	// beginning of the interval to search
		long double,	// end of the interval
		long double,	// precision to find
                long double,	// value to pass into the second parameter of the function
				// the function to call 
	long double (*f) (long double, long double),		
		char *);	// the name of the operation for logging 
		
void
bisect
( long double,	// beginning of the interval to search
		long double,	// end of the interval
		long double,	// precision to find
                long double,	// value to pass into the second parameter of the function
				// the function to call 
	long double (*f) (long double, long double),		
		char *);	// the name of the operation for logging 
		
void
newton
( long double,	// beginning of the interval to search
		long double,	// end of the interval -ignored
		long double,	// precision to find
                long double,	// value to pass into the second parameter of the function
				// the function to call 
	long double (*f) (long double, long double),		
		char *);	// the name of the operation for logging 
		
void
findinterval (long double, long double, long double,
	      long double (*f) (long double, long double), char *);
	      
void
findgraph (long double, long double, long double, long double,
	   long double, long double (*f) (long double, long double),
	   char *);
