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
#include <unistd.h>

sigjmp_buf env;

/*
 *      Handle the SIGALRM signal when a system alarm expires.
 */

void
handle_sigalarm()
{
	siglongjmp(env, 1);
}

/*
 *	Return 1 if timeded out
 *	Return 0 if didn't timeout
 */
int
WatchDogSet (int timeout){

	volatile int x;
	x = sigsetjmp(env,1);

	alarm(timeout);
	if (x == 0)
		return 0;

	alarm(0);
	return 1;
}

void
WatchDogCancel(){

	alarm(0);
}

/*
 *     Initialize the signal handlers for memory faults
 */

void
InitializeSignalHandlers(){

        struct sigaction handle;

        handle.sa_flags = 0;
        handle.sa_handler = handle_sigalarm;

        sigaction(SIGALRM, &handle, NULL);
}

