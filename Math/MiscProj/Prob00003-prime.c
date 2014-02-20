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
main (){

  long double  find = 600851475143;
  //long double  find = 256;
  printf("Factors of %0.0Lf are ", find);
  long double i;
  int count = 0;

  for ( i = 2 ; i < 50000;  i++, i++){
    loop:
    if (divides(i, find)) {
        count ++;
        find = find/i;
        if (count <2)
	  printf("%0.0Lf", i);
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
  printf("\n");
}
