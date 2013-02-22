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
//	printf("%c", Look);
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
//	if (Look == '\n')
//		return (0);
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

    while ((IsAlNum(Look) || (Look == '-')) && (count < MAX_BUF))  {
        Token[count]=Look;
        GetChar();
        count++;
        Token[count]='\0';
    }

    SkipWhite();
//	printf("[%s]\n", Token);
    return (Token);
}

// Initialize
int Init(){
	GetChar();
	SkipWhite();
}

void GetProperty (){
        Match('"');
        while ( Look!='"' )
                GetChar();
        Match('"');
}

// consume all the attributes, one at a time
void GetAttributes(){

	while (Look != '>' && Look != '/'){
		GetName();
		Match('=');
		GetProperty();
	}
}

// for now, skip the contents
void emptytag(){
   while (Look!='<')
      GetChar();
}

// get the tag name
char * tag(){
	return (GetName());
}

// <xml></xml>
void xml (char * c) {

	char opentag[MAX_BUF];

	// loop until we get the ending tag
	while (1){
		if (Look!='<'){
			// consume the stuff between the tags
			emptytag();
		} else {
			// we found the start of a tag, consume it
			Match('<');
			if (Look != '/') {
				// if we are an open tag
				strncpy(opentag, tag(), MAX_BUF);
				GetAttributes();
				if (Look == '/'){
					// self closing tag
					Match ('/');
					Match ('>');
				} else {
					// we just went in one more level
					// call yourself recursively
					// with the name of the closing tag to look for
					Match ('>');
					xml (opentag);
				}
			} else {
				// else we are a closing tag
				Match('/');
				// see if the close tag matches the open tag that was passed into the funtion.
				if (strcmp(c, tag())) {
					Expected("Matching Close Tag");
				}
				Match('>');
				return;
			}
		}
	}
}

// Main
int main_xml () {

	char opentag[MAX_BUF];

	Init();

	// get the first tag name manually
	Match('<');
	strncpy(opentag, tag(), MAX_BUF);
	GetAttributes();
	if (Look == '/'){
		Match('/');
		Match('>');
	} else {
		Match('>');
		xml(opentag);
	}
}

long ProcessLine(char * Input, char * Match, char * Delimiter, long Field,   
                long * CurrentLine, long * CurrentOffset) {

        long Result = 0; 

	GetField()

}

long FindMatch(char * Input, char * Match, char * Delimiter, long Field, 
		long * CurrentLine, long * CurrentOffset) {

	long Result = 0; 

	// Process each line until we find a match
	while (!(Result = ProcessLine (Input, Match, Delimiter, Field, CurrentLine, CurrentOffset))

	return Result;
}

int main () {

	long	Result = 0,
		CurrentLine = 0,
		CurrentOffset = 0;

	while (Result = FindMatch("this|is|a|test\nof|the|emergency|broadcast|system\nboom", "the", "|", 3, &CurrentLine, &CurrentOffset))
		printf("%d", Result);

}
