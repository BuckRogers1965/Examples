/*

Test the procedure to catch a memory exception

*/

/*
 *      Check the given memory allocation
 *	Trap any segmentation faults
 *	Return 1 if would have crashed
 *	Return 0 if good.
 */
int
tryvar (void *);

/*
 *     Initialize the signal handlers for memory faults
 */

void
InitializeSignalHandlers();

