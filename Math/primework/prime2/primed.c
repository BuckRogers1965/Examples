/*

   Prime  Server 

   This program is written to factor numbers upto 2^31-1.

    Written by James M. Rogers
    15 April 2000

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/time.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PRIMARY_TCP_PORT 3508	/* define primary socket */
#define Q_LENGTH	 25	/* the length of the message Q */
#define BUFFER		 8	/* the largest message */

#define MAX_CLIENTS	10	/*  */
#define SOCKET_ERROR	-1	/* assuming a -1 for all socket failures */
#define NEVER_END	1	/* MAIN LOOP NEVER ENDS */



/* these are the states that the player can be in */
#define NEW_CONNECTION	0	/* Initial value */
#define LOGIN	1	/* Initial state to get name */
#define PLAY	2	/* Parses commands and performs actions */
#define QUIT	3	/* Closes connection for person */
#define QUITING	4	/* Closes connection for person */
#define RETURN_FACTORS	5	/*  */

#define MAXSIZE 46340

struct client_data{

	char buffer[BUFFER];
	char buffer2[BUFFER];
	int  buf_size;

	int state;
        unsigned long value;
};

/*** Global Variables ***/
struct client_data client[MAX_CLIENTS+4];

char z[(MAXSIZE/8)+1];

void set_not_prime(unsigned long i) {

    ldiv_t results;
    char   c;

    results=ldiv(i, 16);

    switch (results.rem) {

        case 1:
             c='\xFE';
             break;
        case 3:
             c='\xFD';
             break;
        case 5:
             c='\xFB';
             break;
        case 7:
             c='\xF7';
             break;
        case 9:
             c='\xEF';
             break;
        case 11:
             c='\xDF';
             break;
        case 13:
             c='\xBF';
             break;
        case 15:
             c='\x7F';
             break;
        default:
             break;
    }
    z[results.quot]=(z[results.quot] & c);
}

int is_prime(unsigned long i) {

    ldiv_t results;
    char   c;

    results=ldiv(i, 16);

    switch (results.rem) {

        case 1:
             c='\x01';
             break;
        case 3:
             c='\x02';
             break;
        case 5:
             c='\x04';
             break;
        case 7:
             c='\x08';
             break;
        case 9:
             c='\x10';
             break;
        case 11:
             c='\x20';
             break;
        case 13:
             c='\x40';
             break;
        case 15:
             c='\x80';
             break;
        default:
             break;
    }
    return (long) (z[results.quot] & c);
}

void set_matrix(unsigned long i) {

    unsigned long    j;
    unsigned long    k;

    k=(MAXSIZE/i+1);

    for(j=i;j<k;j+=2) {
        set_not_prime(j*i);
    }
}

void factors( int fd, unsigned long x) {

    unsigned long i;
    unsigned long max_factor;
    unsigned long current_factor;
    ldiv_t results;
    char string[BUFFER];

    /* set the max_factor to square root of variable */
    max_factor = sqrt(x)+1;

    /* see if the variable is more than MAXSIZE^2 */
    if ( max_factor > MAXSIZE ) {
        sprintf(string, "%d is too large for me to factor.\n", x );
        write (fd, string, strlen(string));
    }

    sprintf(string, "%d: ", x);
    write (fd, string, strlen(string));
    
    /* while current_factor < max_factor */
    for(i=2; i<max_factor; i++, i++) {

        /* Test factor */
        results = ldiv(x, i);
    
        /* If there is no remainder, print the current_factor, continue. */
        if ( results.rem == 0 ) {
            sprintf(string, "%d ", i);
            write (fd, string, strlen(string));
            x = results.quot;
            max_factor = sqrt(x)+1 ;
            i--; i--;
        }
        if (i==2) i=1;
    }
    sprintf(string, "%d\n", x);
    write (fd, string, strlen(string));
}

void load_matrix(){

    unsigned long        i;
    div_t	results;
    int         c,
                j;

    /* Initialize the array */

    for(i=0;i<MAXSIZE/16;i++) {
        z[i]='\xFF';
    }

    for(i=3;i<MAXSIZE; i+=2)
        if (is_prime(i)) 
            set_matrix(i);

    /* Done, flush and close */
/*
    for(i=10000000;i<10200000; i++)
        factors(i);

    for (i=0; i<MAXSIZE/16;i++)
         putc(z[i], stdout);

    exit (0);
*/
}

/* initializes the client data to a known state */

void initialize (int fd) {
  client[fd].value = 0;
}

/* display the client prompt */

void display_prompt (int fd) {
  write (fd, "What to do?\n\n", 13);
}

/* Client actions go here */
void client_actions (int fd) {

  switch (client[fd].state)
    {
    case NEW_CONNECTION:
      {
	initialize (fd);
      }
      break;
    case RETURN_FACTORS:
      {
      }
      break;
    }				/* end case */
}				/* end client actions */

int 
main ()
{

  int primary_socket, new_socket;
  struct sockaddr_in sin, new_sin;
  fd_set rfds, afds;
  int fd, nfds, alen;
  int x;
  size_t buf_size;

  load_matrix();

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
	      } else {
		/* server code goes here */
              buf_size=1;
              while (buf_size) {
	        buf_size = read (fd, client[fd].buffer, BUFFER);
		  client[fd].buffer[buf_size] = '\0';
		  client[fd].buf_size = buf_size;
		  if (buf_size > 1) {
                    sscanf (client[fd].buffer, "%d", &client[fd].value);
                    factors (fd, client[fd].value);
		  } else {
		    write (fd, "SERVER Closing connection\n", 26);
		    close (fd);
		    FD_CLR (fd, &afds);
		    printf ("%d Closed Connection\n", fd);
		  }  /* end else */
                }  /* end while */
	      }  /* end else */

	    client_actions (fd);

	    /* clear the characters buffer for say command */
	    for (x = 0; x < BUFFER; x++)
	      client[fd].buffer[x] = '\0';

	    if (client[fd].state == QUITING)
	      client[fd].state = QUIT;

	  }  /* end server code */
    }  /* END WHILE */
}  /* END MAIN */

