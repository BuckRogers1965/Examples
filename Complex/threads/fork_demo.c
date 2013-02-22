#include <stdio.h>
#include <unistd.h>

#define FORK_ERROR -1

int main (){

    pid_t parent;
    parent = fork();
    printf("%d\n",parent);
    if (parent == FORK_ERROR)
	printf("Error on fork attempt\n");
    else 
	    if (parent) printf("Parent stuff\n");
        else
	    printf("Child Stuff\n");
}
