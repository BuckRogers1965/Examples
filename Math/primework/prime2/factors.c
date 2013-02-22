#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*

   This program is written to calculate the primes in the first billion
   numbers.

    Written by James M. Rogers
    04 May 1999

    A test in memory to see if it can be made faster
*/

#define MAXSIZE 46340

char isprime[(MAXSIZE)+1];

void set_matrix(unsigned long i) {

    unsigned long    j;
    unsigned long    k;

    k=(MAXSIZE/i+1);

    for(j=i;j<k;j+=2) {
        isprime[j*i]=0;
    }
}

void init_matrix(){
    unsigned long        i;

    /* Initialize the array to mark all as being prime */

    for(i=0;i<MAXSIZE;i++) {
        isprime[i]=1;
    }

    /* For loop is the main loop that controls the function of the program */

    for(i=3;i<MAXSIZE; i++,i++ )
        if (isprime[i]) 
            set_matrix(i);

}

void factors( int x) {

    int i;
    int max_factor;
    ldiv_t results;

    /* set the max_factor to square root of variable */
    max_factor = sqrt(x)+1;

    printf ("%d: ", x);

    /* find all factors of 2, if any */
    /* we pull this check out to make the next loop simpler and faster. */
    i=2;
    while(x>max_factor) {

        /* Test factor */
        results = ldiv(x, i);
    
        /* If there is no remainder, print the current_factor, continue. */
        if ( results.rem == 0 ) {
            printf ("%d ", i);
            x = results.quot;
            max_factor = sqrt(x)+1 ;
	    if (x!=2)
	        continue;
        }
	break;
    }

    /* find the next factor 
     * we start at 3 and add 2 each time 
     * because we already checked for all the 2's 
     * we continue until the number we are at is less than
     * the square root of the number we are factoring */
    for(i=3; i<max_factor; ) {

	/* skip the numbers if they aren't prime */
	/* only primes can be factors */
	/* this is the key to the biggest speedup */
	if (!isprime[i]){
	    i++; i++;
	    continue;
	}

        /* If there is no remainder, print the current_factor, continue. */
        results = ldiv(x, i);
        if ( results.rem == 0 ) {
            printf ("%d ", i);
            x = results.quot;
            max_factor = sqrt(x)+1 ;
	    /* if we found a factor, repeat without incrementing to see if 
	     * the same value is also a factor of the remainder */
            continue;
        }
	i++; i++;
    }
        printf ("%d\n", x);
}

main(int argc, char *argv[]){

    unsigned long i;

    init_matrix();

    for(i=1;i<2147483647; i=i+10000)
        factors(i);


    exit (0);

}

