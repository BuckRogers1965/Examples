/*

Test the procedure to catch a memory exception

*/

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#include "MemExcpHand.h"

/*
 *     Initialize everything and run the tests.
 */

int
main (){

	void * test;
	int * vtest;
	int a, b, x;

	test = 0;
	vtest = (int *) test;
	
	InitializeSignalHandlers();

	for (b=0; b< 10000; b++){
		for (a=0; a< 10000; a++){
	
			if (tryvar (&a)){
				printf("a ");
			} else {
			//	printf("b ");
			}
		}

		if (tryvar (test)){
		//	printf("a\n");
		} else {
			printf("b\n");
		}
	}

	/* Cause a bus error */
//	x = (int) *vtest;

	printf("%d\n", x);

	return 0;
}
