#include <ctype.h>
#include <stdio.h>

// Constant Declarations
#define MAX_BUF 1024

// Variable Declarations
char Look;					// Lookahead Character
char Token[MAX_BUF];
char QuotePart[MAX_BUF];

// Read New Character From Input Stream
int GetChar()
{
	Look = getchar();
}

// Report What Was Expected
int Expected(char * s)
{
	fprintf(stdout, "\nError: %s Expected.\n", s);
	exit(1);
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
}

// Get the escape section
void GetEscapePart(){
	Match('\\');
	switch (Look){
	case ' ':
		Look=' ';
		break;
	case 'r':
		Look='\r';
		break;
	case 'n':
		Look='\n';
		break;
	case 't':
		Look='\t';
		break;
	case 'b':
		Look='\b';
		break;
	case '\'':
		Look='\'';
		break;
	case '"':
		Look='"';
		break;
	default:
		Expected("Known Escape Sequence");
		}
}

// Get the Single Quoted Section
void GetQuotePart(char c){

	int i=0;
	Match(c);

	while ((Look!=c) && (Look != '\n') && (i < MAX_BUF))  {
		if (Look == '\\')
			GetEscapePart();
		QuotePart[i]=Look;
		GetChar();
		i++;
	}

	QuotePart[i]='\0';
	Match(c);
}

// Get an Identifier
char * GetToken()
{
	int i=0, j, length;

	if (isspace(Look))
		Expected("Command String");

	while (!isspace(Look) && (i < MAX_BUF))  {
		switch (Look){
		case '"':
			GetQuotePart('"');
			length=strlen(QuotePart);
			for (j=0;j<length;j++)
				Token[i++]=QuotePart[j];
			continue;
		case '\'':
			GetQuotePart('\'');
			length=strlen(QuotePart);
			for (j=0;j<length;j++)
				Token[i++]=QuotePart[j];
			continue;
		case '\\':
			GetEscapePart();
			break;
		}

		Token[i]=Look;
		GetChar();
		i++;
	}

	Token[i]='\0';
	SkipWhite();
	return (Token);
}

// Process the commandline
void cmdLine() {
	printf("[%s]\n", GetToken());
	while(!isspace(Look)) {
		printf("[%s]\n", GetToken());
	}
}

// Initialize
int Init(){
	GetChar();
	SkipWhite();
}

// Main
int main () {
	Init();
	cmdLine();
}


