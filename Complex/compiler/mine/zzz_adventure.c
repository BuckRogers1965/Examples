#include <ctype.h>
//program Cradle;

// Constant Declarations
#define MAX_BUF 1024

#define NOUN  1
#define VERB  2
#define ADV   4
#define ADJ   8
#define PREP 16
#define ARTICLE 32
#define PRONOUN 64
#define PROPERNAME 128
#define RELATIVEPRONOUN 64
#define UNKNOWN 128
#define xxxxxxxxxx xx

// Variable Declarations

char Look;					// Lookahead Character
char Token[MAX_BUF];

typedef struct words {
	char * word;
	int code;
	int type;
} words;

words dictionary[]={

{"__unknown__", 0, UNKNOWN},

{"door", 60001, NOUN},
{"apple", 60002, NOUN},
{"baggage", 60003, NOUN},
{"bird", 60004, NOUN},
{"book", 60005, NOUN},
{"boy", 60006, NOUN},
{"cat", 60007, NOUN},
{"cinema", 60008, NOUN},
{"fact", 60009, NOUN},
{"garden", 60010, NOUN},
{"woman", 60011, NOUN},
{"girl", 60012, NOUN},
{"man", 60013, NOUN},
{"boy", 60014, NOUN},
{"room", 60015, NOUN},
{"sofa", 60016, NOUN},
{"song", 60017, NOUN},
{"table", 60018, NOUN},
{"telescope", 60019, NOUN},
{"tree", 60020, NOUN},
{"rats", 60021, NOUN},
{"tape", 60022, NOUN},
{"machine", 60023, NOUN},
{"terminal", 60024, NOUN},
{"coin", 60025, NOUN},
{"candy", 60026, NOUN},
{"computer", 60027, NOUN},
{"bats", 60028, NOUN},
{"desk", 60029, NOUN},
{"manual", 60030, NOUN},
{"clock", 60031, NOUN},
{"key", 60032, NOUN},
{"dir", 60033, NOUN},
{"adventure", 60034, NOUN},
{"logout", 60035, NOUN},
{"road", 60036, NOUN},

{"go",40003,VERB},
{"take",40004,VERB},
{"get",40004,VERB},
{"quit",40005,VERB},

{"north", 20001, ADV},
{"south", 20002, ADV},
{"east", 20003, ADV},
{"west", 20004, ADV},
{"up", 20005, ADV},
{"down", 20006, ADV},

{"hungry", 30001, ADJ},
{"computer", 30002, ADJ},
{"vending", 30003, ADJ},
{"broken-down", 30004, ADJ},
{"candy", 30005, ADJ},
{"elaborate", 30006, ADJ},

{"i",106,PRONOUN},
{"you",107,PRONOUN},
{"he",108,PRONOUN},
{"she",109,PRONOUN},
{"it",110,PRONOUN},
{"we",111,PRONOUN},
{"they",112,PRONOUN},
{"me",113,PRONOUN},
{"you",114,PRONOUN},
{"him",115,PRONOUN},
{"her",116,PRONOUN},
{"it",117,PRONOUN},
{"us",118,PRONOUN},
{"them",119,PRONOUN},

{"the",20,ARTICLE},
{"a",21,ARTICLE},
{"an",22,ARTICLE},

{"at",30,PREP},
{"in",31,PREP},
{"on",32,PREP},
{"over",33,PREP},
{"to",34,PREP},
{"with",35,PREP},
{"under",36,PREP},
{"into",37,PREP},

{"", 0, 0}
};

/*
verbs_t verbs[]={
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
{"sit", "sit", INTRASITIVE, FIRST, SIMPLE, NO},
}


nouns

person
number
dative

verbs

mood
	modal
	no modal

aspect
	simple
	perfect
	progressive
	perfect_progressive

voice
	passive
	active

tense
	past
	present

base


Sentence ::= NounPhrase VerbPhrase [ Conjunction Sentence]
NounPhrase ::= ProperName |
		Pronoun |
		Article NounBar
VerbPhrase ::= IVerbPhrase
		TVerbPhrase
		DVerbPhrase
IVerbPhrase ::= v1 PropositionPhrase
TVerbPhrase ::= v1 NounPhrase PropositionPhrase
DVerbPhrase ::= v1 NounPhrase NounPhrase PropositionPhrase

PropositionPhrase ::= Proposition NounPhrase

NounBar ::= Noun [[RelativeClause] Proposition]

RelativeClause ::= RelativePronoun Sentence

I take the ball.
I go to the store.
I walk to the store in the rain.
The man watched the girl with the telescope.
I take the ball that jack built to the store.
The dog that chased that cat that ate the rat slept in the house that jack built.
I ate an apple while the ice cream melted.
*/

// Read New Character From Input Stream
int GetChar()
{
	Look = getchar();
}

// Report What Was Expected
int Expected(char * s)
{
	char msg[MAX_BUF];
	sprintf(msg, "%s Expected", s);
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
char * GetToken()
{
    int count=0;

    if (!IsAlpha(Look)){
//    	SkipWhite();
    	return ("__unknown__");
        //Expected("Name");
	}

    while (IsAlNum(Look) && (count < MAX_BUF))  {
        Token[count]=Look;
        GetChar();
        count++;
        Token[count]='\0';
    }

    SkipWhite();
    return (Token);
}

// Initialize
int Init(){

	int i;

	GetChar();
	SkipWhite();
}

/*
FullCommand	::= Command [Adverb]
Command		::= Predicate Object |
		    Predicate IndirectObject Object |
		    Predicate Object IndirectObject Preposition IndirectObject
Predicate	::= Verb [ShortAdverb]
IndirectObject	::= Object
Object		::= [Object AND] {Adjective} Noun
*/

int GetParsedToken (){

	int current=0;
	char * string = GetToken();

	while (dictionary[current].word){
		if (!strcmp(string, dictionary[current].word)){
			printf("%d %s %d\n", dictionary[current].code, dictionary[current].word, dictionary[current].type);
			return current;
		}
		current++;
	}

//	printf("%d %s %d\n", dictionary[0].code, dictionary[0].word, dictionary[0].type);
	return 0;
}

int OptionalGet(int type){
}

int FullCommand (){

	int pToken = GetParsedToken();
	
	switch (dictionary[pToken].type) {
	case VERB:
		if (dictionary[pToken].code == 40005)
			return 0;
		break;
	default:
		;
	}

	return (1);
}

int main (){

	int value=1;

	Init();

	while (value) {
		value = FullCommand();
		GetChar();
		Match('\n');
	}

}
