/* James M. Rogers */
/* Copyright 2003  */

#include "server.h"

#define SOCKET_ERROR -1


Server *
NewServer ()
{
  return (Server *) calloc (sizeof (Server), 1);
}

int
SetPort (Server * Current, int Port, int QDepth)
{
  Current->Port = Port;
  Current->QDepth = QDepth;
  return 0;
}

void
SetCallbacks (Server * Current, _cb_1 * cbnew, _cb_3 * cbdata,
	      _cb_1 * cbclose)
{
  Current->callback_new = cbnew;
  Current->callback_data = cbdata;
  Current->callback_close = cbclose;
}

int
ServerOpen (Server * Current)
{

  int primary_socket;
  struct sockaddr_in sin;

  memset ((char *) &sin, 0, sizeof (sin));

  sin.sin_family = AF_INET;
  sin.sin_port = htons (Current->Port);

  primary_socket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (primary_socket == SOCKET_ERROR)
    {
      return (-1);
    }

  if (bind (primary_socket, (struct sockaddr *) &sin, sizeof (sin))
      == SOCKET_ERROR)
    {
      close (primary_socket);
      return (-2);
    }

  if (listen (primary_socket, Current->QDepth) == SOCKET_ERROR)
    {
      close (primary_socket);
      return (-2);
    }

  Current->PrimarySocket = primary_socket;

  /* clear the active file descriptor set */
  FD_ZERO (&(Current->afds));

  /* add primary socket to main loop */
  FD_SET (Current->PrimarySocket, &(Current->afds));

  return primary_socket;
}

int
ServerClose (Server * Current)
{
  int fd;
  int nfds; 

  nfds = getdtablesize ();

  for (fd = 0; fd < nfds; ++fd)
    {
      /* Callback to client closing */
      if (Current->callback_close)
	(Current->callback_close) (fd);
      close (fd);
    }
  return 0;
}

int
ServerLoop (Server * Current)
{

  int new_socket;
  int fd, alen;
  struct sockaddr_in new_sin;
  size_t buf_size;
  int nfds; 

  nfds = getdtablesize ();

  bcopy ((char *) &(Current->afds), (char *) &(Current->rfds),
	 sizeof (Current->rfds));

  /* look for a new connection */
  if (select
      (nfds, &(Current->rfds), (fd_set *) 0, (fd_set *) 0,
       (struct timeval *) 0) == SOCKET_ERROR)
    {
      printf ("FATAL ERROR : Select Error.\n");
      //exit (1);
    }

  /* Add new connects to loop */
  if (FD_ISSET (Current->PrimarySocket, &(Current->rfds)))
    {
      alen = sizeof (new_sin);
      new_socket = accept (Current->PrimarySocket, (struct sockaddr *)
			   &new_sin, &alen);
      if (new_socket == SOCKET_ERROR)
	{
	  printf ("FATAL ERROR : Select Error.\n");
	  //exit (1);
	}
      // Callback to client code, new connection
      if (Current->callback_new)
	(*Current->callback_new) (fd);
      FD_SET (new_socket, &(Current->afds));
    }

  /* Cycle thru all open file descriptors */
  for (fd = 0; fd < nfds; ++fd)
    if (fd != Current->PrimarySocket && FD_ISSET (fd, &(Current->rfds)))
      {
	/* server code goes here */
	Current->buf_size = read (fd, Current->buffer, BUFFER);
/*
EINTR  The  call was interrupted by a signal before any data was read.
EAGAIN Non-blocking I/O has been selected using O_NONBLOCK and no data was immediately available for reading. 
EIO    I/O  error. This will happen for example when the process is in a background process group, tries to read from its  controlling tty,  and either it is ignoring or blocking SIGTTIN or its process group is orphaned.  It may also occur when there is a low level I/O error while reading from a disk or tape.
EISDIR fd refers to a directory.
EBADF  fd is not a valid file descriptor or is not open for reading.
EINVAL fd is attached to an object which is unsuitable for reading.
EFAULT buf is outside your accessible address space.
*/
	if (Current->buf_size != -1)
	  {
	    Current->buffer[buf_size] = '\0';
	    if (Current->callback_data)
	      (Current->callback_data) (fd, Current->buffer,
					Current->buf_size);
	    /* Callback to client data */
	  }
	else
	  {
	    /* Callback to client closing */
	    if (Current->callback_close)
	      (Current->callback_close) (fd);
	    close (fd);
	    FD_CLR (fd, &(Current->afds));
	  }			/* end else */
      }				/* end server code */
}				/* END MAIN */
