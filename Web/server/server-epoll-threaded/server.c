/* James M. Rogers */
/* Copyright 2012  */

#include "server.h"

#define SOCKET_ERROR -1

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/epoll.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>

typedef struct object
{
  int state;
  _cb_1 *callback_new;
  _cb_3 *callback_data;
  _cb_1 *callback_close;

  int PrimarySocket;
  int Port;
  int QDepth;

//  int buf_size;

  int Running;

  struct epoll_event ev;
  struct epoll_event *events;
  int epfd;

} object;

void nonblock(int sockfd)
{
  int opts;
  opts = fcntl(sockfd, F_GETFL);
  if(opts < 0)
  {
    perror("fcntl(F_GETFL)\n");
    exit(1);
  }
  opts = (opts | O_NONBLOCK);
  if(fcntl(sockfd, F_SETFL, opts) < 0) 
  {
    perror("fcntl(F_SETFL)\n");
    exit(1);
  }
}

Server *
ServerNew ()
{
  struct object *obj = (struct object *) calloc (sizeof (object), 1);

  /*initialize here if needed */

  return((Server *)obj);
}

int
SetPort (Server * Current, int Port, int QDepth)
{
  struct object *obj = (object *) Current;
  obj->Port = Port;
  obj->QDepth = QDepth;
  return 0;
}

void
SetCallbacks (Server * Current, _cb_1 * cbnew, _cb_3 * cbdata,
	      _cb_1 * cbclose)
{
  struct object *obj = (object *) Current;
  obj->callback_new = cbnew;
  obj->callback_data = cbdata;
  obj->callback_close = cbclose;
}

int
ServerOpen (Server * Current)
{
  struct object *obj = (object *) Current;
  struct sockaddr_in sin;

  obj->epfd = epoll_create (MAX_CLIENT);
  if (!obj->epfd)
    {
      perror ("epoll_create\n");
      return (-1);
    }

  memset ((char *) &sin, 0, sizeof (sin));

  sin.sin_family = AF_INET;
  sin.sin_port = htons (obj->Port);

  obj->PrimarySocket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (obj->PrimarySocket == SOCKET_ERROR)
    {
      return (-1);
    }

  if (bind (obj->PrimarySocket, (struct sockaddr *) &sin, sizeof (sin))
      == SOCKET_ERROR)
    {
      close (obj->PrimarySocket);
      return (-2);
    }

  if (listen (obj->PrimarySocket, obj->QDepth) == SOCKET_ERROR)
    {
      close (obj->PrimarySocket);
      return (-2);
    }

  int reuse_addr = 1;		/* Used so we can re-bind to our port */
  /* So that we can re-bind to it without TIME_WAIT problems */
  setsockopt (obj->PrimarySocket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr,
	      sizeof (reuse_addr));

  obj->ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
  obj->ev.data.fd = obj->PrimarySocket;
  if (epoll_ctl (obj->epfd, EPOLL_CTL_ADD, obj->PrimarySocket, &obj->ev) < 0)
    {
      perror ("epoll_ctl, failed to add listenfd\n");
      return (-3);
    }

  obj->events = (struct epoll_event *) calloc (MAX_CLIENT, sizeof (struct epoll_event));

  obj->Running = 1;
  return 0;
}

int
ServerClose (Server * Current)
{
  struct object *obj = (object *) Current;

  if (!obj->Running)
    return (0);

  /* close main socket */
  /* close all client connections */

  free(obj->events);

  return 0;
}

int
ServerLoop (Server * Current)
{
  struct object *obj = (object *) Current;

  int clifd;
  int i;
  int res;
  char buffer[SERVBUFFER];
  int n;

  res = epoll_wait (obj->epfd, obj->events, MAX_CLIENT, 1);
  for (i = 0; i < res; i++)
    {
      if (obj->events[i].data.fd == obj->PrimarySocket)
	{
	  clifd = accept (obj->PrimarySocket, NULL, NULL);
	  if (clifd > 0)
	    {
	      /* we could add code here to allow refuse connection */
	      /* add code here to get client info for connection */
	      if (*obj->callback_new)
		(obj->callback_new) (obj->events[i].data.fd);
	      //printf (".");
	      //nonblock (clifd);
	      obj->ev.events = EPOLLIN | EPOLLET;
	      obj->ev.data.fd = clifd;
	      if (epoll_ctl (obj->epfd, EPOLL_CTL_ADD, clifd, &obj->ev) < 0)
		{
		  perror ("epoll_ctl ADD\n");
		  //exit (1);
		}
	    }
	  else
	    {
	      // new connection failed
	    }
	}
      else
	{
	 // Send the response back
	 if (*obj->callback_data)
		(obj->callback_data) (obj->events[i].data.fd, buffer, n);

          // handed off to another thread for processing.
          epoll_ctl (obj->epfd, EPOLL_CTL_DEL, obj->events[i].data.fd, NULL);

	  /* we now have to handle the read and close inside the thread. */

	}
    }
  return (0);
}  /* END LOOP */

int ServerRunning(Server * Current){
  struct object *obj = (object *) Current;

  return (obj->Running);
}

int ServerDel (Server * Current){

  struct object *obj = (object *) Current;

  ServerClose(Current);
  free(obj);
  Current = NULL;

  return (0);
}


