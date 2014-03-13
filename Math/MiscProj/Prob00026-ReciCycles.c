#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "mygrep.h"

#define PREC 3350
#define LIMIT 1000

void
print(char *s, mpf_t x){
  printf("%s: ", s);
  mpf_out_str (stdout, 10, 1000, x);
  printf("\n");
  fflush(stdout);
}

#define SSIZE 10
int
cycle (mpf_t x) {

   char s[10000];
   char srch[SSIZE+1];
   int i;
   mp_exp_t e;
   mpf_get_str (s, &e, 10, 10000, x);
   
   // copy a search string
   for (i=0; i<SSIZE; i++)
     srch[i] = s[i+SSIZE]; 
   srch[i]='\0';

  return grep(srch, s+SSIZE+1);
}

int
main () {

  int i, ix, r, max = 500;

  mpf_t n;
  mpf_init2(n, PREC);

  for (i = LIMIT; i > 0; i--) {
    mpf_set_ui(n, 1);
    mpf_div_ui(n,n,i);
    r = cycle(n);
    if ( r>max) {
      ix = i;
      max = r;
      break;
    }
    //printf("%d for i %d\n", cycle(n), i);
  }

  mpf_set_ui(n, 1);
  mpf_div_ui(n,n,ix);
  printf("Solution is %d with  %d cycles\n", ix, cycle(n));
}
