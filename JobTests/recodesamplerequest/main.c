
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "node.h"
#include "list.h"
#include "sched.h"
#include "deamon.h"
#include "dirscan.h"

#include "object.h"
#include "timer.h"
#include "libload.h"
#include "dyn/bufftest.h"
#include "DebugPrint.h"
#include "namespace.h"

#include "version.h"

TaskList Tasks;

/*

The rest of the code modules are built into a single library.

This main code module is built on top of the library as a 
seperate executable linked to the library.

The reason for this is so that we can have multiple different
executables, all tiny, that each dynamically load the same library
but that can each have radically different behaviors.

This seperates the function of the library from the form of the program.

The main executable defines the behavior of:

	where to look for dynamically loaded modules
		Right now we dynamically scan down from the execution path.

	where to load in a default application
		The default application can define many further 
		operations to control the entire environment.

	what actions to take based on command line options
		Become a service?
		Where to log debug info
		How much debug info to generate
		Run unit tests for sub libraries?

	Collect all the unit tests of all the sublibraries into 
	a single function.
		Should we have an init funtion in each library 
		that calls back a function to call for testing 
		with standard return values?

REGISTERING WITH CODE MODULES	

The Tasklist is called back into the schedule function
	This should be a member of a container 
	So that there can be seperate multiple task lists executing functions

Once the Tasklist is empty, clean up and exit.

The List of registered objects is called back into the object code module so
that loaded modules can be added to the list as they register themselves.

This list of items is used later to call the activation funtions of each
loaded module. 

DYNAMICALLY LOADABLE MODULES

The dynamically loaded modules also link against the framework library.

This dramatically reduces their size into the 10-20 KB range, assuming 
they themselves don't load too big of libraries.

These modules register themselves on library load and unregister on Library exit.

ToDo:

Create a pulse generator that outputs a 1 followed by a 0 at specified millisecond intervals.
Create a timer object that outputs the time between events it receives on it's input.
Create a random object that will output a random value between a high and low value.
Create a filter object that only passes items when the value changes.
Create a filter object that only passes 1's
Create a filter object that only passes a 0
Create a file object that can read and write files.



improvement:

Allow objects to subclass from other objects, making them depend on those
other objects.  Load objects in proper order, so that their dependencies are 
all satisfied or they will be unloaded.

improvement:

The objects will publish their own interface.

Later when I add dynamically loaded language objects the objects will 
work with the language modules to automatically generate the 
necesary include or object definition files in order to properly 
program them in any embedded languages.

If we add a new object it should work with existing languages to 
export it's interface to all available languages.

If we add a new language it should generate proper header files 
for it's object definition for all existing objects.

improvement:

Be able to save and load xml files that describe the state of a container and subcontainers.
Compress these files transparently using zlib for bonus points.  Can be added later.


improvement:

At some point make a graphical interface to describe everything.
Make skins for objects load from an xml property file.

Containers can also be skinned to make them look good.

Be able to load background images for the containers 
and objects and position their 


*/

void
MainLoop(NodeObj Main){

	long offset;

	int CountOfScheduledTasks = 0;

	offset = TimeUpdate();

	if ( offset )
		AdjustDelayedTasks (Tasks, offset);

	CountOfScheduledTasks = ExecTasks(Tasks);

	/* if we have no scheduled tasks, then begin stopping */
	if (CountOfScheduledTasks == 0)
		SetPropInt(Main, "State", Stopping);
		
}

void
CreateTestApp(NodeObj Main){

	/* Create a test app to copy a file */

	NodeObj TestApp = CreateContainer(Main, "TestApp");

	NodeObj WriteFile = CreateObject(TestApp, "File");
	SetPropStr (WriteFile, "Name", "Writer");
	SetPropStr (WriteFile, "Path", "out.txt");
	SetPropStr (WriteFile, "Mode", "w");
	SetPropInt (WriteFile, "State", 1);

	NodeObj ReadFile = CreateObject(TestApp, "File");
	SetPropStr (ReadFile, "Name", "Reader"); 
	SetPropStr (ReadFile, "Path", "in.txt");
	SetPropStr (ReadFile, "Mode", "r");

	Connect(ReadFile, "Out", WriteFile, "In");

	SetPropInt (ReadFile, "State", 1);
	
}

/* return the current status of the Main execution thread */
int
IsRunning(NodeObj Main){

	//return 1;
	return (GetInt((DataObj)GetValueNode(GetPropNode(Main, "State"))));
}

/* Load in a default application */
void
LoadDefaultApp(NodeObj Main){
	DebugPrint ( "Entering Default Application function.", __FILE__, __LINE__, PROG_FLOW);
	CreateTestApp(Main);
}

