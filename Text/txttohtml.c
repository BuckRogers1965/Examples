#include <stdio.h>    /* this is a compiler directive that tells the 
                         the compiler that you are going to be using
                         functions that are in the standard i/o library
                      */

#define OUT       0
#define NEWLINE   1
#define PARAGRAPH 2

main (){ 

/* declare variables */ 
    int buffer_character;    /* need a pointer to hold a single character */ 
    int STATE;
    int count;

    STATE=OUT;
    count=0;
	fprintf(stdout,"\<HTML>\n\<BODY>\n");

/* read and write the file one character at a time until you reach 
    end-of-file on either our file or output.  If the EOF is on file_descriptor 
    then drop out of the while loop. if the end-of-file is on report write 
    errors to standard out and exit the program with an error condition 
*/ 
    while ((buffer_character=getc(stdin))!=EOF) { 
	switch (STATE) {
	case OUT:	if (buffer_character=='\n'){
				STATE=NEWLINE;
				if (count<40){
					fprintf(stdout,"\n<P>\n");
					count=0;
				        }
				}
			else
				STATE=OUT;
			break;
	case NEWLINE:	if (buffer_character=='\r'||buffer_character=='\n'){
				fprintf(stdout,"\n<P>\n");
				count=0;
				STATE=PARAGRAPH;
				}
			else
				STATE=OUT;
			break;
	case PARAGRAPH:	if (buffer_character=='\r'||buffer_character=='\n'){
				STATE=PARAGRAPH;
				}
			else
				STATE=OUT;
			break;

		} /* end switch */

        putc(buffer_character, stdout); 
	count++;

        }  /* end while */ 


/* report success back to environment */ 
    return 0; 

}  /* end main*/ 
