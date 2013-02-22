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

#define MAXSIZE  10000002

char z[MAXSIZE+1];

void set_not_prime(unsigned long i) {

    z[i]=0;
}

int is_prime(unsigned long i) {

    return (int) z[i];
}

void set_matrix(unsigned long i) {

    unsigned long    j;
    unsigned long    k;

    printf("%d\n", i);
    k=(MAXSIZE/i+1);

    for(j=i;j<k;j+=2) {
        set_not_prime(j*i);
    }
}

main(int argc, char *argv[]){

    unsigned long        i;
    div_t	results;
    int         c,
                j;

    /* Initialize the file, quit if we cannot write all the way to the end 
       Because this takes so long on huge databases, I am going to 
       initialize the first several primes as I go along.  I mean, everyone
       knows that 2, 3, 5, and 7 are prime...
    */

    z[0]=0;
    z[1]=0;
    z[2]=1;
    z[3]=1;
    z[4]=0;
    for(i=5;i<MAXSIZE;i++) {

        z[i++]=1;
        z[i]=0;
    }

    printf("2\n");

    /* For loop is the main loop that controls the function of the program */
    for(i=3;i<MAXSIZE; i+=2)
        if (is_prime(i)) 
            set_matrix(i);
          
    /* Done, flush and close */
    exit (0);
}

