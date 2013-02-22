/*   socket demo                */
/*   James M. Rogers            */
/*   It's my code               */
/*   I stold it fair and square */

#include "socket_demo.h"

/* initializes the client data to a known state */
void
initialize (int fd)
{
  client[fd].location = 1;
}

/* displays the location that the client is at */
void
display_location (int fd)
{
  write (fd, location[client[fd].location].title, TITLE_BUFFER);
  write (fd, location[client[fd].location].description, ROOM_BUFFER);
}

/* display the client prompt */
void
display_prompt (int fd)
{
  write (fd, "What to do?\n\n", 13);
}

/* eat the whitespace if any in front of the next word */
/* put a '\0' at the end of the word */
/* store the location following the end of the word */
/* return the location of the begining of the word */
/* check for ignored words here, if found then recursivly */
/* call this function to return the next word */
char *
get_token (int fd)
{

  /* initialize variables */
  char *x, *y;
  x = client[fd].point_buf;

  /* move pointer to first letter in word */
  /* past whitespace (spaces or tabs), if any */
  for (; isspace (*x) && *x != '\0'; x++);

  /* store the beginning of the word */
  y = x;

  /* move one character past the end of the word */
  for (; isalpha (*x) && *x != '\0'; x++);

  /* mark this with an end of string marker */
  *x = '\0';

  /* move one more past the end of string marker */
  /* will moving one more move us past the end of buffer ? */
  /* explore other options */
  x++;

  /* store the pointer to the rest of the buffer in global variable */
  /* so that we can use it again to get the next token */
  client[fd].point_buf = x;

  /* consume all of these ignored words and do not generate a token */
  /* this is accomplished by recursively calling itself and finally */
  /* returning a char pointer to either a non ignored word or '\0'  */
  if (!strcmp ("the", y) || !strcmp ("with", y) || !strcmp ("at", y) ||
      !strcmp ("on", y) || !strcmp ("a", y) || !strcmp ("an", y))

    /* call self if ignored word was found */
    return (get_token (fd));

  /* return a char pointer to a word or a NULL string */
  /* for the end of the buffer */
  else
    return (y);
}

