  /*
  
   Scheduler
   
   Schedule events to happen on specific clock cycles.
   Conserve power when not running.
   
   created 2014
   by James M. Rogers
   
   */
  
//  #include <avr/interrupt.h>
//  #include <avr/power.h>
//  #include <avr/sleep.h>
//  #include <avr/wdt.h>
//  #include <avr/io.h>
  #include <Arduino.h>
  
  //enum {task_callback, task_deactivate};
  typedef int(*FuncPtr)(struct _task_entry_type *, int, int);
  
  typedef struct _task_entry_type {
    struct _task_entry_type * next;        /* for task lists */
    struct _task_entry_type * prev;        /* for task lists */
  
    struct _task_list_type * owner; 	 /* which list is this entry in? */
  
    /* Scheduled time to run */
    unsigned long seconds;
    unsigned long millisecs;
   
    FuncPtr callback;    /* Task active function */
    int mesgid;           /*passed to func as msgid */
    int data;            /* passed to func as data */
  } 
  task_entry;
  
  typedef struct _task_list_type {
    task_entry * head;
    task_entry * tail;
  } 
  task_list;
  
  struct _task_list_type *
  CreateList(){
  
    task_list * list = (task_list *)malloc(sizeof(task_list));
  
    // Check to make sure we allocated memory.
    if (list == NULL) {
      //Serial.println("Could not allocate a task list.");
      return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
  
    return list;
  }
  
  struct _task_entry_type * 
  CreateTask(struct _task_list_type * list){
  
    if (!list) return NULL;
  
    task_entry * task = (task_entry *)malloc(sizeof(task_entry));
  
    // Check to make sure we allocated memory.
    if (task == NULL) return NULL;
    
    task->next = task->prev = NULL;  
    task->owner = list;
  
    return task;
  }
  
  void
  RemoveTaskFromList(struct _task_entry_type * task){
  
    if (!task) return;
  
    task_list * list = task->owner;
  
    // remove a scheduled task from the list of things to execute.
    // this is needed when an item that is running is being deleted.
    // Or when it is being moved to another list

    if (!task->prev){
      list->head = task->next;
    } 
    else {
      task->prev->next = task->next;
    }
  
    if (!task->next){
      list->tail = task->prev;
    } 
    else {
      task->next->prev = task->prev;
    }
  
    task->prev = task->next = NULL;
  }
  
  int
  DeactivateTask(struct _task_entry_type * task){
  
    if (!task) return 0;
  
    //if (task->owner)
    //  RemoveTaskFromList(task);
  
    // call function assigned to task with data 
    (*task->callback)(task, task->data, 0);
  
    return 1;
  }
  
  int
  DeleteTask(struct _task_entry_type * task){
  
    if (!task) return 0;
    
    // Remove task from any list it is in
    DeactivateTask(task);
    free(task);
    task = NULL;
  
    return 1;
  }
  
  int
  DeleteList(struct _task_list_type * list){
  
    if (!list) return 0;
    
    task_entry * current = list->head;
    task_entry * next;
  
    // iterate through the list of tasks, deactivate each one
    while (current){
      next = current->next;
      DeleteTask(current);
      current = next;
    }
  
    free (list);
    list = NULL;
  
    return 1;
  }
  
  static unsigned long global_seconds = 0;
  static unsigned long global_milliseconds = 0;
//  static unsigned long global_start_seconds = 0;
  
  void
  GetCurrentTime (unsigned long * seconds, unsigned long * milliseconds){
  	*seconds = global_seconds;
  	*milliseconds = global_milliseconds;
  }
  
  unsigned long
  GetCurrentSeconds (){
  	return (unsigned long)global_seconds;
  }
  
  // adds a task to the list with a delay
  int
  AddTaskDelay(struct _task_entry_type * task, unsigned long delay_seconds, unsigned long delay_millisecs, int(*FuncPtr)(struct _task_entry_type *, int, int), int mesgid, int data){
  
    if (!task) return 0;
    
    task_list * list = task->owner;
    task_entry * current;
  
    unsigned long seconds;
    unsigned long millisecs;
  
    // Get the time
    GetCurrentTime(&seconds, &millisecs);
  
    task->callback = FuncPtr;
    task->data = data;
    task->mesgid = mesgid;
  
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
    
    Serial.print("Adding Task To run in ");  
    Serial.print(task->seconds);
    Serial.print(" Seconds. ");
    Serial.print(task->millisecs );
    Serial.println(" Milliseconds. ");
  
    task->next=task->prev=NULL;
  
    // just add the task if the task list is empty.
    if (!list->head) {
      list->head = list->tail = task;
      return 1;
    }
  
    // insert the task into the time task list in the order that it is sleeping
  
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
    } 
    else if (!current) {
  
      list->tail->next = task;
      task->prev = list->tail;
      list->tail = task;
  
      // insert in the middle of the list
    } 
    else {
  
      task->next = current;
      task->prev = current->prev;
  
      current->prev = task;
      task->prev->next = task;
    }
  
    return 1;
  }
  
  // convenience function to make Add Task Delay easier
  int
  AddTaskNow(struct _task_entry_type * task, int(*FuncPtr)(struct _task_entry_type *, int, int), int mesgid, int data){
    return AddTaskDelay(task, 0, 0, FuncPtr, mesgid, data);
  }
  
  // convenience function to make Add Task Delay easier
  int
  AddTaskMilli(struct _task_entry_type * task, unsigned long delay_millisecs, int(*FuncPtr)(struct _task_entry_type *, int, int), int mesgid, int data){
    //	printf("Add task with delay of %d milliseconds\n", (int) delay_millisecs);
    return AddTaskDelay(task, delay_millisecs/1000, delay_millisecs%1000, FuncPtr, mesgid, data);
  }
  
  // convenience function to make Add Task easier
  int
  AddTaskSec(struct _task_entry_type * task, unsigned long delay_seconds,int(*FuncPtr)(struct _task_entry_type *, int, int), int mesgid, int data){
    //	printf("Add task with delay of %d seconds\n", (int) delay_seconds);
    return AddTaskDelay(task, delay_seconds, 0, FuncPtr, mesgid, data);
  }
  
  void
  AddTaskToTail(struct _task_list_type * list, struct _task_entry_type * task){
  
    if (!task || !list) return;
  
    //list->entry_count++;
    //task->owner = list;
    // add first task
    if (!list->head){
      list->head = list->tail = task;
      task->next = task->prev = NULL;
      return;
    }
  
    list->tail->next = task;
    task->next = NULL;
    task->prev = list->tail;
    list->tail = task;
  }
  
