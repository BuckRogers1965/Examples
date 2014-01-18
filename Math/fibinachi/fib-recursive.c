#include <stdio.h>

/* This program calculates fibonacci sequence using recursion

 1 1 2 3 5 8 13 21 34
 
 Starting with 1
 Each number in the sequence is created by adding the previous two numbers in sequence.
 
*/


long double fib(long double value){
  if (value <= 2)
    return 1;
    
  return (fib(value-1) + fib (value-2));
}

int
main(){

long double i;

  for (i = 1; i<1000; i++)
     printf ("value is %.0Lf and return value is %.0Lf\n", i, fib(i)); 

}
