
/*   simple jabber server */
/*   James M. Rogers */

/*

  This server is aimed at installations that need a simple to use jabber server for less than a 
thousand people. 

  Limitations:

  <1000 users can be logged in at the same time.
  No file transfers.
  Only supports clear text passwords.
  Support registration, clear text passwords, roster, subscription, jabber messaging.

  No support for agents, except for reporting that there aren't any.

*/

#include "jab.h"

/*** Global Variables ***/
struct client_data client[MAX_CLIENTS+4];

/*
 * Needs to be global because of message delivery.
 */

/*
 *
 */

int main(){

    int primary_socket, new_socket;
    struct sockaddr_in sin, new_sin;
    fd_set rfds, afds;
    int fd, nfds, alen;
    int x, istagflag;
    char line[BUFFER];

    memset ((char *)&sin,0,sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PRIMARY_TCP_PORT);

    primary_socket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (primary_socket == SOCKET_ERROR) {
        printf("FATAL ERROR : Can't create primary socket.\n");
        exit(1);
    }
        printf("Created primary socket.\n");
    
    if(bind(primary_socket, (struct sockaddr *)&sin, sizeof(sin))
        == SOCKET_ERROR) {
        printf("FATAL ERROR : Can't bind primary socket to port.\n");
        exit(1);
    }
        printf("Bind port was good.\n");

    if(listen(primary_socket,Q_LENGTH) == SOCKET_ERROR) {
        printf("FATAL ERROR : Can't listen to primary port.\n");
        exit(1);
    }
        printf("Listening on Primary port.\n");
    
    /* clear the active file descriptor set */
    nfds = getdtablesize();
    FD_ZERO(&afds);

    /* add primary socket to main loop */
    FD_SET(primary_socket,&afds);

    /* *** *** ***   MAIN LOOP   *** *** *** */
    while (NEVER_END){

    bcopy ((char *)&afds, (char *)&rfds, sizeof(rfds));

    /* look for a new connection */
    if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0)
        == SOCKET_ERROR) {
        printf("FATAL ERROR : Select Error.\n");
        exit(1);
    }

    /* Add new connects to loop */
    if (FD_ISSET(primary_socket, &rfds)) {
        alen = sizeof(new_sin);
        new_socket = accept(primary_socket, (struct sockaddr *)
            &new_sin, &alen);
 
        /* set the socket to non-blocking */
        fcntl(new_socket, F_SETFL, O_NONBLOCK); 
        if (new_socket == SOCKET_ERROR){
            printf("FATAL ERROR : Select Error.\n");
            exit(1);
        }
        client[new_socket].state=STREAM;
        init_buf(new_socket);
        printf("New connection on file descriptor %d.\a\n",new_socket);
        FD_SET(new_socket,&afds);
    }

    
    /* Cycle thru all open file descriptors */
    for (fd=0; fd<nfds; ++fd)
        if (fd != primary_socket && FD_ISSET(fd,&rfds)) {

            /* server code goes here */

            while((recv(fd, line, 1, 0))>0) {
                client[fd].buffer[client[fd].msg_length]=line[0];
                if (client[fd].msg_length > client[fd].msg_buf_length-2) {
                    client[fd].msg_buf_length = client[fd].msg_buf_length + BUFFER;
                    client[fd].buffer=(char *)realloc(client[fd].buffer, client[fd].msg_buf_length);
                    /* need to check for a memory allocation error here. */
                 }
                 client[fd].msg_length++;
            }
            client[fd].buffer[client[fd].msg_length]='\000';        


//         printf("current string: %d >%s<\n", fd, client[fd].buffer);
    
            if (client[fd].msg_length==0){
                write(fd, "</stream:stream>", 17);
                close(fd);
                FD_CLR(fd, &afds);
                printf("%d Closed Connection\n",fd);
                deallocate_user(fd);
                printf("%d Cleared user data\n",fd);
            } else {
                printf("%d >%s<\n",fd,client[fd].buffer);
            } /* end else */
            
            /* if we don't have a complete tag, continue */
            if (!isvalidxml(client[fd].buffer)){
                printf("%d waiting for more input\n",fd);
                continue;
            }

//        printf("sending to client_actions: %d >%s<\n",fd,client[fd].buffer);
            client_actions(fd);

            if (client[fd].state == QUIT){
                write(fd, "</stream:stream>", 17);
                close(fd);
                FD_CLR(fd,&afds);
                printf("%d Closed Connection\n",fd);
            }

//        printf("freeing this: %d >%s<\n",fd,client[fd].buffer);
            free (client[fd].buffer);
            init_buf(fd);

        } /* end server code */
    
/*    update_environment(); */
    
    } /* END WHILE */
} /* END MAIN */
