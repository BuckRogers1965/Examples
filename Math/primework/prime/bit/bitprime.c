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

#define MAXSIZE  160000000

char z[(MAXSIZE/8)+1];

void set_not_prime(unsigned long i) {

    ldiv_t results;
    char   c;

    results=ldiv(i, 8);

    switch (results.rem) {

        case 0:
             c='\xFE';
             break;
        case 1:
             c='\xFD';
             break;
        case 2:
             c='\xFB';
             break;
        case 3:
             c='\xF7';
             break;
        case 4:
             c='\xEF';
             break;
        case 5:
             c='\xDF';
             break;
        case 6:
             c='\xBF';
             break;
        case 7:
             c='\x7F';
             break;
        default:
             break;

    }

    z[results.quot]=(z[results.quot] & c);
}

int is_prime(unsigned long i) {

    ldiv_t results;
    char   c;

    results=ldiv(i, 8);

    switch (results.rem) {

        case 0:
             c='\x01';
             break;
        case 1:
             c='\x02';
             break;
        case 2:
             c='\x04';
             break;
        case 3:
             c='\x08';
             break;
        case 4:
             c='\x10';
             break;
        case 5:
             c='\x20';
             break;
        case 6:
             c='\x40';
             break;
        case 7:
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

main(int argc, char *argv[]){

    unsigned long        i;
    div_t	results;
    int         c,
                j;

    /*
          Initialize the array
    */

    z[0]='\xAC';
    for(i=1;i<MAXSIZE/8;i++) {

        z[i]='\xAA';
    }


    /* For loop is the main loop that controls the function of the program */
    for(i=3;i<MAXSIZE; i+=2)
        if (is_prime(i)) 
            set_matrix(i);
          
    /* Done, flush and close */
    for (i=0; i<MAXSIZE/8;i++)
         putc(z[i], stdout);
    exit (0);
}

