#include <stdio.h>
#include <ctype.h>

#define OUT       0
#define NEWLINE   1

#define INQUOTE   3

int
main (){ 

/* declare variables */ 
	int cur;	/* need a pointer to hold a single character */ 
	int prev = 0;	/* the previous non white space charater */
	int count = 0;	/* the count since the beginning of the current line */
	int i;		/* Index for loop */
        int STATE=OUT;
        int IsPeriod = 0;
        int IsElipse = 0;
        int prevpunct = 0;
        int emittednl = 0;

		/* character conversion array */ 
		/* converts special characters to normal values */
	int conv[256];

	// fill in array with identity values.  Map all characters to themselves. 
	for (i = 0; i < 256; i++)
		conv[i]=i;

        // Map set of special characters to space
	conv['\a'] = ' ';	// bell
	conv['\b'] = ' ';	// Backspace 
	conv['\t'] = ' ';	// (Horizontal) Tab
	conv['\v'] = ' ';	// Vertical Tab 	
	conv['\f'] = '\n';	// Form Feed 	

	// Map these characters to regular ascii replacements
	conv['\r'] = '\n';	// Carriage Return (CR)

/*	conv[ 30] = 45;	// nonbreak hyphen	real hyphen
	conv[ 31] = 45;	// optional hyphen	real hyphen
	conv[ 96] = 39;	// Left Apostrophe	single quote
	conv[145] = 39;	// Left Quote		single quote
	conv[146] = 39;	// Right Quote		single quote
	conv[147] = 34;	// Left Double Quote	double quote 
	conv[148] = 34;	// Right Double Quote	double quote 
	conv[150] = 45;	// long hyphen		real hyphen
	conv[151] = 45;	// longer hyphen	real hyphen
	conv[160] = 32;	// non break space	real space
	conv[173] = 45;	// Short hyphen		real hyphen 
*/
	while ((cur=getc(stdin))!=EOF) {

	// translate character set to ascii
	cur = conv[cur];
	count++;
	
	switch (STATE) {
	case OUT:	if (cur=='\n') {
				STATE=NEWLINE;
				
				// End of line is a newline with previous char an end of
				// sentence marker
				if (prevpunct=='.'||prevpunct=='?'||prevpunct=='!' || count < 40) {
					putc('\n', stdout);
					putc('\n', stdout);
					emittednl=1;
				} else
				     if (prev != '-')
					putc(' ', stdout);
				
				count = 0;
		        } else if (cur == '"') {
		        	STATE=INQUOTE;
		        	
			        putc(cur, stdout);
		        
			} else {
				// if something is following the -, then emit it.
				if (prev=='-'&&!isspace(cur)) {
				   putc(prev, stdout);
				   //prev =0;
				 }
	
				if (cur!='-')
				   putc(cur, stdout);

				  // keep a copy of the previous non white space character;
				  // ignoring double quotes.
				  if (!isspace(cur))
					prev = cur;
				  if (!isspace(cur) && cur != '"')
				        prevpunct = cur;
			}
			break;
			
			//eat trailing white spaces.
	case NEWLINE:	if (isspace(cur)) {
				STATE=NEWLINE;
				count = 0;
		        } else if (cur == '"') {
		        	STATE=INQUOTE;
				if(prev == '"' && !emittednl){	
					putc('\n', stdout);
					putc('\n', stdout);
				}		 
				putc(cur, stdout);
				       
			} else {
				
				STATE=OUT;
				emittednl=0;
				putc(cur, stdout);
				// keep a copy of the previous non white space character;
				// ignoring double quotes.
				if (!isspace(cur))
					prev = cur;
				  if (!isspace(cur) && cur != '"')
				        prevpunct = cur;
			}
			break;
			
	case INQUOTE: 
			if (cur == '"') {
		        	STATE=OUT;
			  putc(cur, stdout);			

			} else if (cur == '\n') {
			  putc(' ', stdout);
			} else {
			  putc(cur, stdout);			
			}
			
			if (!isspace(cur))
				prev = cur;
			if (!isspace(cur) && cur != '"')
				prevpunct = cur;
	
			break;

		} /* end switch */
	   
        }  /* end while */ 


/* report success back to environment */ 
	return 0; 

}	/* end main*/ 
