#include <ctype.h>
//program Cradle;

// Constant Declarations
#define MAX_BUF 1024

// Variable Declarations

char Look;					// Lookahead Character
char Token[MAX_BUF];
int Table[26];

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

// Get a Number
long GetNum()
{
	int count=0;

	if (!IsDigit(Look)) 
		Expected("Integer");

	while (IsDigit(Look) && (count < MAX_BUF))  {
		Token[count]=Look;
		GetChar();
		count++;
		Token[count]='\0';
	}

	SkipWhite();
	return (atoi(Token));
}

// Get an Identifier
char * GetName()
{
    int count=0;

    if (!IsAlpha(Look))
        Expected("Name");

    while (IsAlNum(Look) && (count < MAX_BUF))  {
        Token[count]=Look;
        GetChar();
        count++;
        Token[count]='\0';
    }

    SkipWhite();
    return (Token);
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

	int i;

	GetChar();
	SkipWhite();

	// initialize all the variables to 0
	for (i=0; i<26; i++)
		Table[i]=0;
}

int Expression();

// Parse and Translate a Math Factor
int Factor()
{
	int Value;
	char * Name;

	if (Look == '('){
		Match('(');
		Value = Expression();
		Match(')');
		return (Value);
	} else if (IsAlpha(Look)) {
		Name = GetName();
		return (Table[toupper(Name[0])-'A']);
	} else
		return (GetNum());
}

// Parse and Translate a Math Term
int Term()
{
	int Value = Factor();

	while (Look == '*' || Look == '/') {

		switch (Look) {
		 case '*':
			Match('*');
			Value = Value * Factor();
			break;

		 case '/':
			Match('/');
			Value = Value / Factor();
			break;
		}
	}

	return (Value);
}

// Recognize an Addop
int IsAddop(char c)
{
	return (Look == '+' || Look == '-');
}

// Parse and Translate an Expression
int Expression()
{
	int Value = 0;

	if (!IsAddop(Look)) 
		Value = Term();

	while (IsAddop(Look)) {
		switch (Look) {
		case '+': 
			Match('+');
			Value = Value + Term();
			break;

		case '-':
			Match('-');
			Value = Value - Term();
			break;
		}
	}
   return (Value);
}

// Parse and Translate an Assignment Statement
int Assignment()
{
	char * Name;

	Name = GetName();
	Match('=');
	Table[toupper(Name[0])-'A'] = Expression();
}

//Input Routine
void Input ()
{
	char * Name;

	Match('?');
	Name = GetName();
	printf("%d\n", Table[toupper(Name[0])-'A']);
}

//Output Routine
void Output()
{
	char * Name;

	Match('!');
	Name = GetName();
	printf("%d\n", Table[toupper(Name[0])-'A']);
}

// Main
int main () {
	Init();
	while (Look != '.') {
		switch (Look){
		case '?':
			Input();
			break;
		case '!':
			Output();
			break;
		default:
        	printf("%d\n", Assignment());
		}
		Match ('\n');
	}
}


