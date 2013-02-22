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

int violation = 0;
int try = 0;
sigjmp_buf env;

/*
 *      Handle the SIGSEGV signal when a memory segmentation error occurs.
 */

void
handle_segfault()
{
	if (try) {
		/* when we are in a try do this when there is a memory fault */
		violation = 1;
		siglongjmp(env, 1);
       } else {
               /* restore normal signal handling if we run into an issue outside of a try */
               struct sigaction handle;

               handle.sa_flags = 0;
               handle.sa_handler = NULL;

               sigaction(SIGBUS, &handle, NULL);
               sigaction(SIGSEGV, &handle, NULL);

	}
}

/*
 *      Check the given memory allocation
 *	Trap any segmentation faults
 *	Return 1 if would have crashed
 *	Return 0 if good.
 */
int
tryvar (void * test){

	volatile long x;
	volatile long * vtest;

	vtest=(long *) test;

	try = 1;

	x = sigsetjmp(env,1);

	if (x == 0){
		x = (long) *vtest;
	}

	x = violation;
	violation = 0;

	try = 0;
	return (int) x;
}

/*
 *     Initialize the signal handlers for memory faults
 */

void
InitializeSignalHandlers(){

        struct sigaction handle;

        handle.sa_flags = SA_SIGINFO;
        handle.sa_handler = handle_segfault;

        sigaction(SIGBUS, &handle, NULL);
        sigaction(SIGSEGV, &handle, NULL);
}

