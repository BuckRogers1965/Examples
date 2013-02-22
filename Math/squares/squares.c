#include <stdio.h>

main () {

    long int x, y, z;

    y=0;
    z=1;
    for (x=1;x<46340;x++,z=z+2) {
       printf("%d^2  = %d\n", x, y=y+z);
    }

}
