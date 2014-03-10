#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFF 3000

void
itoa (int value, char *sp, int radix)
{
  char tmp[MAXBUFF];		// be careful with the length of the buffer
  char *tp = tmp;
  int i;
  unsigned v;
  int sign;

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned) value;

  while (v || tp == tmp)
    {
      i = v % radix;
      v /= radix;
      if (i < 10)
	*tp++ = i + '0';
      else
	*tp++ = i + 'a' - 10;
    }

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;

  *sp = 0;
}

/*
look into this non string comparison:
from here: http://www.mathblog.dk/
project-euler-36-palindromic-base-10-2/
*/
int isPal(int n, int b){
    int r = 0;
    int k = n;
 
    while (k > 0) {
        r = b * r + k % b;
        k /= b;
    }
    return n == r;
}

int
isPalStr (int n, int radix)
{

  char s[MAXBUFF];
  int i;
  int size;
  int offset;

  itoa (n, s, radix);
  size = strlen (s);
  if (size == 1)
    return 1;

  if (size % 2 == 0)
    {
      size = size / 2;
      offset = -1;
    }
  else
    {
      size = size / 2;
      offset = 0;
    }
//   printf(">>> %ld %s len %d\n", n, s, size);
  for (i = 0; i < size; i++)
    {
      if (s[i] != s[size * 2 + offset - i])
	return 0;
    }
  return 1;
}

#define MAX 1000000

int
main ()
{

  int i;
  long long r = 0;
  for (i = 1; i <= MAX; i++, i++)
    {
      if (isPal (i, 10) && isPal (i, 2))
	{
	  r = r + i;
	}
//    printf("%d %d %d \n", i, isPal(i,10), isPal(i,2));
//    printf ("\n");
    }

//  printf("%d %d %d\n", 585, isPal(585,10), isPal(585, 2));

  printf ("Solution is %lld\n", r);
  exit (0);
}
