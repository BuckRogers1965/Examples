#include <stdlib.h>
#include <math.h>

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

void InitSieve (){

    unsigned long i;

    /* Initialize the array */
    for(i=0;i<MAXSIZE/16;i++) {
        z[i]='\xFF';
    }

    /* clear bits to make table */
    for(i=3;i<MAXSIZE; i+=2)
        if (is_prime(i)) 
            set_matrix(i);
}

