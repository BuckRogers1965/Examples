#include <stdio.h>

/* This program calculates fibonacci sequence using recursion

 1 1 2 3 5 8 13 21 34
 
 Starting with 1
 Each number in the sequence is created by adding the previous two numbers in sequence.
 
 If you notice, something bad happens when we reach number 93 and we lose precision off the end.
 The number is close to the right number but is subtly wrong.
 
 We need to switch to a bignum library to add numbers that large precisely.
 
 Interestingly we can calculate the first thousand numbers in the sequence this way before we can calculate the first 30 numbers recursively.
 
*/


int
main(){

long double i, j, p1, p2;

  p1 = 0;
  p2 = 1;
  i  = 0;
  j = 1;
  
  while (j<1000){
    i = p1 + p2;
    printf ("\t%.0Lf\t%.0Lf\n", j, i);
    p2 = p1;
    p1 = i;
    j++;
  }

}
