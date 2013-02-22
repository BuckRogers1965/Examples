#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char ** String_Tokenizer(char * string){
	
	
	const char **temp;

	enum {OUT, IN, IN_ESC, IN_DOUBLE, IN_DOUBLE_ESC, IN_SINGLE, IN_SINGLE_ESC, BEGIN};

	int i,
		length,
		current=0,
	    current_max=20,
		state= OUT;

	int begin=0,
		 end=1;
	
	// we need to dynamical allocate enough memory to hold 
	// an array of pointers to strings and the strings
	//

	temp = malloc (current_max*sizeof(char *));

    // parse the string, skipping white space and taking
	// each section of non white space into a seperate
	// 0 terminated string.
	//
	
	for (i=0; string[i]; i++){
			
		if(isspace(string[i])){

			switch(state){

			case OUT:
					break;

			case IN:
				// we just found the end of a string
				end=i-1;

				// create the new string
				length = (end - begin)+1;
				temp[current]=malloc(length+1);
				
				// copy the string into the space we just allocated
				strncpy((char *)temp[current], &string[begin], length);
                                
        printf("\npart is: >%s< length of %d\n", temp[current], length);
        fflush(stdout);

				// set the end of the string
				temp[current+length-1]=0;

				// increment the count by one
				current++;
				
				// if we need more entries, make them, ten at a time.
				if (current==(current_max-2)) {
					current_max = current_max + 10;
					realloc(temp, current_max*sizeof(char *));
				}

				state=OUT;
				break;

			case IN_ESC:
				break;

			case IN_DOUBLE:
				break;

			case IN_DOUBLE_ESC:
				break;

			case IN_SINGLE:
				break;

			case IN_SINGLE_ESC:
				break;

			case BEGIN:
				state=OUT;
				break;

			default:
				break;

			}


		} else {

			switch(state){

			case OUT:
				// just found the begining of a string
				begin=i;
			    state=IN;
				break;

			case IN:
				break;

			case IN_ESC:
				break;

			case IN_DOUBLE:
				break;

			case IN_DOUBLE_ESC:
				break;

			case IN_SINGLE:
				break;

			case IN_SINGLE_ESC:
				break;

			case BEGIN:
			    state=IN;
				break;

			default:
				break;
			}

		}

	}

	// catch the last string
	if (state==IN){   
	    // we just found the end of a string
	    end=i-1;
	           
	    // create the new string
	    length = (end - begin)+1;
	    temp[current]=malloc(length+1);
	                                                                
	    // copy the string into the space we just allocated
	    strncpy((char *)temp[current], &string[begin], length);

        printf("\nlast part is: >%s<\n\n\n", temp[current]);
        fflush(stdout);
        	                                                                                            
		// set the end of the string
	    temp[current+length-1]=0;

		// increment the count by one
		current++;

	}

	temp[current]=NULL;

	return temp;
}

int main (){

#define STRING_SIZE 16384
#define NUM_ENTRIES  1024

	char command_line[STRING_SIZE+1];
        const char **my_argv;

        strncpy(command_line, "/usr/bin/grep test \"test test\"", STRING_SIZE);
	my_argv=String_Tokenizer(command_line);

return 0;
}
