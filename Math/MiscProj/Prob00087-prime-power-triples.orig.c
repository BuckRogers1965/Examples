#include <stdio.h>
#define MAXSIZE  7072
#define TARGET 50000000
#include "prime.c"

main(int argc, char *argv[]){

    long long  i, j, k;
    long count = 0;
    char *found  =  calloc (1, TARGET+1); 
    long long res;

    InitSieve();

    for (i=2; i<MAXSIZE; i++){
      if (is_prime(i)){
        for (j=2; j<MAXSIZE; j++){
          if (is_prime(j)){
            for (k=2; k<MAXSIZE; k++){
              if (is_prime(k)){
                res = i*i + j*j*j + k*k*k*k;
                if (res >= TARGET) break;
                if (!found[res]) {
                  count++; 
                  found[res]=1;
                } 
              }
            }
          }
        }
      }
    }
    printf("Solution is %lu \n",count);
}

