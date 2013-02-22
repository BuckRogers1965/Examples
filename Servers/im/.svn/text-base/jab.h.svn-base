#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER             4096    /* the largest message */
 
/* connection paramaters */
#define PRIMARY_TCP_PORT   5222    /* define primary socket */
#define Q_LENGTH             25    /* the length of the message Q */
#define MAX_CLIENTS        1000    /*  */
#define SOCKET_ERROR         -1    /* assuming a -1 for all socket failures */
#define NEVER_END             1    /* MAIN LOOP NEVER ENDS */

/* possible connection states */
#define STREAM                0    /* Initial value */
#define LOGIN                 1    /* Initial state to get name */
#define CHAT                  2    /* Parses commands and performs actions */
#define QUIT                  3    /* Closes connection for person */

/* boolean values */
#define FALSE                 0
#define TRUE                  1

/* structure used to access all connected users */
struct client_data{

    int state;                     /* current state of connection */
    char *name;                    /* name of user, used to deliver messages */
    char *resource;                /* name of resource */
    char *data;                    /* userdata duplicated from disk */
    size_t  msg_buf_length;        /* The amount of memory allocated for the buffer */
    size_t  msg_length;            /* The actual length of the message */
    char *buffer;                  /* The message buffer */
};

/* dependencies */
char *load_user(char *);
void save_user(char *, char *);
int isloggedin(char *);
void stream(int);
void roster (int);
void iq (int);
void message (int);
void presence (int);
void register_x (int) ;
void auth (int);
void client_login(int);
void unknown_msg(int);
void client_actions(int);

void initialize(int);
void init_buf(int);
void deallocate_user(int);
int main();

char *concat(char *, char *);
char *strnset (char *, int);
char *xmlgetdat(char *);
char *xmlgetval(char *, char *);
char *xmlgettag(char *, char *);
char *xmlgetloc(char *);
char *xmlget(char *, char *) ;
char *xmlgetfirsttagname(char *) ;
int isvalidxml(char *) ;
