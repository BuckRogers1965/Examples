#include "halfbitprime.h"

/*

	This program is written to calculate the primes in the first billion
        numbers.

	Written by James M. Rogers

	04 May 1999

*/

int is_prime(unsigned long i, FILE *stream) {

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

    if(fseek(stream, results.quot, SEEK_SET)) {
        printf("Failed to fseek during is_prime\n");
	exit (1);
    }
    return (int) (fgetc(stream) & c);
}

main(int argc, char *argv[]){

    unsigned long        i=0;
    int         c,
                j;
    FILE        *stream;    /* need a stream pointer of type FILE */ 

    /* ensure that the filename in argv[1] exists and is a file */

    /* open the file designated on the command line */
    if (!(stream = fopen(argv[1], "r+"))){
	printf("Failed to open the designated file, I am quiting.\n");
	exit (1);
    } 
        sscanf(argv[2], "%d", &i);
        printf("I am checking to see if %d is prime.\n", i);

        if (is_prime(i , stream))
            printf("yes\n");
        else
            printf("no\n");
          
    /* Done, flush and close */
    fclose(stream);
    exit (0);
}

