#include "includes.h"

/*

This interprocess communication works with pairs of pipes.

    talk   0 read   child
           1 write  parent

    listen 0 read   parent
           1 write  child

Just before a child is spawned the patent initializes the talk and listen pipe pairs with a call to init_ipc

Immediately after the fork happens the parent closes the ports that the child is going to use and the child closes the ports that the parent is going to use with calls to the init_parent_ips and init_child_ipc function calls.

The talk and listen is from the perspective of the parent.  If the parent writes to a node it writes to talk[1]. If the parent wants to listen to a child then it reads listen[0].

The child does this backwards.  The child writes to the parent on listen[1] and reads from the parent on talk[0].

*/

/* the parent must call this function before forking in order to create */
/* the pair of communications sockets */

int
init_ipc (struct node_t *node){

    pipe(node->talk);

    fcntl(node->talk[0], F_SETFL, O_NONBLOCK);
    fcntl(node->talk[1], F_SETFL, O_NONBLOCK);

    pipe(node->listen);

    fcntl(node->listen[0], F_SETFL, O_NONBLOCK);
    fcntl(node->listen[1], F_SETFL, O_NONBLOCK);

    return 0;
}

/* the parent must call this function in order to close the child ipc ports */
/* this is called by the parent immeadiately after forking */

int
init_parent_ipc (struct node_t *node){

    close(node->talk[0]);
    close(node->listen[1]);     

    return 0;
}

/* the parent must call this function in order to close the child ipc ports */
/* this is called by the parent immeadiately after forking */

int
clear_parent_ipc (struct node_t *node){

    close(node->talk[1]);
    close(node->listen[0]);     

    return 0;
}

/* the child must call this function in order to close the parent ipc ports */
/* this is called by the child immeadiately after forking */

int
init_child_ipc (struct node_t *node){

    close(node->talk[1]);
    close(node->listen[0]);     

    return 0;
}

/* the parent will call this function to write a command to a child */

int
write_to_child (struct node_t *node, char * message){

    unsigned char message_length;
    char errmsg[1024];
    char buffer[1024];

    message_length = strlen ( message );

    if (message_length > 256) {
        sprintf(errmsg, "Message to child too long");
        notify(__FILE__, __LINE__, errmsg);
        return (1);
        }

    sprintf(buffer, "%c%s", message_length, message);

/*
    sprintf(errmsg,"parent writes: %d >%s<\n", message_length, message);
    notify(__FILE__, __LINE__, errmsg);
*/

    if (write(node->talk[1], buffer, message_length+1) && !(errno == EAGAIN)) {
        notify(__FILE__, __LINE__, "problem writing to child");
        return (2);
    }                                            

    return 0;
}

/* a child will call this function to write a report to the parent */

int
write_to_parent (struct node_t *node, char *message){

    unsigned char message_length;
    char errmsg[1024];
    char buffer[1024];

    message_length = strlen ( message );

    if (message_length > 256) {
        sprintf(errmsg, "Message to parent too long");
        notify(__FILE__, __LINE__, errmsg);
        return (1);
        }

    sprintf(buffer, "%c%s", message_length, message);

/*
    sprintf(errmsg,"child writes: %d >%s<\n", message_length, message);
    notify(__FILE__, __LINE__, errmsg);
*/

    if (write(node->listen[1], buffer, message_length+1) && (errno == EAGAIN)) {
        notify(__FILE__, __LINE__, "parent died");
        return (2);
    }

    return 0;
}

/* the parent will call this function to read all child reports */

int
read_from_child (struct conf_t *nodes){

    fd_set rfds;
    int    nfds,
           fd;
    struct node_t *node;
    char status_report[255];
    char report_len;
    char errmsg[255];

    FD_ZERO(&rfds);
    nfds = OPEN_MAX; 

    /* build a list of clients that may need to comminicate */

    /* add each child to ready */
    for( node = nodes->nodes; node; node = node->next) {
        FD_SET(node->listen[0], &rfds);
    }

    /* look for a new connection */
    if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) == -1) {
        notify(__FILE__, __LINE__, "ERROR on Select ");
    }             

    for (fd=0; fd<nfds; ++fd)
        if (FD_ISSET(fd,&rfds)) {

            for( node = nodes->nodes; node->listen[0] != fd; node = node->next) {
            }

            if( read(node->listen[0], (char *) &report_len, 1) ) {

                read(node->listen[0], status_report, (int) report_len);
                status_report[(int) report_len] = '\0';

                sprintf(errmsg,"from %s to parent: %d %d %s ", node->name, node->listen[0], report_len, status_report);
                notify(__FILE__, __LINE__, errmsg);

            } else {

/*
                sprintf(errmsg,"Can't read from file descriptor %d from node: >%s<", node->listen[0], node->name);
                notify(__FILE__, __LINE__, errmsg);
*/
            }
        }

    return 0;
}

/* a child will call this function to read a command from the parent */

int
read_from_parent (struct node_t *node){

    fd_set rfds;
    int    nfds;
    char status_report[255];
    int report_len;
    char errmsg[255];

    FD_ZERO(&rfds);
    nfds = OPEN_MAX;

    return 0;
    /* build a list of clients that may need to comminicate */

    /* add the parent to the select list */
        FD_SET(node->talk[0], &rfds);

    /* look for a new connection */
    if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) == -1) {
        notify(__FILE__, __LINE__, "ERROR on Select ");
    }

    if (FD_ISSET(node->talk[0],&rfds)) {

        if( read(node->talk[0], (char *) &report_len, 1) ) {

            read(node->talk[0], status_report, (int) report_len);
            status_report[report_len] = '\0';

            sprintf(errmsg,"from %s to parent: %d %d %s ", node->name, node->talk[0], report_len, status_report);
            notify(__FILE__, __LINE__, errmsg);

        } else {

            sprintf(errmsg,"Can't read from file descriptor %d from parent %s", node->talk[0], node->name);
            notify(__FILE__, __LINE__, errmsg);
        }
    }

}


/*
The above functions are the application layer of the interprocess 
communnication layer.  But these only enable the parent and child to exchange
information.  Yet another layer is needed to actual understand the
communications.

The following functions will allow the child to report the following to the
parent:

status dead
status down
status start
status up
status message _number_

The parent is able to send the child the following commands:

command stop

The monitor will be able to tell the parent the same commands as the parent
can tell the child, but with another parameter to say which thread is being 
acted upon.  A thread name of all will cause all threads to be given  the 
command:

command stop _thread_

*/

int parse_command (struct conf_t *conf, struct node_t *node) {

    return 0;
}

int communicate (struct conf_t *conf){

    read_from_child (conf);

    return 0;
}
