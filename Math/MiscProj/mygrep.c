#include <stdio.h>

int matchhere(char * srch, char * msg){

  if (srch[0] == 0) return 1;

  if (srch[0] == '*')
    return grep(srch+1, msg);

  if( msg[0] != 0  && ( srch[0] == '.' || srch[0] == msg[0])  ) 
      return matchhere (srch+1, msg+1);

  return 0;
}

int grep(char * srch, char * msg) {

 // printf("%s\n%s\n", srch, msg);
  int n = 1;
  if (srch[0] == '^')
     return matchhere(srch+1, msg);

  for (; msg[0] != 0; *msg++, n++) 
    if (matchhere (srch, msg))
      return n;

  return 0;
}

int
searchTest (char * srch, char * msg, int correct) {
  printf("  Search <%s>  in Message <<%s>> ", srch, msg);
  int result = grep (srch, msg);
  if (result)
    printf("Found ");
  else
    printf("Not Found ");
  if (result == correct) 
    printf("Passed\n");
  else
    printf("*** Failed ****\n");

  return !(result ^ correct);
}

void
unitTest ()
{
  int passed = 0;
  int count = 0;

  printf("\nThis is a test of my implementation of grep.\n\n");

  passed += searchTest ("th*st", "this is the besk", 0);
  count++;

  passed += searchTest ("th*st", "this is the best", 1);
  count++;

  passed += searchTest ("the ", "this is the best", 1);
  count++;

  passed += searchTest ("the ", "ahis is ake best", 0);
  count++;

  passed += searchTest ("t.e ", "this is the best", 1);
  count++;

  passed += searchTest ("^the ", "this is the best", 0);
  count++;

  passed += searchTest ("^this ", "this is the best", 1);
  count++;

  printf("\n  This test will report failed, but is counted as passed:\n");
  passed += !searchTest ("elephant", "this is the best", 1);
  printf("  This is a test of the reporting mechanism\n");
  count++;

  printf("\nPassed %d of %d tests\n\n", passed, count);
}