/* get a noun */
int
get_noun (int fd)
{
  char *y;
  y = get_token (fd);
  switch (client[fd].token[0])
    {
    case T_GO:
      {
	if (!strcmp ("north", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_NORTH;
	  }
	else if (!strcmp ("northeast", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_NORTHEAST;
	  }
	else if (!strcmp ("east", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_EAST;
	  }
	else if (!strcmp ("southeast", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_SOUTHEAST;
	  }
	else if (!strcmp ("south", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_SOUTH;
	  }
	else if (!strcmp ("southwest", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_SOUTHWEST;
	  }
	else if (!strcmp ("west", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_WEST;
	  }
	else if (!strcmp ("northwest", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_NORTHWEST;
	  }
	else if (!strcmp ("up", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_UP;
	  }
	else if (!strcmp ("down", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_DOWN;
	  }
	else
	  {			/* If you don't understand */
	    client[fd].needed = client[fd].tokens = 1;
	    client[fd].token[0] = T_MUMBLE;
	  }
	break;
      }				/* end T_GO */
    default:
      {
	if (!strcmp ("sword", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_SWORD;
	  }
	else if (!strcmp ("ogre", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_OGRE;
	  }
	else if (!strcmp ("apple", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_APPLE;
	  }
	else if (!strcmp ("lamp", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_LAMP;
	  }
	else if (!strcmp ("book", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_BOOK;
	  }
	else if (!strcmp ("key", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_KEY;
	  }
	else if (!strcmp ("ladder", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_LADDER;
	  }
	else if (!strcmp ("coal", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_COAL;
	  }
	else if (!strcmp ("letter", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_LETTER;
	  }
	else if (!strcmp ("machine", y))
	  {
	    client[fd].tokens = 2;
	    client[fd].token[1] = T_MACHINE;
	  }
	else
	  {			/* If you don't understand */
	    client[fd].needed = client[fd].tokens = 1;
	    client[fd].token[0] = T_MUMBLE;
	  }
	break;
      }

    }				/* end case */

}				/* end get_noun */

/* see if correct number of tokens found */
/* some commands are good with one */
/* others need two or three */
int
get_verb (int fd)
{
  char *y, *x;
  y = get_token (fd);
  if (!strcmp ("quit", y))
    {
      client[fd].needed = client[fd].tokens = 1;
      client[fd].token[0] = T_QUIT;
    }
  else if (!strcmp ("say", y))
    {
      client[fd].needed = client[fd].tokens = 1;
      for (x = y; isalpha (*x) && x != '\0'; x++)
	*x = '\0';
      client[fd].token[0] = T_SAY;
    }
  else if (!strcmp ("help", y))
    {
      client[fd].needed = client[fd].tokens = 1;
      client[fd].token[0] = T_HELP;
    }
  else if (!strcmp ("shout", y))
    {
      client[fd].needed = client[fd].tokens = 1;
      client[fd].token[0] = T_SHOUT;
    }
  else if (!strcmp ("go", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_GO;
    }
  else if (!strcmp ("get", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_GET;
    }
  else if (!strcmp ("drop", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_DROP;
    }
  else if (!strcmp ("attack", y))
    {
      client[fd].needed = 3;
      client[fd].tokens = 1;
      client[fd].token[0] = T_ATTACK;
    }
  else if (!strcmp ("use", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_USE;
    }
  else if (!strcmp ("look", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_LOOK;
    }
  else if (!strcmp ("move", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_MOVE;
    }
  else if (!strcmp ("lock", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_LOCK;
    }
  else if (!strcmp ("unlock", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_UNLOCK;
    }
  else if (!strcmp ("read", y))
    {
      client[fd].needed = 2;
      client[fd].tokens = 1;
      client[fd].token[0] = T_READ;
    }
  else
    {				/* If you don't understand */
      client[fd].needed = client[fd].tokens = 1;
      client[fd].token[0] = T_MUMBLE;
    }
  if (client[fd].needed > 1)
    return 1;
  else
    return 0;
}				/* end get_verb */

/* parse the input string */
void
parse (int fd)
{
  client[fd].tokens = client[fd].needed = 0;
  client[fd].point_buf = client[fd].buffer;
  get_verb (fd);
  if (client[fd].needed == 2)
    get_noun (fd);
  if (client[fd].needed == 3)
    get_noun (fd);
}

/* process the tokens found by the parser.
/* perform client actions */
void
execute (int fd)
{
  int i, x, y;
  switch (client[fd].token[0])
    {
    case T_MUMBLE:
      {
	write (fd,
	       "I don't understand what you have typed.\nType help for instruction on this games grammer.\n\n",
	       89);
	printf ("\a");
      }
      break;
    case T_QUIT:
      {
	write (fd, "Thank you, press enter to quit!\n\n", 33);
	client[fd].state = QUIT;
      }
      break;
    case T_SAY:
      {
	/* Calls a function to write out the message */
	/* following the command say in the buufer to */
	/* the other peoples screens who are in the */
	/* same room.  */
	/* other deamons can read these messages in */
	/* the game and act on them. */
	for (i = 0; i < MAX_CLIENTS; i++)
	  {
	    if (client[fd].location == client[i].location)
	      {
		write (i, client[fd].name, BUFFER);
		write (i, "says: ", 6);
		write (i, client[fd].buffer, client[fd].buf_size);
	      };		/* end if */
	  };			/* end for */
      }
      break;
    case T_HELP:
      {
	/* prints out a help screen giving examples */
	write (fd, "Hello, this is the help screen for the chat mansion.\n",
	       53);
	write (fd, "\n", 1);
	write (fd,
	       "You must type a verb followed by a noun and optionally a prepositional phrase.\n",
	       79);
	write (fd, "\n", 1);
	write (fd, "Examples are:\n", 14);
	write (fd,
	       "go north     go east     go south     go west     go up     go down           \n",
	       79);
	write (fd, "\n", 1);
	write (fd, "To quit the game type: quit\n", 27);
	write (fd, "\n", 1);
	write (fd,
	       "To talk to those in the room with you, type:  say  hello, how are you today?\n",
	       77);
	write (fd, "Anything can follow the command say.\n", 37);
	write (fd, "\n", 1);
	write (fd, "\n", 1);
	write (fd, "\n", 1);
	write (fd, "\n", 1);
	printf ("\a");
      }
      break;
    case T_SHOUT:
      {
	/* Calls a function to write out the message */
	/* following the command say in the buufer to */
	/* the other peoples screens who are in the */
	/* same room in all capital letters. In rooms */
	/* that connect to the current room a garbled */
	/* message is faintly heard. */
	write (fd, "I am calling Jim, do this some more.\n\n", 38);
	printf ("\a");
      }
      break;
    case T_GO:
      {
	/* if direction is blocked */
	/* print out a message saying why */
	/* if that direction is null */
	/* say that you can't go that way */
	/* otherwise move current room to */
	/* the connection room and print */
	/* the new rooms description */
	if (location[client[fd].location].connections[client[fd].token[1]] !=
	    0)
	  client[fd].location =
	    location[client[fd].location].connections[client[fd].token[1]];
	else
	  write (fd, "You can't go that way.\n\n", 24);
	display_location (fd);
	if (client[fd].location == 20)
	  {
	    write (fd, "Press ENTER to quit.\n\n", 22);
	    client[fd].state = QUIT;
	  }
      }
      break;
    case T_GET:
      {
	/* if object is blocked */
	/* print out a message saying why */
	/* if that object isn't in room */
	/* say that you don't see it here */
	/* if you have too many objects */
	/* say you have too much other junk */
	/* otherwise add object to inventory */
	write (fd, "It seems to be nailed down.\n\n", 29);
      }
      break;
    case T_DROP:
      {
	/* if object is blocked */
	/* print out a message saying why */
	/* if that object isn't in inventory */
	/* say that you don't have that item */
	/* otherwise add object to room list */
	write (fd, "You don't have that object.\n\n", 31);
      }
      break;
    case T_ATTACK:
      {
	/* if object2 not in inventory */
	/* say you don't have that item */
	/* if object1 not present */
	/* check to see if it matches person */
	/* if neither is true then say that */
	/* isn't present */
	/* figure what happens in any number of cases */
	write (fd, "Take a chill pill dude.\n\n", 25);
      }
      break;
    case T_USE:
      {
	/* if object1 not in inventory */
	/* say you don't have that item */
	/* if object2 not present */
	/* check to see if it matches person */
	/* if neither is true then say that */
	/* isn't present */
	/* figure what happens in any number of cases */
	write (fd, "Nothing seemed to happen.\n\n", 27);
      }
      break;
    case T_LOOK:
      {
	/* print the room description again */
	write (fd, "Nothing seemed to happen.\n\n", 27);
      }
      break;
    case T_MOVE:
      {
	/* if object not present, say so */
	/* figure out what happens */
	write (fd, "Nothing seemed to happen.\n\n", 27);
      }
      break;
    case T_LOCK:
      {
	/* if object2 not in inventory */
	/* say you don't have that item */
	/* if object1 not present, say so */
	/* if items match, replace object 1 */
	/* with an unlocked version of self */
	/* and unblock that direction */
	write (fd, "Nothing seemed to happen.\n\n", 27);
      }
      break;
    case T_UNLOCK:
      {
	/* if object2 not in inventory */
	/* say you don't have that item */
	/* if object1 not present, say so */
	/* if items match, replace object 1 */
	/* with an locked version of self */
	/* and block that direction */
	write (fd, "Nothing seemed to happen.\n\n", 27);
      }
      break;
    case T_READ:
      {
	/* if object is readable */
	/* give read description of item */
	write (fd, "It appears to be blank.\n\n", 25);
      }
      break;
    default:
      {
	/* something weird happened if you are here */
	/* the parser did something weird */
	write (fd, "There is an error in the parser.\n\n", 34);
      }
      break;
    }

}

/*  update the world environment and deamons */
void
update_environment ()
{
}

/* print the intro screen and login prompt */
void
login_screen (int fd)
{
  write (fd, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", 25);
  write (fd, "Welcome to my chat room.\n", 25);
  write (fd, "\n", 1);
  write (fd, "\n", 1);
  write (fd, "\n", 1);
  write (fd, "What is your name?\n", 19);
  write (fd, "\n", 1);
}

/* Client actions go here */
void
client_actions (int fd)
{

  switch (client[fd].state)
    {
    case NEW_CONNECTION:
      {
	login_screen (fd);
	client[fd].state = LOGIN;
      }
      break;
    case LOGIN:
      {
	strcpy (client[fd].name, client[fd].buffer);
	write (fd, "\nThank you\n\n", 12);
	client[fd].state = PLAY;
	if (client[fd].state == PLAY)
	  {
	    initialize (fd);
	    display_location (fd);
	    display_prompt (fd);
	  }
      }
      break;
    case PLAY:
      {
	parse (fd);
	execute (fd);
	display_prompt (fd);
      }
      break;
    }				/* end case */
}				/* end client actions */

/* loads the location data from the location.load file */
/* change this later to also load from a -locations filename */
int
load_locations ()
{
  int i, j, x, y, z;
  char string[BUFFER];
  FILE *fp;
  if (fp = fopen ("locations.load", "r"))
    {
      /* read the file */
      fgets (string, BUFFER, fp);
      y = atoi (string);
      printf ("The # of rooms to be read is %d\n", y);
      for (i = 0; i < y; i++)
	{
	  fgets (string, BUFFER, fp);
	  z = atoi (string);
	  if (i != z)
	    printf ("room was to be %d, read %d\n", i, z);
	  fgets (string, BUFFER, fp);
	  strcpy (location[i].title, string);
	  fgets (string, BUFFER, fp);
	  strcpy (location[i].description, string);
	  for (j = 0; j < DIRECTIONS; j++)
	    {
	      fgets (string, BUFFER, fp);
	      z = atoi (string);
	      location[i].connections[j] = z;
	    }			/* close inner for */
	}			/* close for */
      fclose (fp);
    }
  else
    return 0;
}				/* end load_locations */


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
  if (primary_socket == SOCKET_ERROR)
    {
      printf ("FATAL ERROR : Can't create primary socket.\n");
      exit (1);
    }
  printf ("Created primary socket.\n");

  if (bind (primary_socket, (struct sockaddr *) &sin, sizeof (sin))
      == SOCKET_ERROR)
    {
      printf ("FATAL ERROR : Can't bind primary socket to port.\n");
      exit (1);
    }
  printf ("Bind port was good.\n");

  if (listen (primary_socket, Q_LENGTH) == SOCKET_ERROR)
    {
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
      if (select
	  (nfds, &rfds, (fd_set *) 0, (fd_set *) 0,
	   (struct timeval *) 0) == SOCKET_ERROR)
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

      update_environment ();

    }				/* END WHILE */
}				/* END MAIN */
