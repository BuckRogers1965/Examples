#include <stdio.h>
#include "WatchDogTimer.h"

int
infinite_loop (){
	while(1);
}


int
main (){

	InitializeSignalHandlers();

	WatchDogSet(5);
	printf("A\n");
	infinite_loop ();
	printf("B\n");
	WatchDogCancel();
	printf("C\n");

		
	return 0;
}
