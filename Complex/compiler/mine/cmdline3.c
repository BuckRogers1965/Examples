
// Constant Declarations
#define MAX_BUF 1024

// Variable Declarations
char Look;					// Lookahead Character
int LookOffset;				// Offset in string
char * LookString;			// Current working string
int LookLength;				// Length of the current working string

char Token[MAX_BUF];
char QuotePart[MAX_BUF];

// Read New Character From Input Stream
void GetChar()
{
    LookOffset++;
    if (LookLength < LookOffset)
        Look = '\0';
    else
        Look = LookString[LookOffset];
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
void Match( char x )
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

	while ((Look!=c) && (Look != '\0') && (i < MAX_BUF))  {
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

	while (!isspace(Look) && (Look != '\0') && (i < MAX_BUF))  {
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

// Initialize
void Init(char * StringToParse){

    Look = 0;
    LookOffset=-1;
    LookString = StringToParse;
    LookLength = strlen(LookString);

	GetChar();
	SkipWhite();
}

// Process the commandline
char ** cmdLine(char * StringToParse) {

	int current_max = 20; 
	int current = 0; 
	int length;
	char token;
	char ** temp;


    Init (StringToParse);
	//we need to dynamical allocate enough memory to hold
	// an array of pointers to strings and the strings
	//

	temp = malloc(current_max * sizeof(char *));

	// get the tokens and put them into an array in memory
	//GetToken()
	while(!isspace(Look) && Look != '\0') {
		token = GetToken();

		//create the new string
		length = strlen(token);
		temp[current] = malloc(length + 1);

		//copy the string into the space we just allocated
		strncpy((char *) temp[current], token, length);

		//set the end of the string
		temp[current][length] = 0;

		//increment the count by one
		current++;

		//if weneed more entries, make them, ten at a time.
		if (current == (current_max - 2)) {
			current_max = current_max + 10;
			temp = realloc(temp, current_max * sizeof(char *));
		}
	}

	return temp;
}