void
PerformTesting(){

	int i;

	DebugPrint ( "Entering Perform Testing function.", __FILE__, __LINE__, PROG_FLOW);

//	printf("\n");
	for (i=0; i<10 ; i++)
		DataTest();

//	printf("\n");

	for (i=0; i<10 ; i++)
		NodeTest();

//	printf("\n");

	BuffTest();

	NameSpaceTest();

	SchedTest();
}

void 
Init(NodeObj Main){

	char * logname;
	NodeObj RegObjList;

	/* just hum along, add in the parts to initialize base object as I find we need them. */

	DebugPrint ( "Entering Init function.", __FILE__, __LINE__, PROG_FLOW);

	/* Set the name of the main object */
	SetName (Main, "Main");

	/* Create a place to store registered Objects */
	SetPropInt(Main, "RegObjList", 1);
	RegObjList = GetPropNode(Main, "RegObjList");
	ObjSetRegObjList(RegObjList);

	/* activate the main object */
	SetPropInt(Main, "State", Running);

	/* Insert release info into the Main node properties */
	SetPropStr(Main, "ReleaseMajor", RELEASEMAJOR);
	SetPropStr(Main, "ReleaseName",  RELEASENAME);
	SetPropStr(Main, "ReleaseMinor", RELEASEMINOR);
	SetPropStr(Main, "ReleaseLevel", RELEASELEVEL);
	SetPropStr(Main, "Copyright",    COPYRIGHT);
	SetPropStr(Main, "Author",       AUTHOR);
	SetPropStr(Main, "ReleaseTag",   RELEASETAG);

	/* process the command line */

	/* print out the help text if printhelp is turned on */
	if (GetValueInt(GetPropNode(Main, "printhelp"))) {
		printf ("%s %s.%s %s - (C) %s %s\n%s\nhttp://grokthink.org\n\n  Usage: framework <options>\n\n  Options:\n\n       -h              : This help screen\n       -d              : Become a server process\n       -l    <logfile> : logfile to output debug info\n       -p              : Print Main Nodes on exit\n       -t              : Perform Unit Testing of library functions\n       -v     <number> : Verbose level from 0 to 9, inclusive\n\n", RELEASENAME, RELEASEMAJOR, RELEASEMINOR, RELEASELEVEL, COPYRIGHT, AUTHOR, RELEASETAG);
	}

	/* if -t command line argument is set, perform unit test */
	if (GetValueInt(GetPropNode(Main, "UnitTest"))) {
		PerformTesting();
	}

	/* if deamon option was turned on, become a deamon */
	if (GetValueInt(GetPropNode(Main, "deamon"))) {
		// also turn off logging in debug print.
		// because part of becoming a deamon is eliminating stdout

		DebugPrint ( "Becoming a Deamon.", __FILE__, __LINE__, PROG_FLOW);
		become_deamon ();
	}

	/* if logname is given, set the debug print to use the logfile */
	logname = GetValueStr(GetPropNode(Main, "logname"));
	if (logname && strlen(logname)) {
		// set up the debug print to output to logfile
		// turn on normal debug printing
		DebugPrint ( "Verbose Logging Enabled.", __FILE__, __LINE__, PROG_FLOW);
		;
	}

	/* set the logging level for debug print */

	DebugPrint ( "Logging Level Set.", __FILE__, __LINE__, PROG_FLOW);


	/* Setup task list */
	Tasks = CreateList();

}

void InstallObjects(void)
{
	DebugPrint ( "Entering Install Objects function.", __FILE__, __LINE__, PROG_FLOW);
        ScanDir (".", ".object", (void *) LoadObject, 8, 0, PreOrder);

	// once the objects are found and loaded then initialize them after this.
}

