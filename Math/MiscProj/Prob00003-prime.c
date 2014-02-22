#include <stdio.h>
#include <math.h>

int
divides(long double first, long double second){
  unsigned long r =  remainderl(second, first);
  if (r == 0.0)
	return 1;
  else
      return 0;
}


void
findprime (long double find){

  printf("Factors of %0.0Lf are ", find);
  long double i;
  int count = 0;
  long double max = sqrtl(find) +2 ;
  int factor_count = 0;
  for ( i = 2 ; i <= max;  i++, i++){
    loop:
    factor_count++;
    if (divides(i, find)) {
        count ++;
        if (count <2)
	  printf("%0.0Lf", i);
        find = find/i;
        goto loop;
    } 
    if (count > 1)
	printf("^%d ", count);
    else
      if (count ==1)
        printf(" ");
    count = 0;
    if (i==2)
       i=1;
  }
  if (find != 1) printf("%0.0Lf", find);
  printf("\n");
}

void
main (){
  long double i;

  findprime(600851475143);
  findprime(256);
  findprime(32);

  printf("\n");
  for (i = 2; i<21 ; i++)
    findprime(i);
}
