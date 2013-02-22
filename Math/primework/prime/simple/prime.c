#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*

	This program is written to calculate the primes in the first billion
        numbers.

	Written by James M. Rogers

	04 May 1999


Ideas for the future of this project:

Make the program work at the bit level to store 8 numbers per byte, right
now it is wasting 7 bits per byte.

Write a standalone program/server that when given a number will lookup the
number in one or more compressed blocks of 100,000 bytes. Make it so that
this server can also connect to a master server and report the range(s) of
primes that it is able to recognize.

Rewrite the function so that it will generate blocks of numbers and then
compress them using bz2.  The current prime is stored in a filename.ptr
file so that if the program is stopped it can restart from were it left
off.(resume)  When the local prime server has processed a file as much as
it can it is passed to another server who is registered as having the next
consecutive block.

If you had a 10,000 machines each with 1GB of free harddrive then you could
basically serve the first 400000000000000000 numbers, saying if any of these
numbers was prime.

Given a number, give me the next prime number, if you reach the end of your
scale pass a value back to the main server asking for the prime that follows
MAXSCALE + 1.

Given a number return the factors of that number.
First, check to see if the number is greater than the square of your largest
prime.  If it is then you cannot factor it.  Return an error stating this.
See if the number is prime.  If so, return one and the number.
Otherwise the hard work begins.
     use given prime.
     If number is divisible by the prime without remainder {
         recusively call factor with the current prime and the product.
         return the value when it is returned to you, tack on your prime
     } else {
         get the next prime and start jump back upto 'use given prime'
     }

 

*/

#define MAXSIZE  1002
#define NUMPRIMES 10

int known_primes[NUMPRIMES]={ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

isprime(long int thenumber)
{
        int isitprime=1,loop;
        for(loop=3 ; (isitprime) && (loop<(sqrt(thenumber)+1)) ; loop+=2)
                isitprime = (thenumber % loop);
        return(isitprime);
}

void set_not_prime(unsigned long i, FILE *stream) {

    if(fseek(stream, i, SEEK_SET)) {
        printf("Failed to fseek to %d during set_not_prime.\n", i);
	exit (1);
    }
    fputc('\000', stream);
}

int is_prime(unsigned long i, FILE *stream) {

    if(fseek(stream, i, SEEK_SET)) {
        printf("Failed to fseek during is_prime\n");
	exit (1);
    }
    return (int) fgetc(stream);
}

void set_matrix(unsigned long i, FILE *stream) {

    unsigned long    j;

    printf("%d\n", i);
    fflush(stdout);

    for(j=i;j<(MAXSIZE/i+1);j++,j++) {
        if (isprime(j)){
            set_not_prime(j*i, stream);
        }
    }
}

main(int argc, char *argv[]){

    unsigned long        i;
    div_t	results;
    int         c,
                j;
    FILE        *stream;    /* need a stream pointer of type FILE */ 

    /* ensure that the filename in argv[1] exists and is a file */

    /* open the file designated on the command line */
    if (!(stream = fopen(argv[1], "w+"))){
	printf("Failed to open the designated file, I am quiting.\n");
	exit (1);
    } 

    /* Initialize the file, quit if we cannot write all the way to the end 
       Because this takes so long on huge databases, I am going to 
       initialize the first several primes as I go along.  I mean, everyone
       knows that 2, 3, 5, and 7 are prime...
    */

    fputc('\000', stream);
    fputc('\000', stream);
    fputc('\001', stream);
    fputc('\001', stream);
    fputc('\000', stream);
    for(i=5;i<MAXSIZE;i++,i++) {

        c=1;

        for (j=0; j<NUMPRIMES; j++) {
            results=div(i, known_primes[j]);
            if (results.rem<1){
                if (i>known_primes[j])
                    c=0;
            }
        }

        fputc(c, stream);
        fputc('\000', stream);
    }

    for (j=0; j<NUMPRIMES; j++)
        printf("%d\n", known_primes[j]);

    /* For loop is the main loop that controls the function of the program */
    for(i=31;i<MAXSIZE; i++,i++)
        if (is_prime(i, stream)) 
            set_matrix(i, stream);
          
    /* Done, flush and close */
    fflush(stream);
    fclose(stream);
    exit (0);
}

