#include <stdio.h>
#include <stdlib.h>

/*

	This program is written to use the database created by prime to
        say if a number is prime or not.

	Written by James M. Rogers

	04 May 1999


 

*/

#define MAXSIZE  1000002


int is_prime(unsigned long i, FILE *stream) {

    if(fseek(stream, i, SEEK_SET)) {
        printf("Failed to fseek during is_prime\n");
	exit (1);
    }
    return (int) fgetc(stream);
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

