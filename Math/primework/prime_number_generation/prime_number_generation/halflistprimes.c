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

    printf("2\n");

    for(i=3; i<MAXSIZE; i++,i++)
        if (is_prime(i , stream))
            printf("%d\n", i);
          
    /* Done, flush and close */
    fclose(stream);
    exit (0);
}

