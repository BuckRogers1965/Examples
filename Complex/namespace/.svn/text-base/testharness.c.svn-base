//#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "namespace.h"

int main (){

	Node * NameSpace;
	int i, j;
	char string[1024];

  for (j=0; j<=100; j++) {

	NameSpace = NSCreate();

    for (i=0; i <= 10000; i++) {
	
	sprintf(string, "lksdfhjklsdfjklsdfhjklsdfhjklsdfh%d/test0/test1/test2/test3/test4/%d", i/10, j);
	NSInsert(NameSpace, string, i);
	printf("%ld\n", NSSearch(NameSpace, string));

	NSInsert(NameSpace, "james",     1);
	NSInsert(NameSpace, "rogers",    2);
	NSInsert(NameSpace, "bob",       3);
	NSInsert(NameSpace, "aaa",       3);
	NSInsert(NameSpace, "bobabcdefghijklmnopqrstuv",    4);
	NSInsert(NameSpace, "bobabcdefghij",   5);
	NSInsert(NameSpace, "fred",      6);
	NSInsert(NameSpace, "This is a very/long/test of /multiple dirs/",       7);
	NSInsert(NameSpace, "This is a very/long/test of /multiple dirs/me too",       8);
	NSInsert(NameSpace, "harry",     9);
	NSInsert(NameSpace, "retriever", 10);

	printf("%ld ", NSSearch(NameSpace, "james"));
	printf("%ld ", NSSearch(NameSpace, "rogers"));
	printf("%ld ", NSSearch(NameSpace, "bob"));
	printf("%ld ", NSSearch(NameSpace, "aaa"));
	printf("%ld ", NSSearch(NameSpace, "bobabcdefghijklmnopqrstuv"));
	printf("%ld ", NSSearch(NameSpace, "bobabcdefghij"));
	printf("%ld ", NSSearch(NameSpace, "fred"));
	printf("%ld ", NSSearch(NameSpace, "This is a very/long/test of /multiple dirs/"));
	printf("%ld ", NSSearch(NameSpace, "This is a very/long/test of /multiple dirs/me too"));
	printf("%ld ", NSSearch(NameSpace, "harry"));
	printf("%ld  ", NSSearch(NameSpace, "retriever"));

	printf("%ld ", NSSearch(NameSpace, "I don't exist"));
	
	printf("%d ", NSDelete(NameSpace, "bobabcdefghij") );
	printf("%d ", NSDelete(NameSpace, "bobabcdefghij") );
	printf("%d  ", NSDelete(NameSpace, "I don't exist") );

	printf("%ld ", NSSearch(NameSpace, "bob"));
	printf("%ld ", NSSearch(NameSpace, "bobabcdefghijklmnopqrstuv"));
	printf("%ld ", NSSearch(NameSpace, "bobabcdefghij"));

	NSInsert(NameSpace, "james",     1000);
	printf("%ld\n", NSSearch(NameSpace, "james"));

    }

	NSRelease(NameSpace);

	usleep (0);
	fprintf(stderr,".");
  }
	return 0;
}
