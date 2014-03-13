#include <stdio.h>
#include <stdlib.h>
#define LIMIT 28123

long sumofdiv(long n){
  long i, r = 0;
  if (n==2)
	return 1;
  if (n==0)
	return 0;
  for (i = 1; i <= (n/2)  + 1; i++)
    {
      if (n % i == 0)
        r += i;
    }
  return r;
}

int
main (){
  long i, j;
  long long  r = 0;
  long d[LIMIT+1][3];


  // clear array, just to be sure
  for (i=12; i<=LIMIT; i++) {
      d[i][0]=0;
      d[i][1]=0;
      d[i][2]=0;
  }

  // calculate array of sums of proper divisors
  int cA = 0;
  for (i=0; i<LIMIT; i++) {
    d[i][0] = sumofdiv(i);
    if (i<d[i][0]){
      d[i][1]=1;
      cA++;
    }
    else
      d[i][1]=0;
  }

  printf("Number of Abundent is %d\n", cA);
  
  cA = 0;
  // mark all that is the sum of two abundent numbers
  for (i=12; i<LIMIT; i++)
    if (d[i][1])
	for (j=i; j<LIMIT; j++) 
          if (d[j][1]) {
            r=i+j;
            if (r>LIMIT)
		break;
            if (!d[r][2])
              cA++;
            d[r][2]=1;
            
          }
  printf("Number of abundent sums is %d\n", cA);

  r=0;
  // finally total up the results
  for (i=0; i<LIMIT; i++)
    if (!d[i][2])
	r += i;

  printf("Solution is %lld\n", r);
/*
  for (i=0; i<100; i++)
    printf("sum of div for %ld is %ld  \tabnd  %ld \t%ld\n", i, d[i][0], d[i][1], d[i][2]);
*/
  exit(0);
}

