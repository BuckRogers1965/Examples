/*
This was written by James M. Rogers on 06 December 1998.
The program was written on the authors own hardware on the authors own
time.  This software is released under the GNU Public License.
*/

/*
The intent of this code is to provide a standard toolset to implement various
Health Level 7 protocols in a portable and uniform manner.
*/

#include "includes.h"

/*
    The global configuration structure
*/

struct conf_t conf;

/*
    Handle the sigchild signal when a child dies.
*/

void handle_child(){
    union wait wstatus;
    long int pid;
    struct node_t *ptr;

    signal(SIGCHLD, handle_child);
    while((pid=wait3(&wstatus, WNOHANG, NULL)) > 0){
        ptr=conf.nodes;
        while ( ptr ) {
            if(ptr->child_pid==pid){
                 ptr->state=RESTART;
            }
            ptr=ptr->next;
        }
    }
}

/*
    Initialize what needs to be initialized at program startup.
*/

void initialize ( struct conf_t *conf ) {
    notify(__FILE__, __LINE__, "Beginning initialization.");
   /* setup signals */
   signal(SIGCHLD, handle_child);
}  /* end initialize */

/* 
    Do whatever it takes to become a deamon process
*/

void become_deamon ( struct conf_t *conf ) {

   int i, max_files, fd;
   notify(__FILE__, __LINE__, "Beginning become_deamon");
   /* close all open file descriptors */
   max_files=getdtablesize();
   for (i = 0; i < max_files; i++)
      close(i);

   /* change to log directory */
   /* chdir(conf.defaults.logdir); */
   chdir("/");

   /* reset the file access creation mask */
   umask(0);

   /* ignore terminal i/o signals */
   #ifdef SIGTTOU
      signal(SIGTTOU, SIG_IGN);
   #endif
   #ifdef SIGTTIN
      signal(SIGTTIN, SIG_IGN);
   #endif
   #ifdef SIGTSTP
      signal(SIGTSTP, SIG_IGN);
   #endif

   /* run in the background */
   /* disassociate from process group */
   setpgrp();
   /* disassociate from control terminal */
   if ( fork() != 0)
      exit(0); /* parent process */
   setpgrp();
   if ( fork() != 0)
      exit(0);  /* parent process */
   if ( (fd = open("/dev/tty", O_RDWR)) >= 0) {
      ioctl(fd, TIOCNOTTY, (char *) 0); /* lose control tty */
      close(fd);
   }
   /* don't reacquire a control terminal */
}  /* end become_deamon */

/* 
    Close file handles and free memory
*/

void shutdown_main ( struct conf_t *conf ) {
    notify(__FILE__, __LINE__, "Beginning shutdown");
   /* free memory */
   /* kill children */
}  /* end shutdown */

/*
    Keep the children and the monitor running.
*/

int spawn_children ( struct conf_t *conf ) {

   struct node_t *ptr;
   pid_t child_pid;
   char   errmsg[255];

   /* spawn children */
    ptr = conf->nodes;
    while ( ptr != (struct node_t *)NULL ) {

      if ( ptr->state == RESTART ) {  
          sprintf(errmsg, "Restarting %s", ptr->name);
          notify(__FILE__, __LINE__, errmsg);
          clear_parent_ipc (ptr);
          ptr->state = START;
      }

      if ( ptr->state == START ) {  
        init_ipc(ptr);
        child_pid = fork();
        if (child_pid == ERROR) {
            notify(__FILE__, __LINE__, "Error on fork attempt.\n");
        } else if (child_pid > 0) {
            /* parent process */
            init_parent_ipc (ptr);
            ptr->child_pid=child_pid;
            ptr->state=RUNNING;
        } else {
            /* child process */
            init_child_ipc (ptr);
            ptr->state=RUNNING;
            child_loop ( conf, ptr);
	    exit (0);  /* exit upon return  from child */
        }
      }
      ptr = ptr->next;
    }
    return 0;
}  /* end spawn_children */

/*
   Controls the main order of events  
*/

int
main (int argc, char *argv[]) {

    notify(__FILE__, __LINE__, "Beginning main");

    configure ( argc, argv, &conf );

    initialize ( &conf );

    if ( conf.deamon == YES ) {
        become_deamon ( &conf );
    }

    while ( conf.state==RUNNING ) {
        spawn_children(&conf);
	communicate(&conf);
    }

   shutdown_main ( &conf );

   exit (0);

}  /* end main */