//  print out the names, msg id, and data values of each item in the given task list 
//  void
//  PrintDebugList(struct _task_list_type * list){
//  }
  
  void
  ActivateTimedTasks(struct _task_list_type * list, struct _task_list_type * runnow){
  
    unsigned long seconds;
    unsigned long millisecs;
  
    if (!list || !runnow) return;
  
    struct _task_entry_type * current = list->head;
    struct _task_entry_type * next= NULL;
  
    // Get the time
    GetCurrentTime(&seconds, &millisecs);
    
    while (current) {
      if ((current->seconds > seconds) || 
        (current->seconds == seconds && current->millisecs > millisecs))
        break;
     
      next=current->next;
      RemoveTaskFromList(current);
      AddTaskToTail(runnow, current);
      current=next;
    }  
  }
  
  
  struct _task_list_type * runlist = CreateList();
  
  // this is the part that does the work
  int
  ExecTasks(struct _task_list_type * list){
  
    if (!list) return 0; 
    
    struct _task_entry_type * current;
    int taskcount = 0;
  
    // move all the items whose timer has expired to the execute now list
    // this prevents there from being confusion between what we are currently doing and what we will be doing next time
    ActivateTimedTasks(list, runlist);
  
    // iterate through the list of items to execute
    while (runlist->head){
      // remove task from list
      // tasks must reschedule each time they are called
      current = runlist->head;
      runlist->head = current->next;
      current->next = NULL;
      current->prev = NULL;
  
      //current->owner = NULL;
      // call function assigned to task with data
      if(current->callback)
        (*current->callback)(current, current->data, current->mesgid);
  
      taskcount++;
    }
  
    if (list->head || taskcount)
      return 1;
    else return 0;
  
  }
  
   void
   AdjustDelayedTasks(struct _task_list_type * list, unsigned long offset){
   
   	struct _task_entry_type * current = list->head; 
   
   	while (current) {
   		current->seconds += offset;
   		current = current->next;
   	}
   }
  
  
