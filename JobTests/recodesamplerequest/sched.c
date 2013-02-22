#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "node.h"
#include "list.h"
#include "timer.h"
#include "callback.h"


/*

This is the scheduler/state machine engine.  This allows arbitrary execution of a function bundled with a data object

Check for this already done in svn project.  NOPE!  Must have been on the laptop hard drive when that ate itself.  Note to self, start backing up my work on hard drive to thumb drive.

This object tracks lists of nodes that are scheduled to run at some point.

Items are added to the list to be executed with various similar function calls that add with a 0 delay, a millisecond delay, or a second delay, all unsigned.  You cannot add an item scheduled to run before now.

There is a single list.  There is a pointer to the end of the "now" items on the front of the list to allow you to easily add more 0 second delay items to the list.  

The items that are scheduled to run now, including scheduled items that have expired are moved to another list.  This is so that you don't confuse items that are being rescheduled to run with the items in your current list.

The item itself has a function to call, a message id, and a data object that is the data.

The receiving object can then process the event and perhaps send more messages to other items.

*/


enum {task_callback, task_deactivate};

typedef struct task_entry * TaskPtr;
typedef struct task_list * TaskList;

//typedef int(*FuncPtr)(TaskPtr, NodeObj, int);


struct task_entry {
   TaskPtr  next;        /* for task lists */
   TaskPtr  prev;        /* for task lists */

   TaskList owner;	 /* which list is this entry in? */

			 /* Scheduled time to run */
   unsigned long seconds;
   unsigned long millisecs;

			 /* Start Time */
   unsigned long start_seconds;
   unsigned long start_millisecs;

   FuncPtr  callback;    /* Task active function */
   NodeObj  data;       /* passed to func as fData */

   int      trace;	 /* Turn on extra debugging output for this task */
   DataObj  name;	 /* task name */
   } task_entry;

struct task_list {

	TaskPtr head;
	TaskPtr tail;

	unsigned long entry_count;

} task_list;


/* create and initialize a new task list object that is empty */
TaskList
CreateList(){

	TaskList list = malloc(sizeof(task_list));

	list->head = NULL;
	list->tail = NULL;

	list->entry_count = 0;

	return list;
}

TaskPtr
CreateTask(TaskList list){

	TaskPtr task = malloc(sizeof(task_entry));

	task->next = NULL;
	task->prev = NULL;

	task->owner = list;

	return task;


	return NULL;
}

void
RemoveTaskFromList(TaskPtr task){

	TaskList list = task->owner;

	/* remove a scheduled task from the list of things to execute. */
	/* this is needed when an item that is running is being deleted. */
	/* Or when it is being moved to another list */

	if (!task->prev){
		list->head = task->next;
	} else {
		task->prev->next = task->next;
	}

	if (!task->next){
		list->tail = task->prev;
	} else {
		task->next->prev = task->prev;
	}

	task->prev = NULL;
	task->next = NULL;
}


int
DeactivateTask(TaskPtr task){

	RemoveTaskFromList(task);

	/* call function assigned to task with data */
	(*task->callback)(task, task->data, task_deactivate);
	
	return 1;
}

int
DeleteTask(TaskPtr task){

	/* Remove task from any list it is in */
	DeactivateTask(task);

	free(task);

	task = NULL;

	return 1;

}

int
DeleteList(TaskList list){

	/* iterate through the list of tasks, deactivate each one */

	TaskPtr current = list->head;
	TaskPtr next;

	while (current){
		next = current->next;
		DeleteTask(current);
		current = next;
	}

	free (list);

	list = NULL;

	return 1;
}

/* adds a task to the list with a delay */
int
AddTaskDelay(TaskPtr task, int delay_seconds, int delay_millisecs, FuncPtr func, int mesgid, NodeObj data){

//	printf("Add task with delay of % d seconds %d milliseconds\n", delay_seconds, delay_millisecs);
	TaskList list = task->owner;
	TaskPtr current;

	unsigned long seconds;
	unsigned long millisecs;

	/* Get the time */
	GetCurrentTime(&seconds, &millisecs);

	task->callback = func;

	delay_seconds = delay_seconds + seconds;

	delay_millisecs = delay_millisecs + millisecs;


	if (delay_millisecs > 1000) {
		delay_millisecs = delay_millisecs - 1000;
		delay_seconds += 1;
	}
//	printf("\n\n*** Schedule %d %d\n\n", seconds, millisecs);
//	printf("\n\n*** Schedule %d %d\n\n", delay_seconds, delay_millisecs);

	task->seconds = delay_seconds;
	task->millisecs = delay_millisecs;
	task->next=NULL;
	task->prev=NULL;


	// just add the task if the task list is empty.
	if (!list->head) {
		list->head = list->tail = task;
		task->next = task->prev = NULL;
		return 1;
	}

	/* insert the task into the time task list in the order that it is sleeping */
   
	for ( current = list->head; current && (current->seconds < delay_seconds 
		|| (current->seconds == delay_seconds && current->millisecs < delay_millisecs)); ) {
        current = current->next;
    }

	// insert at the front of the list
	if (list->head == current) {

		list->head->prev = task;
		task->next = list->head;
		list->head = task;

	// insert at the end of the list
	} else if (!current) {

		list->tail->next = task;
		task->prev = list->tail;
		list->tail = task;

	// insert in the middle of the list
	} else {

		task->next = current;
		task->prev = current->prev;

		current->prev = task;
		task->prev->next = task;
	}

	return 1;
}

