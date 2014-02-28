#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "roman.h"

enum roman_numerals { I = 0, V = 1, X = 2, L = 3, C = 4, D = 5, M = 6 };

  int rn[2][7] =
      {{'I', 'V', 'X',  'L',  'C',   'D',   'M' },
        {1,   5,   10,   50,   100,   500,   1000}};

  int nr[]= { 0,0,100,500,0,0,0,0,1,0,0,50,1000,0,0,0,0,0,0,0,0,5,0,10,0,0 };
  int nr2p[] = { 9, 22, 24, 12, 3, 4, 13 };

char *Look;  /* Lookahead Character */
                              
void GetChar() {
   Look++;
}

long A (char x){
  long res = 0;
  while (Look[0] == x){
    res += nr[x-'A'];
    GetChar();
  }
  return res;
}

long De (){
  char curr = Look[0];
  long val = A(curr);

  if (!Look[0]) return val;
  if (nr[curr-'A'] < nr[Look[0]-'A'])  {
    return ( De() - val);
  } else {
    return ( De() + val);
  }
}

long decode (char *r) {
  Look = r;
  return De();
}

void En(long x, int i){
  if (x == 0 || i < 0) return;

  // takes as much as we can.
  while ( x >= rn[1][i]) {
     putchar(rn[0][i]);
     x -= rn[1][i];
  }

/* Only I, X, and C can be used as the leading numeral in part of a subtractive pair.
I can only be placed before V and X.
X can only be placed before L and C.
C can only be placed before D and M.
  int rn[2][7] = {{'I', 'V',   'X',  'L',    'C',   'D',   'M' },
                   {1,   5,     10,   50,     100,   500,   1000}};
   I see a 1 - 5 - 10 pattern
*/
  if (i==6 || i == 4 || i == 2) {
    long temp = rn[1][i] - rn[1][i-2];
    if (x>=temp) {
        x -= temp;
       putchar (rn[0][i-2]);
       putchar (rn[0][i]  );
    }
  }
  if (i==5 || i == 3 || i == 1) {
    long temp = rn[1][i] - rn[1][i-1];
    if (x>=temp) {
        x -= temp;
       putchar (rn[0][i-1]);
       putchar (rn[0][i]  );
    }
  }

  En(x, --i);
}

void encode (long x){
  En(x, 6);
  printf ("\n");
}

void
main () {
  printf("%d\n",   decode("LIIIVX"));
  exit (0);
  int i;
  for (i=0; i<1000; i++) {
    encode(decode(rom[i]));
  }
}
