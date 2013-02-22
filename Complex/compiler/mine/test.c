#include <ctype.h>
//program Cradle;

// Constant Declarations
#define MAX_BUF 1024

// Variable Declarations

char Look;					// Lookahead Character
char Looktmp;					// Lookahead Character

char Name[MAX_BUF];
char Number[MAX_BUF];
										
// Read New Character From Input Stream
int GetChar()
{
	Look = getchar();
}

// Report an Error
int Error(char * s)
{
	printf("\nError: %s.\n", s);
}

// Report Error and Halt
int Abort( char * s)
{
	Error(s);
	exit(1);
}

// Report What Was Expected
int Expected(char * s)
{
	char msg[MAX_BUF];
	sprintf(msg, "%s Expected", s);
	Abort(msg);
}

// Recognize an Alpha Character
int IsAlpha(char c)
{
	return (isalpha(c));
}
										
// Recognize a Decimal Digit
int IsDigit(char c)
{
	return (isdigit(c));
}

// Recognize an Alphanumeric
int IsAlNum(char c)
{
	return (isalnum(c));
}

// Recognize White Space
int IsWhite(char c)
{
	if (Look == '\n')
		return (0);
	return (isspace(c));
}

// Skip Over Leading White Space
void SkipWhite()
{
   while (IsWhite(Look))
      GetChar();
}

// Match a Specific Input Character
int Match( char x )
{
	char x1[2];
	x1[0]=x;
	x1[1]='\0';

	if (Look != x) 
		Expected(x1);

	GetChar();
	SkipWhite();
}

// Get an Identifier
char * GetName()
{
	int count=0;

	if (!IsAlpha(Look)) 
		Expected("Name");

	while (IsAlNum(Look) && (count < MAX_BUF))  {
		Name[count]=Look;
		GetChar();
		count++;
		Name[count]='\0';
	}

	SkipWhite();
	return (Name);
}

// Get a Number
char * GetNum()
{
	int count=0;

	if (!IsDigit(Look)) 
		Expected("Integer");

	while (IsDigit(Look) && (count < MAX_BUF))  {
		Number[count]=Look;
		GetChar();
		count++;
		Number[count]='\0';
	}

	SkipWhite();
	return (Number);
}

// Output a String with Tab
int EmitTab()
{
	printf("	");
}

// Output a String with Tab
int Emit(char * s)
{
	printf("%s", s);
}

// Output a String with Tab and CRLF
int EmitLn(char * s)
{
	Emit(s);
	printf("\n");
}

// Initialize
int Init(){
	GetChar();
	SkipWhite();
}

// Parse and Translate an Identifier

int Ident()
{
char * Name;

	Name = GetName();

	 if (Look == '(') {
		  Match('(');
		  Match(')');

		EmitTab();
		Emit("BSR ");
		EmitLn(Name);
	} else {
		EmitTab();
		  Emit("MOVE ");
		  Emit(Name);
		  EmitLn("(PC),D0");
	}
}

// Parse and Translate a Math Factor
int Factor()
{

	char * num;

	if (Look == '('){
		Match('(');
		Expression();
		Match(')');
	} else if (IsAlpha(Look)){
		Ident();
	} else {
		num=GetNum();
	
		EmitTab();
		Emit("MOVE #");
		Emit(num);
		EmitLn(",D0");
	}
}

// Recognize and Translate a Multiply
int Multiply()
{
	Match('*');
	Factor();
	EmitTab();
	EmitLn("MULS (SP)+,D0");
}

// Recognize and Translate a Divide
int Divide()
{
	Match('/');
	Factor();
	EmitTab();
	EmitLn("MOVE (SP)+,D1");
	EmitTab();
	EmitLn("DIVS D1,D0");
}

// Parse and Translate a Math Term
int Term()
{
	Factor();
	while (Look == '*' || Look == '/') {
		EmitTab();
		EmitLn("MOVE D0,-(SP)");
		switch (Look) {
		 case '*':
			Multiply();
			break;
		 case '/':
			Divide();
			break;
		default:
			Expected("Mulop");
		}
	}
}

// Recognize and Translate an Add
int Add()
{
	Match('+');
	Term();
	EmitTab();
	EmitLn("ADD (SP)+,D0");
}

// Recognize and Translate a Subtract
int Subtract()
{
	Match('-');
	Term();
	EmitTab();
	EmitLn("SUB (SP)+,D0");
	EmitTab();
	EmitLn("NEG D0");
}

// Recognize an Addop

int IsAddop(char c)
{
	return (Look == '+' || Look == '-');
}

// Parse and Translate an Expression
int Expression()
{
	if (IsAddop(Look)){
		EmitTab();
		EmitLn("CLR D0");
	} else
		Term();

	while (IsAddop(Look)){
		EmitTab();
		EmitLn("MOVE D0,-(SP)");
		switch(Look) {
	 	case '+':
			Add();
			break;
	 	case '-':
			Subtract();
			break;
		default:
			Expected("Addop");
		}
	}
}

// Parse and Translate an Assignment Statement

void Assignment ()
{
	char * Name;

	Name = GetName();
	Match('=');
	Expression();

	EmitTab();
	Emit("LEA ");
	Emit(Name);
	EmitLn("(PC),A0");

	EmitTab();
	EmitLn("MOVE D0,(A0)");
}

int main () {
	Init();
	Assignment();
	if (Look != '\n')
		Expected("Newline");
}


