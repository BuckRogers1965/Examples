/* James M. Rogers */
/* Copyright 2012  */

#define SERVBUFFER	 512		/* the largest message */
#define MAX_CLIENT 5000


typedef void _cb_1 (int);
typedef void _cb_3 (int, char *, int);

typedef void * Server;

Server *ServerNew ();
int ServerDel (Server *);
int SetPort (Server *, int, int);
void SetCallbacks (Server *, _cb_1 *, _cb_3 *, _cb_1 *);
int ServerOpen (Server *);
int ServerClose (Server *);
int ServerLoop (Server *);
int ServerRunning(Server *);
