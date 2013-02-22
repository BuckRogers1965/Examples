/*
This was written by James M. Rogers on 26 May 2000.
The program was written on the authors own hardware on the authors own
time.  This software is released under the GNU Public License.
*/

/*
The intent of this code is to provide a standard toolset to implement various
Health Level 7 protocols in a portable and uniform manner.
*/

#include "includes.h"

/* open protocol */

int
protocol_open (struct node_t *node) {

    char status[BUFFER];
    struct thread_t *current;

    struct sockaddr_in sin, new_sin;
    fd_set rfds, afds;
    int primary_socket, nfds, alen;

    extern int errno;
 
    current = node->threads;

    while (current) {

        sprintf (status, "opening protocol %d %d %d %d %s %s %s %s %s %d %d", 
            current->type,
            current->direction,
            current->model, 
            current->timeout,
            current->dbname,
            current->name, 
            current->thread,
            current->filename,
            current->host, 
            current->port,
            current->ack);

        write_to_parent (node, status);

        /* what protocol is being used? */
        switch (current->type) {

           case DISK:

                switch (current->direction) {

                    case SOURCE:
                        /* open the file for reading */
                        if (!(current->stream = fopen(current->filename, "r"))) {
                            sprintf(status,"error protocol open: failed to open >%s< for reading: >%s<", current->filename, strerror(errno));
                            write_to_parent (node, status);
                            exit (1);
                        }
                        sprintf(status, "opened >%s< for reading", current->filename);
                        write_to_parent (node, status);
                        break;

                    case DEST:
                        /* open the file for writing */
                        if ( !(current->stream = fopen(current->filename, "a+"))) {
                            sprintf(status,"error protocol open: failed to open >%s< for writing: >%s<", current->filename, strerror(errno));
                            write_to_parent (node, status);
                            exit (1);
                        }
                        sprintf(status, "opened >%s< for writing", current->filename);
                        write_to_parent (node, status);
                        break;

                    default:
                        break;
                }

                break; 

           case TCP:

                switch (current->model) {

                    case SERVER:

                        memset ((char *)&sin,0,sizeof(sin));
 
                        sin.sin_family = AF_INET;
                        sin.sin_port = htons(current->port);
 
                        primary_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                        if (primary_socket == ERROR) {
                            write_to_parent (node, "FATAL ERROR : Can't create primary socket");
                            exit(1);
                        }
                        write_to_parent (node, "Created primary socket");

                        if(bind(primary_socket, (struct sockaddr *)&sin, sizeof(sin)) == ERROR) {
                            write_to_parent (node, "FATAL ERROR : Can't bind primary socket to port");
                            exit(1);
                        }
                        write_to_parent (node, "Bind port was good");
 
                        if(listen(primary_socket,Q_LENGTH) == ERROR) {
                            write_to_parent (node, "FATAL ERROR : Can't listen to primary port");
                            exit(1);
                        }
                        write_to_parent (node, "Listening on Primary port");
 
                        /* clear the active file descriptor set */
                        nfds = getdtablesize();
                        FD_ZERO(&afds);
 
                        /* add primary socket to main loop */
                        FD_SET(primary_socket,&afds);    

                        /* *** *** ***   MAIN LOOP   *** *** *** */
                        while (NEVER_END){
 
                            bcopy ((char *)&afds, (char *)&rfds, sizeof(rfds));
 
                            /* look for a new connection */
                            if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) == ERROR) {
                                write_to_parent (node, "FATAL ERROR on select");
                                exit(1);
                            }                                                                       

                            if (FD_ISSET(primary_socket, &rfds)) {
                                alen = sizeof(new_sin);
                                current->sock = accept(primary_socket, (struct sockaddr *) &new_sin, &alen);
                                if (current->sock == ERROR){
                                    write_to_parent (node, "FATAL ERROR on accept");
                                    exit(1);
                                }
                                write_to_parent (node, "New connection");
                                FD_SET(current->sock, &afds);
                                break;
                            }    
                        }
                        break;

                    case CLIENT:
                        
                        memset ((char *)&sin,0,sizeof(sin));
 
                        sin.sin_family = AF_INET;
                        sin.sin_addr.s_addr = inet_addr(current->host);
                        sin.sin_port = htons(current->port);

                        current->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                        if (current->sock == ERROR) {
                            write_to_parent (node, "FATAL ERROR : Can't create socket");
                            exit(1);
                        }
                        write_to_parent (node, "Created primary socket");
                        sleep(5);

                        if (connect(current->sock, (struct sockaddr *) &sin, sizeof(sin))< 0) {
                            write_to_parent (node, "FATAL ERROR : Can't connect to server");
                            exit(1);
                        }
                        write_to_parent (node, "Connected to server");

                        break;

                    default:
                        break;
                }

                break;

           default:
                break;
        }

        current = current->next;
    }

    return 0;
}

