#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000000
#include "prime.c"

// you must define  MAXSIZE before you call this function to the range
// that you wish to use prime numbers in. 


int
match (char s[]){
  int i;
  int x;
  int n = 0;
  int savei;
  char number[100];
  for (i=0; i<10; i++) {
    sprintf(number, s, i,i,i);
    //printf("\n");
    sscanf(number, "%d", &x);
    if (x<1000)
      break;
    if (is_prime(x)) {
//      printf("> %d  %d\n",i, x);
      if (n==0)
        savei=i;
      n++;
    }
    if (n > 7) {
     printf("found!!!  ");
     printf(s, savei, savei, savei);

     exit (0);
    }
  }

 return 0;

}

char pat[7][50] = {
    "%%d%%d%%d%d%d%d\n",
    "%%d%%d%d%%d%d%d\n",
    "%%d%%d%d%d%%d%d\n",
    "%%d%d%%d%d%%d%d\n",
    "%%d%d%d%%d%%d%d\n",
    "%d%%d%d%%d%%d%d\n",
    "%d%d%%d%%d%%d%d\n"
  };

int 
test (int a, int b, int last){

  int i;
  char s[100];

  for (i=0; i<7; i++) {
    sprintf(s, pat[i], a, b, last);
    match(s);
  }
}

int
main (){

  int i,j,k;
  int lastd[4] = {1, 3, 7, 9}; 
  
  InitSieve () ;

  for (i=0; i<9; i++)
    for (j=0; j<10; j++)
      for (k=0; k<4; k++)
          test(i, j, lastd[k]);

  exit (0);
}

