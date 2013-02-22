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
#define NEW_CONNECTION        0    /* Initial value */
#define STREAM                1    /* Initial value */
#define LOGIN                 2    /* Initial state to get name */
#define PLAY                  3    /* Parses commands and performs actions */
#define QUIT                  4    /* Closes connection for person */

/* boolean values */
#define FALSE                 0
#define TRUE                  1

/* structure used to access all connected users */
struct client_data{

    int state;                     /* current state of connection */
    char *name;                    /* name of user, used to deliver messages */
    char *data;                    /* userdata duplicated from disk */
    size_t  msg_buf_length;        /* The amount of memory allocated for the buffer */
    size_t  msg_length;            /* The actual length of the message */
    char *buffer;                  /* The message buffer */
};
