/*   socket demo  */
/*   James M. Rogers */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PRIMARY_TCP_PORT 3507	/* define primary socket */
#define Q_LENGTH	 25	/* the length of the message Q */
#define BUFFER		 512	/* the largest message */
#define TITLE_BUFFER	 128	/* the largest message */
#define ROOM_BUFFER	 512	/* the largest message */

#define MAX_CLIENTS	10	/*  */
#define SOCKET_ERROR	-1	/* assuming a -1 for all socket failures */
#define NEVER_END	1	/* MAIN LOOP NEVER ENDS */

#define MAX_COUNTDOWN	5	/* largest number of countdown timers */
#define MAX_TOKENS      3	/* how many tokens allowed per line */

/* these are the states that the player can be in */
#define NEW_CONNECTION	0	/* Initial value */
#define LOGIN	1		/* Initial state to get name */
#define PLAY	2		/* Parses commands and performs actions */
#define QUIT	3		/* Closes connection for person */
#define QUITING	4		/* Closes connection for person */

/* the all important mumble mumble */
#define T_MUMBLE	0

/* define the verb tokens */
#define T_QUIT		1
#define T_SAY		2
#define T_HELP		3
#define T_SHOUT		4
#define T_GO		5
#define T_GET		6
#define T_DROP		7
#define T_ATTACK	8
#define T_USE		9
#define T_LOOK		10
#define T_MOVE		11
#define T_LOCK		12
#define T_UNLOCK	13
#define T_READ		14

/* define the helper words */
#define T_WITH		100
#define T_THAT		100

/* define the adjectives */
#define T_RED		210
#define T_ORANGE	220
#define T_YELLOW	230
#define T_GREEN		240
#define T_BLUE		250
#define T_PURPLE	260
#define T_BIG		301
#define T_SMALL		302
#define T_TALL		303
#define T_SHORT		304
#define T_PLATINUM	401
#define T_GOLD		402
#define T_SILVER	403
#define T_COPPER	404
#define T_IRON		405
#define T_WOODEN	406

/* define the Nouns */
#define T_SWORD		500
#define T_OGRE		501
#define T_APPLE		502
#define T_LAMP		503
#define T_MACHINE	504
#define T_BOOK		505
#define T_KEY		506
#define T_LADDER	507
#define T_COAL		508
#define T_LETTER	509

/* define the directions */
#define T_NORTH		0
#define T_NORTHEAST	1
#define T_EAST		2
#define T_SOUTHEAST	3
#define T_SOUTH		4
#define T_SOUTHWEST	5
#define T_WEST		6
#define T_NORTHWEST	7
#define T_UP		8
#define T_DOWN		9

/* define the adjectives */
#define T_A	999
#define T_AN	999
#define T_AT	999
#define T_THE	999


/* these are needed for the room connection table */
#define MAX_LOCATIONS	21	/* how many rooms */
#define DIRECTIONS	10	/* how many directions */


struct client_data
{

  int health;
  int light;
  int location;
  int state;
  char name[BUFFER];

  int countdown[MAX_COUNTDOWN];

  int token[MAX_TOKENS];
  char *word[MAX_TOKENS];
  int tokens;
  int needed;
  char *point_buf;
  int buf_size;
  char buffer[BUFFER];
};

struct locations
{

  int connections[DIRECTIONS];
  char description[ROOM_BUFFER];
  char title[TITLE_BUFFER];
};

/*** Global Variables ***/
struct client_data client[MAX_CLIENTS + 4];
struct locations location[MAX_LOCATIONS];
