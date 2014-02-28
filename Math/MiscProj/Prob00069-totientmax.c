#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
	This program is written to calculate the primes in the first billion
        numbers.

	Written by James M. Rogers
	04 May 1999
*/

#define MAXSIZE  10000000

int
divides(long double first, long double second){
  long double r =   second/first;
  if (floorl (r) == r)
      return 1;
  else
      return 0;
}

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

int is_prime(unsigned long i) {

    ldiv_t results;
    char   c;

    // updated to check for even
    if ( i%2 == 0 ) {
      if (i==2)
        return 1;
      else
        return 0;
    }

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

unsigned long min (unsigned long i, unsigned long j){
    return  i<j?i:j;
}

unsigned long max (unsigned long i, unsigned long j){
    return  i>j?i:j;
}

int
common(unsigned long b, unsigned long a){

  unsigned long i;

  for (i=2; i<min(a,b); i++)
     if(is_prime(i)){
     int ax, bx;
     ax = divides(i,a); 
     bx = divides(i,b);

     //printf (" %lu %lu  %d   %lu  %lu %d  ", a, i, ax, b, i, bx);
     if ( ax & bx) {
        //printf(" true, common \n");
        return 1;
     }
    //printf("\n");
  }
  //printf(" false, no common \n");
  return 0;
}

main(int argc, char *argv[]){

    unsigned long        i;
    unsigned long        j;
    unsigned long        k;
    unsigned long        qn;
    div_t	results;
    int         c;

    /*
          Initialize the array
    */

    for(i=0;i<MAXSIZE/16;i++) {
        z[i]='\xFF';
    }


    /* For loop is the main loop that controls the function of the program */
    for(i=3;i<MAXSIZE; i+=2)
        if (is_prime(i)) 
            set_matrix(i);
          
 //  used to store the array to a file for later reuse.
 //   /* Done, flush and close */
 //   for (i=0; i<MAXSIZE/16;i++)
 //        putc(z[i], stdout);

/*

    if(is_prime(2))
       printf("2 is prime\n");

    if(is_prime(4))
       printf("4 is prime\n");

    if(is_prime(8))
       printf("8 is prime\n");

    if(is_prime(11))
       printf("11 is prime\n");

    if(is_prime(9))
       printf("9 is prime\n");

    if(divides(3,9))
       printf("3 divides into 9\n");

    if(divides(9,3))
       printf("9 divides into 3\n");

    if(common(5,7))
       printf("5 and 7 have common divisors\n");

    if(common(2,6))
       printf("2 and 6 have common divisors\n");
    if(common(4,6))
       printf("4 and 6 have common divisors\n");

*/

  unsigned long maxn = 0;
  unsigned long maxqn = 0;

    for (i=500000; i<1000000; i++){
      if (!is_prime(i)){
          qn=0;
          //printf("%lu\t", i);
          for (j=1; j<i; j++) {
             if (!common(j,i)){
                    qn++;
                    //printf("%lu ", j);
                 } 
          }
          if (i/qn > maxqn){
             maxqn = i/qn;
             maxn = i;
             printf("New max %lu for %lu  at %lu\n", maxqn, maxn, i);
          }
          //printf("\t%lu  %0.9Lf ", qn, (long double) i/qn);
      }
      //printf("\n");
      printf(".");
      fflush(stdout);
    }

  finished:
    printf("Solution is %lu for %lu  searching through %lu\n", maxn, maxqn, i);
    exit (0);

}

