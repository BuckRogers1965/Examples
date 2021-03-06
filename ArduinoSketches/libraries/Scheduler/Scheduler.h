/*
  Scheduler.h - Library for Scheduler code.
  Created by James M. Rogers, 04 Dec, 2014.
  Released under GPL v3 License.
  
  Basically, in non lawyer speak, you can include this as a library in your commercial product and you do not have to free your entire code base, but any changes you make to the code in this library must be shared with any customer that asks.  
  
  You used this library for free, so give back the same as you got.
  
*/
#ifndef Scheduler_h
#define Scheduler_h

#include "Arduino.h"
  
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
  } task_entry;
  
  typedef struct _task_list_type {
    task_entry * head;
    task_entry * tail;
  } task_list;
  
  struct _task_list_type *  CreateList();
  struct _task_entry_type * CreateTask();
  int                       DeleteTask(struct _task_entry_type *);
  int                       DeleteList(struct _task_list_type *);
  void                      GetCurrentTime (unsigned long *, unsigned long *);
  unsigned long             GetCurrentSeconds ();
  
  int                       AddTaskDelay(struct _task_entry_type *, unsigned long, unsigned long, int(*FuncPtr)(struct _task_entry_type *, int, int), int, int);
  // convenience functions to make Add Task Delay easier
  int                       AddTaskNow(struct _task_entry_type *, int(*FuncPtr)(struct _task_entry_type *, int, int), int, int);
  int                       AddTaskMilli(struct _task_entry_type *, unsigned long, int(*FuncPtr)(struct _task_entry_type *, int, int), int, int);
  int                       AddTaskSec(struct _task_entry_type *, unsigned long delay_seconds,int(*FuncPtr)(struct _task_entry_type *, int, int), int, int);

  
  void                      DoTasks();

#endif