//  ISR( WDT_vect ) {
    /* dummy */
//  }
  
  /*
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);             // select the watchdog timer mode
   MCUSR &= ~(1 << WDRF);                           // reset status flag
   WDTCSR |= (1 << WDCE) | (1 << WDE);              // enable configuration changes
   WDTCSR = (1<< WDP0) | (1 << WDP1) | (1 << WDP2); // set the prescalar
   WDTCSR |= (1 << WDIE);                           // enable interrupt mode
   sleep_enable();                                  // enable the sleep mode ready for use
   sleep_mode();                                    // trigger the sleep
   // ...time passes ... 
   sleep_disable();                                 // prevent further sleeps
   */
  
  
  
  /* 
  update time to current tics,
  millis resets after 49 days, so we need to detect and compensate for that.
  This is to allow the main loop to reschedule running tasks.
  */
  
  long
  TimeUpdate (){

    unsigned long milliseconds; 
    unsigned long prevSecs = global_seconds;
    long offset;
  
    milliseconds = millis();
  
  	if (!global_seconds){
  		/* first time thru manually set the offset and start time */
  //		prevSecs = tv.tv_sec;
  //		global_start_seconds  = tv.tv_sec;
  	}
  
  	global_seconds  = milliseconds/1000;
  	global_milliseconds = milliseconds%1000;
  
          //offset = global_seconds - prevSecs;
  
  	/* if offset is more than a second from last time, adjust things */
  	/* time should jump forward smoothly no more than a second at a time */
          //if ( offset < 0 || offset > 1){
  	//	global_start_seconds += offset;
  	//	return offset;
  	//}
  
  	return 0;
  }
    
  int
  testcallback(struct _task_entry_type * task, int led, int mesgid){

    switch (mesgid) {
      
      // Handle a deactivate  this is hardcoded
      case 0:      
          //Serial.println("Deleting Task.");  
          break;
      
      // Handle an on.
      case 1:
           digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
           //Serial.println("Turning LED On.");
           AddTaskMilli (task, 100, &testcallback, 2, led);
           
           break;
      
      // Handle an off.
      case 2:
           digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
           //AddTaskMilli (task, 100, &testcallback, 1, led);
           DeleteTask(task);  

           //Serial.println("Turning LED Off.");

           break;
           
      default:
           //Serial.println("Doing Nothing.");
           break;
    }
    return 0;
  
  }
  
  struct _task_list_type * Tasks;
  
  #define  LED 13
  
  void setup() {
    
    
    //Serial.begin(115200);
    
    // Setup scheduler for operation.
    Tasks = CreateList();
     pinMode(LED, OUTPUT); 
    
    // Setup timers.
    AddTaskNow   (CreateTask(Tasks),         &testcallback, 1, LED);
    AddTaskSec   (CreateTask(Tasks), 10,     &testcallback, 1, LED);
    AddTaskDelay (CreateTask(Tasks), 5, 500, &testcallback, 1, LED);
    AddTaskMilli (CreateTask(Tasks), 3000,   &testcallback, 1, LED);
    AddTaskSec   (CreateTask(Tasks), 20,     &testcallback, 1, LED);

  }
  
  void loop() {
  
    // Do all this stuff in Exec Tasks to make the main loop easier to maintain. 
    // Call timer loop.
    unsigned long offset;
    int CountOfScheduledTasks = 0;
    offset = (unsigned long) TimeUpdate();
    //if ( offset > 0 )
    //  AdjustDelayedTasks (Tasks, offset);
  
    CountOfScheduledTasks = ExecTasks(Tasks);
  
    delay(1);
  }

