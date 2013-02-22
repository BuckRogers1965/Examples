/*
This was written by James M. Rogers on 06 December 1998.
The program was written on the authors own hardware on the authors own
time.  This software is released under the GNU Public License.
*/

/*
The intent of this code is to provide a standard toolset to implement various
Health Level 7 protocols in a portable and uniform manner.
*/

#include "includes.h"

void child_loop (struct conf_t *conf, struct node_t *node){

    char status[BUFFER];
    char *message;
    int i;

    write_to_parent(node, "Starting Child");

    node->state = RUNNING;

    /* open */
    i = protocol_open(node);

    /* initialize the proto stack */

    while (node->state == RUNNING) {

        /* proto get */
        message = protocol_get(node);

        /* is there an inbound message? */

            /* inbound process */

            /* route message */

            /* route process */

            /* store the messages */

            /* generate ack, if needed */

        /* else if the proto read failed */

            /* wait for a set timeout */

            /* restart the proto */


        /* is there an outbound message? */

            /* get the next stored message */

            /* outbound process */
    
            /* proto put */
            i = protocol_put(node, message);

            /* if the proto_put failed execute proto_fail process */

                /* proto_fail process */
    
                /* wait for a set timeout */

                /* restart the proto */

            /* else execute proto_good process */

                /* proto_good process */

        /* free the memory given by the message */
        free(message);
    
        /* listen for a command from the parent */
        i = read_from_parent (node);

/*
        sleep(1);
        node->state = SHUTDOWN; */
    }

    sleep(node->threads->timeout);
    write_to_parent(node, "Stopping Child");

    /* close */
    i = protocol_close(node);

    exit (0);
}

