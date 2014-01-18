#include <stdio.h>
#include <math.h>

/* This program calculates fibonacci sequence using binet formula

 1 1 2 3 5 8 13 21 34
 
 Starting with 1
 Each number in the sequence is created by adding the previous two numbers in sequence.
 
*/

long double myphi = 0;
long double myalpha = 0;

long double phi(long double i) {
  return (powl( myphi, i) );
}

long double alpha(long double i) {
  return (powl( myalpha, i) );
}

long double fib(long double i){

  long double p = phi(i);
  long double a = alpha(i);
  return ( ( p - a )/sqrtl(5));
}

int
main(){

  long double i;

  myphi = (1+ sqrtl(5))/2;
  myalpha = (1- sqrtl(5))/2;

  for (i = 1; i<1000; i++)
     printf ("value is %.0Lf and return value is %.0Lf\n", i, fib(i)); 

}
