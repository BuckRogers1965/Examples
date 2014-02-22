#include <stdio.h>
#define MAXBUFF 1024

int
isPal(int size, int value){

   char test[MAXBUFF];
   int i;

   snprintf(test, MAXBUFF, "%d", value);

   for (i=0; i< size ; i++){
      if (test[i] != test[size*2-1-i])
	return 0;
   }
   return 1;
}

long
retMax(long a, long b){
  if (a> b) return a;
  else      return b;
}

long
findPal (int size){

  long maxSize =1;
  long result = 0;
  int i, j;
  for (i=0; i<size; i++)
	maxSize*=10;
//  printf("%ld\n", maxSize);
//  for (i=maxSize-1; i>(1); i--) 
//    for (j=maxSize-1 ;j>(1); j--){

  for (i=maxSize-1; i>(maxSize * .9 ); i--) 
    for (j=i ;j>(maxSize *.9 ); j--){
        long test;

        test = i*j;
        if (isPal(size, test)) {
//          printf("%d x %d = %ld\n", i, j, test);
          result = retMax(test, result);
        }
    }
    fflush(stdout);
    return result;
}

void
main (){

  printf ("Result for  2 digit numbers is %ld \n", findPal (2));
  printf ("Result for  3 digit numbers is %ld \n", findPal (3));
  printf ("Result for  4 digit numbers is %ld \n", findPal (4));
  printf ("Result for  5 digit numbers is %ld \n", findPal (5));

}
