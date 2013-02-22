/*

Test the procedure to catch a memory exception

*/

#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>


/*****************************************************************/

/*
 *      Handle the SIGSEGV signal when a memory segmentation error occurs.
 */

int violation = 0;
int try = 0;
jmp_buf env;

void
handle_segfault()
{

	printf("test aaa\n");
	if (try) {
		violation = 1;
		siglongjmp(env, 1);
	}
}

int
tryvar (void * test){

	int x;
	int * vtest;

	vtest = (int *) test;

	try = 1;
	x = sigsetjmp(env,0);

	if (x == 0)
		x = (int) *vtest;

	x = violation;
	violation = 0;

	try = 0;
	return x;
}

void
InitializeSignalHandlers(){

        struct sigaction handle;

        handle.sa_flags = SA_SIGINFO;
        handle.sa_handler = handle_segfault;

        sigaction(SIGBUS, &handle, NULL);
        sigaction(SIGSEGV, &handle, NULL);
}

int
main (){

	void * test;
	int a;

	test = 0;
	
	InitializeSignalHandlers();

	for (a=0; a< 10000; a++){

		if (tryvar (test)){
		//	printf("a\n");
		} else {
			printf("b\n");
		}
	
		if (tryvar (&a)){
			printf("a\n");
		} else {
		//	printf("b\n");
		}
	}

	return 0;
}
