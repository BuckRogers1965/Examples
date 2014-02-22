

#include <stdio.h>

int iseven(unsigned long  x){

    if (x & 1)
        return 0;

    return 1;
}

int main (){


    unsigned long x, y, z;
    unsigned long maxz = 0,
                  maxy = 0;


    for (y=1; y<1000001; y++, y++){
        x=y;
        z=1;
        while (x != 1){

            z++;

	    //if (iseven(x))
	    if (!(x&1))
		x=x/2;
	    else
		x=x*3+1;
	}
        if (z > maxz){
           maxz = z;
           maxy = y;
        }
    }
    printf ("Max z %lu at  %lu\n", maxz, maxy);
}
