#include <stdio.h>

int main( int argc, char *argv[]){

	char *ptr, *getenv();
	
	if( (ptr = getenv("HOME")) == NULL)
		printf("HOME is not defined\n");
	else
		printf("HOME=%s\n", ptr);
	exit(0);
}
