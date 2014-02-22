#include <stdio.h>

int maxp = 0;
int maxc = 0;

void
f (int p) {
  int a, b, c;
  int count = 0;

  printf ("p %d ", p);
  for (a=1; a < p ; a++)
    for (b=a; b<(p-a); b++){
       c = p-a-b;
       if ( (a*a + b*b) == c*c) {
            count ++;
            printf ("{%d, %d, %d}, ", a, b, c);
       }
    }

   if (count > maxc){
      maxp = p;
      maxc = count;
   }
   printf("\n");
}

void
main () {
  int i;
  
  for (i=3; i<1001; i++)
    f(i);

  printf("\nMax int right triangals for a given p %d is:\n", maxp);
  f(maxp);
}
