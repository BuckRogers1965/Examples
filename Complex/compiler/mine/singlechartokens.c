//program Cradle;

// Constant Declarations

// Variable Declarations

char Look;					// Lookahead Character
char Looktmp;					// Lookahead Character
										
// Read New Character From Input Stream

int GetChar1()
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
	char msg[1024];
	sprintf(msg, "%s Expected", s);
	Abort(msg);
}

// Match a Specific Input Character

int Match( char x )
{

	char x1[2];
	x1[0]=x;
	x1[1]='\0';

	if (Look == x) 
		GetChar1();
	else
		Expected(x1);
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

// Get an Identifier

char GetName()
{
	if (!IsAlpha(Look)) 
		Expected("Name");
	Looktmp = Look;
	GetChar1();
	return (toupper(Looktmp));
}

// Get a Number }

char GetNum()
{
	if (!IsDigit(Look)) 
		Expected("Integer");
	Looktmp = Look;
	GetChar1();
	return (Looktmp);
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
	GetChar1();
}

// Parse and Translate an Identifier

int Ident()
{
char Name;

	char x1[2];

	Name = GetName();
	x1[0]=Name;
    x1[1]='\0';

    if (Look == '(') {
        Match('(');
        Match(')');

		EmitTab();
		Emit("BSR ");
		EmitLn(x1);
	} else {
		EmitTab();
        Emit("MOVE ");
        Emit(x1);
        EmitLn("(PC),D0");
	}
}

// Parse and Translate a Math Factor
int Factor()
{

	char x1[2];

	if (Look == '('){
		Match('(');
		Expression();
		Match(')');
   } else if (IsAlpha(Look)){
		Ident();
   } else {
		x1[0]=GetNum();
		x1[1]='\0';
	
		EmitTab();
		Emit("MOVE #");
		Emit(x1);
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

int main () {
	Init();
	Expression();
	if (Look != '\n')
		Expected("Newline");
}