/* get a message */

char *
protocol_get (struct node_t *node) {

    struct thread_t *current;
 
    char status[BUFFER];
 
    char *message;
    int   msg_length,
          msg_buffer_length;
    int n, c;
    char buffer[2];

    fd_set rfds;
    int    nfds,
           fd;
    extern int errno;

    struct timeval tv;
    int retval;
 
    message = (char *) 0;
 
    current = node->threads;
 
    while (current) {
 
        switch (current->direction) {
 
            case SOURCE:
 
                switch (current->type) {
 
                    case DISK:
                        message = calloc(1,BUFFER);
                        /* need to check for a memory allocation error here. */
                        msg_buffer_length = BUFFER;
                        msg_length = 0;
                        while((c=fgetc(current->stream))!=EOF) {
                            message[msg_length]=c;
                            if (msg_length > msg_buffer_length-2) {
                                msg_buffer_length = msg_buffer_length + BUFFER;
                                message=realloc(message, msg_buffer_length);
                                /* need to check for a memory allocation error here. */
                            }
                            msg_length++;
                            if (c == '\n')
                                 break; 
                        }

                        if (c ==EOF) {
                            sleep(1);
                        }

                        message[msg_length]='\000';

                        break;
 
                    case TCP:
                        nfds = getdtablesize();
                        FD_ZERO(&rfds);
                        FD_SET(current->sock, &rfds);
                        tv.tv_sec = 5;
                        tv.tv_usec = 0;
 
                        if (select(nfds, &rfds, 0, 0, &tv) == -1) {
                            notify(__FILE__, __LINE__, "ERROR on Select ");
                        }
                        if (FD_ISSET(current->sock,&rfds)) {
                            message = calloc(1,BUFFER);
                   /* need to check for a memory allocation error here. */
                            msg_buffer_length = BUFFER;
                            msg_length = 0;
                            while((recv(current->sock, buffer, 1, 0))>0) {
                                message[msg_length]=buffer[0];
                                if (msg_length > msg_buffer_length-2) {
                                    msg_buffer_length = msg_buffer_length + BUFFER;
                                    message=realloc(message, msg_buffer_length);
                   /* need to check for a memory allocation error here. */
                                }
                                msg_length++;
                                if (buffer[0] == '\n')
                                     break; 
                            }
                            message[msg_length]='\000';
                        } else {

                            sleep(1);

                            message = calloc(1,1);
                            message[0]='\000';
                        }
                        break;
 
                    default:
                        break;
                }
 
                break;
 
            case DEST:
                break;
 
            default:
                break;
        }
 
        current = current->next;
    }
 
    return message;                                          
}


/* put a message */

int
protocol_put (struct node_t *node, char *message) {

    char status[BUFFER];
    struct thread_t *current;


    extern int errno;

    current = node->threads;
 
    while (current) {
 
        switch (current->direction) {
 
            case SOURCE:
                break;
 
            case DEST:
 
                switch (current->type) {
 
                    case DISK:
                        if (!(fputs (message, current->stream))) {
                            sprintf(status, "error >>>>>%s<", strerror(errno));
                            write_to_parent (node, status);
                        }
                        fflush(current->stream);
                        break;
 
                    case TCP:
                        if ((send(current->sock, message, strlen(message),0))==-1) {
                            sprintf(status, "tcp write error >>>>>%s<", strerror(errno));
                            write_to_parent (node, status);
                        }
                        break;
 
                    default:
                        break;
                }
 
                break;
 
            default:
                break;
        }
 
 
        current = current->next;
    } 

    return 0;
}

/* close protocol */

int
protocol_close (struct node_t *node) {

    char status[BUFFER];
    struct thread_t *current;

    write_to_parent (node, "protocol close");

    current = node->threads;

    while (current) {

        /* what protocol is being used? */
        switch (current->type) {

           case DISK:
                fclose(current->stream);
                break; 

           case TCP:
                close(current->sock);
                break;

           default:
                break;
        }

        current = current->next;
    }

    return 0;
}
