#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define PREC 2560

void
print(char *s, mpf_t x){
  printf("%s: ", s);
  mpf_out_str (stdout, 10, 1000, x);
  printf("\n");
  fflush(stdout);
}

#define START 1000000000000.0
int check(mpf_t n){

//  print("n", n);

  mpf_t b;
  mpf_init2(b, PREC);
  mpf_set_ui(b, 5);
  mpf_div_ui(b, b, 10);
   
 // print("bb", bb);

  mpf_t srpf;
  mpf_init2(srpf, PREC);
  mpf_sqrt(srpf, b);

  //print("srpf", srpf);

  mpf_mul(b, srpf, n);
  mpf_add_ui(b,b, 1);
  mpf_floor(b, b);

 // print("b", b);

  mpf_t n1, b2;
  mpf_init2(n1, PREC);
  mpf_init2(b2, PREC);

  mpf_set(n1, n);
  mpf_sub_ui(n1,n1, 1);
 // print("n1", n1);

  mpf_set(b2, b);
  mpf_sub_ui(b2, b2, 1);
 // print("b1", b2);

  mpf_t res;
  mpf_init2(res, PREC);
  mpf_div(res, b, n);
  mpf_mul(res, res, b2);
  mpf_div(res, res, n1);

  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_mul_ui(res,res,1000000);
  mpf_add_ui(res,res, 1);
  mpf_floor(res, res);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
  mpf_div_ui(res,res,1000000);
//  print("res", res);

//  printf("%d %0.30f  %0.30f \n",  mpf_get_d (res)==0.5, 0.5, mpf_get_d (res));


  mpf_clears(srpf, n1, b2, NULL);

  if (!mpf_cmp_d (res,0.5)){
  print("b", b);
    mpf_clears(b, res, NULL);
    printf(" match  .\n");
  //printf("\n");
    return 1;
  } else {
    mpf_clears(b, res, NULL);
//  printf("\n");
 //   printf(" nope.\n");
    return 0;
  }
}

int
main () {

  long double i ;

  mpf_t n;
  mpf_init2(n, PREC);

//  mpf_set_ui(n, 22);

  mpf_set_d(n, 1070379000000);
//  mpf_set_d(n, 1000000000000);
  //mpf_pow_ui(n,n,12);

  while(!check (n)) {
    mpf_add_ui(n, n, 1);
  }

  printf("Solution is %0.0f\n", mpf_get_d (n));
}
