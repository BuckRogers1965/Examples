#include <stdio.h>

void
main (){
           // 3  5  6  9  10  12  15
  int d[] = { 3, 2, 1, 3, 1, 2, 3 };
  int max_m = 6;
  register int m;
  register int i;
  register int result;

  // testing loop to see how efficient algoryth is
  //int j;
  //for (j = 0; j< 10000; j++)

  for (i=3, m=1, result = 0; i<1000; i=i+d[m], m++ ) {
    if (m>max_m)
       m=0;
    result+=i;
  }
  printf("%d \n", result);
}
