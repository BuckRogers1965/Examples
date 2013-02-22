struct thread_t {
   int type;			/* tcp or disk */
   int direction;		/* source or destination */
   int model;			/* client or server */
   int timeout;			/* seconds */
   char *dbname; 		/* database name */
   char *name; 			/* name */
   char *thread;		/* threadname */
   char *filename;		/* name of hl7 message file */
   char *host;	                /* hostname */
   long int port;		/* port number */
   int ack;			/* do we acknowledge these or not */
   FILE *stream;	                /* Stream descriptor */
   int sock;	                /* Network socket */
   struct thread_t *next; 	/* the pointer to the next thread */
};

struct node_t {
   char *name; 			/* Node name */
   int state;			/* Are we running or not? */
   int talk[2];			/* IPC communications channels */
   int listen[2];		/* IPC communications channels */
   long int child_pid;		/* The PID of the child */
   struct thread_t *threads;    /* Top of thread list */
   struct node_t *next; 	/* The next node */
};

struct conf_t {
   int state;			/* state of parent machine */
   int deamon;                  /* become a deamon or not */
   char *confname;		/* configuration file name */
   char *homedir;		/* base directory to find items */
   char *messagesdir;		/* where are the messages at ? */
   char *logdir;		/* where is the log dir? */
   char *libdir;		/* where is the library dir? */
   struct node_t *nodes; 	/* Top of node list */
};
