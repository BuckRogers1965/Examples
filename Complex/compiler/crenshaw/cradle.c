#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
void exit( int exit_code );

void EmitLn(char *);

#define TAB = '\t';

char *Look;  /* Lookahead Character */
                              
void GetChar() {
   Look++;
}

void Error(char *s) {
   printf ("Error %s.", s);
   EmitLn("");
}

void Abort(char *s){
   Error(s);
   exit (1);
}


void Expected(char * s){
   printf("%s", s);
   Abort("Expected");
}

void Match(char x){
   if (Look[0] == x)
      GetChar();
   else {
      char error[4];
      error[0]='\'';
      error[0]=x;
      error[0]='\'';
      error[0]='\0';
      Expected(error);
   }
}


int IsAlpha(char c){
   return isalpha(c);
}
                              

int IsDigit(char c){
   return isdigit(c);
}

char GetName(){
   char GetName;
   if (!IsAlpha(Look[0]))
	Expected("Name");
   GetName = Look[0];
   GetChar();
   return GetName;
}

char GetNum (){
   char GetNum;
   if (!IsDigit(Look[0]))
	Expected("Integer");
   GetNum = Look[0];
   GetChar();
   return GetNum;
}

void Emit(char *line){
   printf ("\t%s", line);
}

void EmitLn(char *line){
   Emit(line);
   printf ("\n");
}

void Init(char *s){
	Look=s;
}


void parenPermutations(char *s){
   	Init(s);
}

int
main (){

	parenPermutations("1 + 2 - 3 * 4");
	parenPermutations("1 - 1 + 1");
	parenPermutations("10");
	parenPermutations("1 + 2 + 3 * 4 - 5 * 2");
}
