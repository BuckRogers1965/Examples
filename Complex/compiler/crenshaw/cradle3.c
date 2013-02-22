#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
void exit( int exit_code );

void EmitLn(char *);
void Expression();

#define TAB = '\t';

char *Look;  /* Lookahead Character */

                              
void GetChar() {
   Look++;
}

int IsWhite(char c){
   return isspace(c);
}

void SkipWhite (){
   while (IsWhite(Look[0])) 
      GetChar();
}

void Init(char *s){
   Look=s;
   SkipWhite();
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
   if (Look[0] == x){
      GetChar();
      SkipWhite();
   } else {
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
   SkipWhite();
   return GetName;
}

int GetNum (){
   int x=0;
   if (!IsDigit(Look[0]))
      Expected("Integer");
   while (IsDigit(Look[0])){
      x = x*10 + Look[0]-'0';
      GetChar();
   }
   SkipWhite();
   return x;
}

void Emit(char *line){
   printf ("\t%s", line);
}

void EmitLn(char *line){
   Emit(line);
   printf ("\n");
}


void parenPermutations(char *s){
   	Init(s);
}

void Factor(){
   if (Look[0] == '(') {
      Match('(');
      Expression();
      Match(')');
   } else {
      printf ("\tMOVE #%d,D0", GetNum() );
      EmitLn("");
   }
}

void Multiply() {
   Match('*');
   Factor();
   EmitLn("MULS (SP)+,D0");
}

void Divide(){
   Match('/');
   Factor();
   EmitLn("MOVE (SP)+,D1");
   EmitLn("DIVS D1,D0");
}


void Term (){
   Factor();
   EmitLn("MOVE D0,-(SP)");
   while (Look[0] == '*' || Look[0] == '/'){
      switch (Look[0]){
         case '*': Multiply();
              break;
         case '/': Divide();
              break;
         default: Expected("Mulop");
      }
   }
}


void Add(){
   Match('+');
   Term();
   EmitLn("ADD D1,D0");
}


void Subtract(){
   Match('-');
   Term();
   EmitLn("SUB D1,D0");
}

int IsAddop(char c){
    if ( c == '+' || c == '-')
      return 1;
   else
      return 0;
}

void Expression(){
   if (IsAddop(Look[0]))
      EmitLn("CLR D0");
   else
      Term();
   EmitLn("MOVE D0,D1");
   while (IsAddop(Look[0])){
      switch (Look[0]){
         case '+': Add();
	    break;
         case '-': Subtract();
	    break;
         default:
            Expected("Addop");
      }
   }
}


int
main (){

   Init("1");
   Expression();
   printf("\n");

   Init("2+1");
   Expression();
   printf("\n");

   Init("3*1");
   Expression();
   printf("\n");

   Init("(4+2)/((3+4)+(5-6))");
   Expression();
   printf("\n");

   Init("-5");
   Expression();
   printf("\n");

   Init(" ( 6 + 2 ) / ( ( 3 + 4 ) + ( 5 - 6 ) ) ");
   Expression();
   printf("\n");

   Init(" ( 777 + 23 ) / ( ( 43 + 49 ) + ( -50349 - 6235454 ) ) ");
   Expression();
   printf("\n");

   Init("a");
   Expression();
   printf("\n");

}
