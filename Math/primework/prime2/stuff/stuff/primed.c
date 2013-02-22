/*   James M. Rogers            */

#include "socket_demo.h"

/* initializes the client data to a known state */

void initialize (int fd) {
  client[fd].current = 2;
}

/* display the client prompt */

void display_prompt (int fd) {
  write (fd, "What to do?\n\n", 13);
}

/* Client actions go here */
void 
client_actions (int fd)
{

  switch (client[fd].state)
    {
    case NEW_CONNECTION:
      {
	initialize (fd);
      }
      break;
    case RETURN_PRIME:
      {
	execute (fd);
      }
      break;
    }				/* end case */
}				/* end client actions */

void 
main ()
{

  int primary_socket, new_socket;
  struct sockaddr_in sin, new_sin;
  fd_set rfds, afds;
  int fd, nfds, alen;
  int x;
  size_t buf_size;

  load_locations ();

  memset ((char *) &sin, 0, sizeof (sin));

  sin.sin_family = AF_INET;
  sin.sin_port = htons (PRIMARY_TCP_PORT);

  primary_socket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (primary_socket == SOCKET_ERROR) {
      printf ("FATAL ERROR : Can't create primary socket.\n");
      exit (1);
  }
  printf ("Created primary socket.\n");

  if (bind (primary_socket, (struct sockaddr *) &sin, sizeof (sin)) == SOCKET_ERROR) {
      printf ("FATAL ERROR : Can't bind primary socket to port.\n");
      exit (1);
  }
  printf ("Bind port was good.\n");

  if (listen (primary_socket, Q_LENGTH) == SOCKET_ERROR) {
      printf ("FATAL ERROR : Can't listen to primary port.\n");
      exit (1);
  }
  printf ("Listening on Primary port.\n");

  /* clear the active file descriptor set */
  nfds = getdtablesize ();
  FD_ZERO (&afds);

  /* add primary socket to main loop */
  FD_SET (primary_socket, &afds);

/* *** *** ***   MAIN LOOP   *** *** *** */
  while (NEVER_END)
    {

      bcopy ((char *) &afds, (char *) &rfds, sizeof (rfds));

      /* look for a new connection */
      if (select (nfds, &rfds, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0)
	  == SOCKET_ERROR)
	{
	  printf ("FATAL ERROR : Select Error.\n");
	  exit (1);
	}

      /* Add new connects to loop */
      if (FD_ISSET (primary_socket, &rfds))
	{
	  alen = sizeof (new_sin);
	  new_socket = accept (primary_socket, (struct sockaddr *)
			       &new_sin, &alen);
	  if (new_socket == SOCKET_ERROR)
	    {
	      printf ("FATAL ERROR : Select Error.\n");
	      exit (1);
	    }
	  login_screen (new_socket);
	  client[new_socket].state = LOGIN;
	  printf ("New connection on file descriptor %d.\a\n", new_socket);
	  FD_SET (new_socket, &afds);
	}

      /* Cycle thru all open file descriptors */
      for (fd = 0; fd < nfds; ++fd)
	if (fd != primary_socket && FD_ISSET (fd, &rfds))
	  {

	    if (client[fd].state == QUIT)
	      {
		write (fd, "SERVER Closing connection\n", 26);
		close (fd);
		FD_CLR (fd, &afds);
		printf ("%d Closed Connection\n", fd);
	      }
	    else
	      {
		/* server code goes here */
		buf_size = read (fd, client[fd].buffer, BUFFER);
		client[fd].buffer[buf_size] = '\0';
		client[fd].buf_size = buf_size;
		if (buf_size > 1)
		  printf ("%d %s", fd, client[fd].buffer);
		else
		  {
		    write (fd, "SERVER Closing connection\n", 26);
		    close (fd);
		    FD_CLR (fd, &afds);
		    printf ("%d Closed Connection\n", fd);
		  }		/* end else */
	      }			/* end else */

	    client_actions (fd);

	    /* clear the characters buffer for say command */
	    for (x = 0; x < BUFFER; x++)
	      client[fd].buffer[x] = '\0';

	    if (client[fd].state == QUITING)
	      client[fd].state = QUIT;

	  }			/* end server code */

    }				/* END WHILE */

}				/* END MAIN */
