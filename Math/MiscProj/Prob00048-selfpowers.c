#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void
printlast(int length, mpz_t x){
  int slen; 
  char s[10000];
  mpz_get_str (s, 10, x);
  slen = strlen(s);
  if (length >= slen)
      printf("%s", s);
  else
      printf("%s", s+slen-length);

  printf("\n");
}

int
main () {

  int i;
  mpz_t n, tot;

  mpz_init(n);
  mpz_init(tot);
  mpz_set_ui(tot, 0);

  for (i=1; i<=1000; i++ ){
    mpz_set_ui(n, i);
    mpz_pow_ui(n,n,i);
    mpz_add(tot, tot, n);
  }

  printf("Solution is " );
  printlast (10, tot);

}
