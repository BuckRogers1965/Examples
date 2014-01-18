

#include <stdio.h>


int main () {


  int i, j, k;

  for (i = 1, j = 0, k =1 ; k<100; k++, i++, i++, i++, i++, i++ ){
    j+=i;
    printf("%d  %d  %d  %d \n", k, i, j, (5*k*k-3*k)/2);
  }

}