/* convenience function to make Add Task Delay easier */
int
AddTaskNow(TaskPtr task, FuncPtr func, int mesgid, NodeObj data){
	return AddTaskDelay(task, 0, 0, func, mesgid, data);
}

/* convenience function to make Add Task Delay easier */
int
AddTaskMilli(TaskPtr task, unsigned long delay_millisecs, FuncPtr func, int mesgid, NodeObj data){
//	printf("Add task with delay of %d milliseconds\n", (int) delay_millisecs);
	return AddTaskDelay(task, delay_millisecs/1000, delay_millisecs%1000, func, mesgid, data);
}

/* convenience function to make Add Task easier */
int
AddTaskSec(TaskPtr task, unsigned long delay_seconds, FuncPtr func, int mesgid, NodeObj data){
//	printf("Add task with delay of %d seconds\n", (int) delay_seconds);
	return AddTaskDelay(task, delay_seconds, 0, func, mesgid, data);
}

void
AddTaskToTail(TaskList list, TaskPtr task){

	/* add first task */
	if (!list->head){
		list->head = list->tail = task;
		task->next = NULL;
		task->prev = NULL;
		return;
	}

	list->tail->next = task;
	task->next = NULL;
	task->prev = list->tail;
	list->tail = task;
}

/* print out the names, msg id, and data values of each item in the given task list */
void
PrintDebugList(TaskList list){

}

void
ActivateTimedTasks(TaskList list, TaskList runnow){

	unsigned long seconds;
	unsigned long millisecs;

	TaskPtr current = list->head;
	TaskPtr next= NULL;

	/* Get the time */
	GetCurrentTime(&seconds, &millisecs);

//	printf("\n\n*** Activate Time %d %d\n\n", seconds, millisecs);

	while (current) {
        	if ((current->seconds > seconds) || 
				(current->seconds == seconds && current->millisecs > millisecs))
			break;

//		printf("\n\n*** TASK Activate %d %d\n\n", current->seconds, current->millisecs);

		next=current->next;
		RemoveTaskFromList(current);
		AddTaskToTail(runnow, current);
		current=next;
	}

}

/* this is the part that does the work */
int
ExecTasks(TaskList list){

	TaskList runlist = CreateList();
	TaskPtr current;

	int taskcount = 0;

	/* move all the items whose timer has expired to the execute now list */
	/* this prevents there from being confusion between what we are currently doing and what we will be doing next time */

	ActivateTimedTasks(list, runlist);

	/* iterate through the list of items to execute */

	while (runlist->head){

		/* remove task from list */
		/* tasks must reschedule each time they are called */
		current = runlist->head;
		runlist->head = current->next;
		current->next = NULL;
		current->prev = NULL;
	
		/* call function assigned to task with data */
		if(current->callback)
			(*current->callback)(current->data, current->data, task_callback);

		taskcount++;
	}

	if (list->head || taskcount)
		return 1;
	else return 0;

}

void
AdjustDelayedTasks(TaskList list, unsigned long offset){

	TaskPtr current = list->head; 

	while (current) {
		current->seconds += offset;
		current = current->next;
	}

}

int
testcallback(NodeObj object, NodeObj data, int value){

	printf("!!! ");
	return 1;
}

void
SchedTest (){

	int CountOfScheduledTasks = 1;

	TimeUpdate();

	TaskList testlist = CreateList();
	
	TaskPtr   testtask1 =  CreateTask(testlist);
	TaskPtr   testtask2 =  CreateTask(testlist);
	TaskPtr   testtask3 =  CreateTask(testlist);
	TaskPtr   testtask4 =  CreateTask(testlist);

	NodeObj testdata = NewNode();
	SetPropInt(testdata, "TestData", 1);


	AddTaskDelay(testtask1, 5, 500, &testcallback, 1000, testdata);
	AddTaskNow(testtask2, &testcallback, 1001, testdata);
	AddTaskMilli(testtask3, 100, &testcallback, 1002, testdata);
	AddTaskSec(testtask4, 10, &testcallback, 1003, testdata);

	printf("Schedtest\n");

	while(CountOfScheduledTasks){
		//long offset;

		TimeUpdate();

		CountOfScheduledTasks = ExecTasks(testlist);

		/* if we have no scheduled tasks, then begin stopping */

		printf(".");
		fflush(stdout);
		usleep(10000);
	}

	printf("\n");

}


#ifdef TESTBUILD
int main (){

SchedTest();

return 0;
}

#endif
