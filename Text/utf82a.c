#include <stdio.h>


enum {IN, OUT};

int main (){

	int c; /* holds the character returned by getchar */
	int state = OUT;

	while ((c = getchar()) != EOF){
		switch (state){

		case IN:
			putchar(c);
			state = OUT;
			break;

		case OUT:
			state = IN;
			break;



		}

	}


}
