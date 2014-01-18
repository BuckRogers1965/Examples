

#include <stdio.h>

int iseven(unsigned long  x){

    if (x & 1)
        return 0;

    return 1;
}

int main (){


    unsigned long x, y, z;

    for (y=1; y<10000000; y++){
        x=y;
        z=1;
        while (x != 1){

            z++;

	    if (iseven(x))
		x=x/2;
	    else
		x=x*3+1;
	}
	printf ("%lu %lu\n", y, z);
    }

}