enum { STORE_FILENAME=0, STORE_LOGNAME, STORE_OPTION, STORE_LOGLEVEL };
void
ProcessCmdLine(NodeObj Main, int argc, char * argv[]){

	/* skip the process name */
	int i=0;
	int state=STORE_FILENAME;

	DebugPrint ( "Entering Process Command Line Function.", __FILE__, __LINE__, PROG_FLOW);

	DebugPrint ( "Store default verbose logging level of 1.", __FILE__, __LINE__, CMDLINEOPTS);
	SetPropInt(Main, "loglevel", 1);


	while(i < argc){

		//printf("%d %s\n", i, argv[i]);
		DebugPrint ( argv[i], __FILE__, __LINE__, CMDLINEOPTS);
		switch (state){

		case STORE_LOGLEVEL:
			if ( argv[i][0]=='-' ) {
				DebugPrint ( "Option found instead of loglevel.", __FILE__, __LINE__, ERROR);	
				SetPropInt(Main, "printhelp", 1);
				return;
			} else {

				if (strlen (argv[i]) > 1 || argv[i][0]-'0' < 0 || argv[i][0]-'0' > 9) {
					DebugPrint ( "Log level not between 0 to 9, inclusive.", __FILE__, __LINE__, ERROR);
					SetPropInt(Main, "printhelp", 1);
					return;
				}
		
				DebugPrint ( "Store log level.", __FILE__, __LINE__, CMDLINEOPTS);
				SetPropInt(Main, "loglevel", argv[i][0]-'0');
			}
			state=STORE_OPTION;
			break;

		case STORE_FILENAME:
			DebugPrint ( "Store file name.", __FILE__, __LINE__, CMDLINEOPTS);
			SetPropStr(Main, "filename", argv[i]);

			// improvement:
			// need to seperate the file name from the path and store them seperate
			// That way the path to the executable can be used in searching for 
			// loadable objects in the install Objects routine later.
			state=STORE_OPTION;
			break;
			
		case STORE_LOGNAME:
			if ( argv[i][0]=='-' ) {
				DebugPrint ( "Option found instead of filename.", __FILE__, __LINE__, ERROR);	
				SetPropInt(Main, "printhelp", 1);
				return;
			} else {
				DebugPrint ( "Store log name.", __FILE__, __LINE__, CMDLINEOPTS);
				SetPropStr(Main, "logname", argv[i]);
			}
			state=STORE_OPTION;
			break;

		case STORE_OPTION:

			if (  argv[i][0]!='-' ) {
				DebugPrint ( "Option not found.", __FILE__, __LINE__, ERROR);
				SetPropInt(Main, "printhelp", 1);
				break;
			} else {

				if ( strcmp ( argv[i], "-l" ) == 0 ) {
					state=STORE_LOGNAME;
					break;
				}

				if (strcmp ( argv[i], "-h" ) == 0 ) {
					DebugPrint ( "Store print help file.", __FILE__, __LINE__, CMDLINEOPTS);
					SetPropInt(Main, "printhelp", 1);
					break;
				}

				if (strcmp ( argv[i], "-t" ) == 0 ) {
					DebugPrint ( "Store perform unit tests.", __FILE__, __LINE__, CMDLINEOPTS);
					SetPropInt(Main, "UnitTest", 1);
					break;
				}

				if (strcmp ( argv[i], "-v" ) == 0 ) {
					state = STORE_LOGLEVEL;
					break;
				}

				if (strcmp ( argv[i], "-d" ) == 0 ) {
					DebugPrint ( "Store become deamon.", __FILE__, __LINE__, CMDLINEOPTS);
					SetPropInt(Main, "deamon", 1);
					break;
				}

				if (strcmp ( argv[i], "-p" ) == 0 ) {
					DebugPrint ( "Store print nodes on exit.", __FILE__, __LINE__, CMDLINEOPTS);
					SetPropInt(Main, "PrintNodes", 1);
					break;
				}

				DebugPrint ( "Unknown Option.", __FILE__, __LINE__, ERROR);
				SetPropInt(Main, "printhelp", 1);
				return;
			}

			break;

		default:
			DebugPrint ( "Option Not Found.", __FILE__, __LINE__, ERROR);
			SetPropInt(Main, "printhelp", 1);
		}
		i++;
	}

	if (state == STORE_LOGNAME) {
		DebugPrint ( "Log filename not given.", __FILE__, __LINE__, ERROR);
		SetPropInt(Main, "printhelp", 1);
		return;
	}

	if (state == STORE_LOGLEVEL) {
		DebugPrint ( "Verbose log level not given.", __FILE__, __LINE__, ERROR);
		SetPropInt(Main, "printhelp", 1);
		return;
	}

}

/* MAIN */

int 
main ( int argc, char* argv[] ){

	NodeObj Main = NewNode();

	SetPropInt(Main, "State", Starting);

	TimeUpdate();

	DebugPrint ( "Entering Main", __FILE__, __LINE__, PROG_FLOW);

	ProcessCmdLine(Main, argc, argv);

	Init(Main);

	InstallObjects();

	LoadDefaultApp(Main);

	DebugPrint ( "Entering Main Loop.", __FILE__, __LINE__, PROG_FLOW);

	while(IsRunning(Main)){
		MainLoop(Main);
		// improvement: get delay from next scheduled item, min of 10 usecs
		usleep(10);
	}

	DebugPrint ( "No more tasks scheduled, cleaning up and exiting", __FILE__, __LINE__, PROG_FLOW);

	if (GetValueInt(GetPropNode(Main, "PrintNodes"))) {
		DebugPrint ( "Dumping Main Node on exit because -p was passed on command line.\n", __FILE__, __LINE__, PROG_FLOW);
		PrintNode(Main);
	}

	return 0;
}

