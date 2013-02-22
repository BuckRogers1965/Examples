#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prime.h"

/*

   This program is written to calculate the primes in the first billion
   numbers.

    Written by James M. Rogers
    04 May 1999

    A test in memory to see if it can be made faster
*/

char z[(MAXSIZE/8)+1];

void set_not_prime(unsigned long i) {

    ldiv_t results;
    char   c;

    results=ldiv(i, 16);

    switch (results.rem) {

        case 1:
             c='\xFE';
             break;
        case 3:
             c='\xFD';
             break;
        case 5:
             c='\xFB';
             break;
        case 7:
             c='\xF7';
             break;
        case 9:
             c='\xEF';
             break;
        case 11:
             c='\xDF';
             break;
        case 13:
             c='\xBF';
             break;
        case 15:
             c='\x7F';
             break;
        default:
             break;
    }
    z[results.quot]=(z[results.quot] & c);
}

int is_prime(int i) {

    ldiv_t results;
    char   c;

    results=ldiv(i, 16);

    switch (results.rem) {

        case 1:
             c='\x01';
             break;
        case 3:
             c='\x02';
             break;
        case 5:
             c='\x04';
             break;
        case 7:
             c='\x08';
             break;
        case 9:
             c='\x10';
             break;
        case 11:
             c='\x20';
             break;
        case 13:
             c='\x40';
             break;
        case 15:
             c='\x80';
             break;
        default:
             break;
    }
 
    return (int) (z[results.quot] & c);
}

void set_matrix(unsigned long i) {

    unsigned long    j;
    unsigned long    k;

    k=(MAXSIZE/i+1);

    for(j=i;j<k;j+=2) {
        set_not_prime(j*i);
    }
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

        /* If there is no remainder, print the current_factor, continue. */
        results = ldiv(x, i);
        if ( results.rem == 0 ) {
            printf ("%d ", i);
            x = results.quot;
            max_factor = sqrt(x)+1 ;
            continue;
        }
	i++; i++;
    }
        printf ("%d\n", x);
}

main(int argc, char *argv[]){

    unsigned long        i;
    div_t	results;
    int         c,
                j;

    /* Initialize the array */

    for(i=0;i<MAXSIZE/16;i++) {
        z[i]='\xFF';
    }

    /* For loop is the main loop that controls the function of the program */

    for(i=3;i<MAXSIZE; i++,i++ )
        if (is_prime(i)) 
            set_matrix(i);

    for(i=1;i<2147483647; i=i+10000)
        factors(i);


    /* Done, flush and close */
/*
    for (i=0; i<MAXSIZE/16;i++)
         putc(z[i], stdout);
*/
    exit (0);

}

