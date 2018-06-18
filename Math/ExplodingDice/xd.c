

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <time.h>


int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }


    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

long xplod (int sides, int offset, long r) {

	long result; 

	result = random_number(1,sides);
  	//printf("		result %ld\n", result);

	if (result < sides) 
		return(r + result + offset);
	else
		return (xplod(sides, -1, r + result + offset));
	
}

int main () {


  long i, j, n, x, r;

  double t, z;

	z=10000000; t=0;

    srand(time(NULL));

  for (i=0; i < z; i++) {
	r = xplod(6, 0, 0);
	t += r;
	if (r>10)
  		printf("%ld\n", r);
	//else 
  	//printf("\n");

    //srand(time(NULL)+t);

  }

 	printf("Total  %f	Average %f\n", t, t/z);
 
}
