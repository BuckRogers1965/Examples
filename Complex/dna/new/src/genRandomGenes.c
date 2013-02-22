/*
 *
 * The purpose of this file is to generate random DNA sequences to analayze using 
 * the same tools that I am using to analysis the real DNA sequences.
 *
 * The differences between real and randomly generated DNA sequences will
 * help highlight the features and structures that can be found in DNA.
 *
 */

/*
 * The inputs to this program are size and distribution of A T G and C.
 *
 * If only size is given, then generate a file with a distribution of
 * 30, 30, 20, 20 by default.
 * If we don't get 1 or 5 arguments, then print usage on stderr and exit 1;
 *
 * Then print out the results to stdout.
 *
 * If stdout can't print, then complain on stderr and exit 1;
 *
 * If we get everything else done, return a 0 from main.
 *
 */

/*
 * James M. Rogers
 * 30 August 2003
 *
 */

#include <stdio.h>
#include <time.h>

int main (int argc, char * argv []){

	int dist[4] = {30,30,20,20};
	long size=0, current=0;
	char genecode[4]={'T', 'A', 'G', 'C'};
	int i;

	long total = 0;
	
	/*printf("%d\n", argc);
	 */

	/* if we don't get the correct number of arguments */
	if (argc != 2 && argc != 6){
		fprintf(stderr, "This program expects a size followed by an optional 4 percentages of distribution that represent T A G and C. If only a size is given, we default to 30 30 20 20.\n");
		exit (1);
	}

	/* read in the size and if needed, the 4 values. */

	size = atol(argv[1]);

	/* if we have a new distribution, read them in, fail if they are not each between 0 and 100 or if they don't add upto 100, exactly. */
	if (argc == 6) {
		int totalPercentage = 0;
		int i, j;
		for (i=2, j=0; i < 6; i++, j++){
			dist[j] = atoi(argv[i]);
			if (dist[j] < 0 || dist[j] > 100){
				fprintf(stderr, "A percentage is between 0 and 100, you gave %d on argument %d.\n", dist[j], i);
				exit (1);
			}
			totalPercentage += dist[j];
		}
		if (totalPercentage!=100){
			fprintf(stderr, "Total of all distribution percenages must exactly equal 100. Yours add up to %d instead.\n", totalPercentage);
			exit (1);
		}
	}

	/* At this point we have everything we need, lets spit out some random numbers! */

	/* first, initialize this to something we know it has never been before, the seconds since 1970 */
	srand (time(NULL));

	for (; current < size; current++){
		int result;
		char * result_s = (char *)&result;

		// get random number and throw out stuff to prevent rounding errors
		result = 101;
		while (result > 99) {
			/* get a random number */
			result = rand ();

			/* pack a whole random numbers creamy goodness into a single byte */
			/* this is because some implemenations of rand don't do so well */
			/* on the low order bytes. */
			result = (unsigned char)(result_s[0] ^ result_s[1] ^result_s[2] ^result_s[3]);

			/* get a number between 0 and 99 */
			result = result / 2 ;
			//result = (unsigned char)(result_s[0]);
		} 

		/* is less than current value? 
		 * if not, then subtract current value and go on
		 */

		for (i=0; i<4 ; i++)
			if ( dist[i]  && result < dist[i] ){
				/* we have a match */
				putchar(genecode[i]);
				break;
			} else {
				if (i == 3){
					putchar(genecode[i]);
					break;
				}

				result -= dist[i] ;

			}
	}

	return 0;
}
