#include "jab.h"

/*** Global Variables ***/
extern struct client_data client[];
extern char hostname;

/*
 *  load the data for user from file
 */

char
*load_user(char *username){
    /* open filename in read mode */
    /* read file into dynamically allocatted strings */
    /* close file */
}


/*
 *  save the data for user to file
 */

void
save_user(char *username, char *data){

    /* open filename in overwrite mode */
    /* write data out to file */
    /* close file */
}


/*
 *  return TRUE if the user is already logged in, FALSE otherwise.
 */

int
isloggedin(char *username){

    /* go through the list of people logged into the system */
    /* if given name matches any name return true */

    return FALSE;
}

/*
 *  Presence and subscription information. 
 */

void
vcard (int fd){
    /* put from into message */
    /* if there is a to, send message to designated user */

}


/*
 *  Presence and subscription information. 
 */

void
agents (int fd){
    /* put from into message */
    /* if there is a to, send message to designated user */

}


/*
 *  handle initial message to and from client
 */

void
stream(int fd){

    char buf[BUFFER];

    /* setup a new stream */
    /* Ignore what we are given and just tell the client about the stream */
    printf("STREAM\n");          
    sprintf(buf,"<?xml version='1.0'?><stream:stream xmlns:stream='http://etherx.jabber.org/streams' id='%d' xmlns='jabber:client' from='%s'>\n", fd, "hostname");          
    write(fd, buf, strlen(buf));
    client[fd].state = LOGIN; 

}

/*
 *  Handle roster requests
 */

void
roster (int fd){

    char *id,
        *type,
        *resource;
      
    id       = xmlget(client[fd].buffer, "iq..id");
    type     = xmlget(client[fd].buffer, "iq..type");

    printf("username >%s< resource >%s< \n", client[fd].name, client[fd].resource);

    free(id);
    free(type);

/* this is what we get: "<iq type='get'><query xmlns='jabber:iq:roster'/></iq>" */
/*    sprintf(buf, "<iq type='result' id='%d' from='jrogers@localhost/test'><query xmlns='jabber:iq:roster'><item jid='test@localhost' subscription='both' name='test'/></query></iq>",); */
/* sprintf(buf, "<iq type='result' id='%d' from='%s' to='%s@%s/%s'><query xmlns='jabber:iq:agents' /></iq>",id,"hostname",username,resource); */
}

/*
 *  Handle client queries
 */

void
iq (int fd){

    char *xmlns;

    xmlns = xmlget(client[fd].buffer, "iq.query..xmlns");
    if (!strcmp(xmlns,"jabber:iq:agents")) {
        agents(fd);
    } else if (!strcmp(xmlns,"jabber:iq:roster")) { 
        roster(fd);
    } else if (!strcmp(xmlns,"vcard-temp")) { 
        vcard(fd);
    } else {
        /*  */
        /* send back an error */
    }

    free (xmlns);
}

/*
 *  handle message routings
 */

void
message (int fd){

    /* from reference into the incoming message */
    /* find user named in the to */
        /* if to user doesn't exist then send back an error message */
        /* else if user is offline, send message to offline message store */
        /* else route the message to designated user */

/* messaging

    <<< <message to='buck@six/Gabber' type='normal'><body>This is a sample message.</body></message>
    >>> <message to='buck@six/Gabber' type='normal' from='gandalf@six/Gabber'><body>This is a sample message.</body></message>

    <<< <message to='gandalf@six/Gabber' type='normal'><body>This is a responce back</body></message>
    >>> <message to='gandalf@six/Gabber' type='normal' from='buck@six/Gabber'><body>This is a responce back </body></message>     

   chat

    <<< <message to='buck@six/Gabber' type='chat'><body>chat test...</body></message>
    >>> <message to='buck@six/Gabber' type='chat' from='gandalf@six/Gabber'><body>chat test...</body></message>

    <<< <message to='gandalf@six/Gabber' type='chat'><body>what a test...</body></message>
    >>> <message to='gandalf@six/Gabber' type='chat' from='buck@six/Gabber'><body>what a test...</body></message>

*/
}

/*
 *  Presence and subscription information. 
 */

void
presence (int fd){
    /* put from into message */
    /* if there is a to, send message to designated user */

}

/*
 *  register a new user
 */

void
register_x (int fd) {

    char buf[BUFFER];
    char *id,
        *type,
        *username,
        *password,
        *stored_password,
        *resource,
        *digest;
      
    id       = xmlget(client[fd].buffer, "iq..id");
    type     = xmlget(client[fd].buffer, "iq..type");

    username = xmlget(client[fd].buffer, "iq.query.username..");
    password = xmlget(client[fd].buffer, "iq.query.password..");
    resource = xmlget(client[fd].buffer, "iq.query.resource..");
    digest   = xmlget(client[fd].buffer, "iq.query.digest..");
    printf("username >%s< password >%s< digest >%s< resource >%s< \n", username, password, digest, resource);

    /* if the user already exists, error, unathorized */
    /* else create user, save user, return error code */

    /* load user data */
    client[fd].data=load_user(username);

    if (!strcmp(client[fd].data,"")) {

        /* user doesn't exist */

        /* setup the userdata */

        /* save user */
        save_user(username, client[fd].data);

        /* send back a success message */
        sprintf(buf,"<iq id='%s' type='result'/>", id);          
        write(fd, buf, strlen(buf));

    } else {

        /* user exists */

        /* send back an error */
        sprintf(buf,"<iq id='%d' type='error'><query xmlns='jabber:iq:auth'><username>%s</username><resource>%s</resource><digest/><error code='401'>Unauthorized</error></iq>\n", id, username, resource);
        write(fd, buf, strlen(buf));

    }

    /* free everything, don't store any data until we get a good authentication */
    free (client[fd].data);
    free (id);
    free (type);
    free (password);
    free (username);
    free (digest);

/*
    <<< <iq id='2' type='set'><query xmlns='jabber:iq:register'><username>jabber</username><resource>Gabber</resource><password>1234</password></query></iq>
    >>> <iq id='2' type='error'><query xmlns='jabber:iq:register'><username>jabber</username><resource>Gabber</resource><digest sid='3A62E006'>f4d6efcadbf398e1bf78f0fec9d07feac09c3e0b</digest></query><error code='401'>Unauthorized</error></iq>
    >>> <iq id='2' type='result'/>
*/
}

/*
 *  Handle initial login
 */

void
auth (int fd){

    char 
        *id,
        *type,
        *username,
        *password,
        *stored_password,
        *resource,
        *digest;
    char buf[BUFFER];
      
    id       = xmlget(client[fd].buffer, "iq..id");
    type     = xmlget(client[fd].buffer, "iq..type");

    username = xmlget(client[fd].buffer, "iq.query.username..");
    password = xmlget(client[fd].buffer, "iq.query.password..");
    resource = xmlget(client[fd].buffer, "iq.query.resource..");
    digest   = xmlget(client[fd].buffer, "iq.query.digest..");
    printf("username >%s< password >%s< digest >%s< resource >%s< \n", username, password, digest, resource);

    /* if user is already logged in, refuse new connection */
    /* else if user doesn't exist, send back an unathorized message */
        /* load user data*/
    /* else if password doesn't match send back an unauthorized message */
    /* else log user in */

    if (isloggedin(username)){

        /* user is already logged in */

        sprintf(buf,"<iq id='%d' type='error'><query xmlns='jabber:iq:auth'><username>%s</username><resource>%s</resource><digest/><error code='401'>Unauthorized</error></iq>\n", id, username, resource);
        write(fd, buf, strlen(buf));

        free (username);
        free (resource);

    } else {

        /* load user data */

        client[fd].data=load_user(username);

        if (!strcmp(client[fd].data, "")){

            /* user does not exist */

            sprintf(buf,"<iq id='%d' type='error'><query xmlns='jabber:iq:auth'><username>%s</username><resource>%s</resource><digest/><error code='401'>Unauthorized</error></iq>\n", id, username, resource);
            write(fd, buf, strlen(buf));

            free (username);
            free (resource);

            free(client[fd].data);
            client[fd].data=NULL;

        } else {

            stored_password=xmlget(client[fd].data, "xml.auth.password..");

            if (!strcmp(password, stored_password)) {

                /* password good */

                client[fd].state    = CHAT; 
                client[fd].name     = username;
                client[fd].resource = resource;

                /* return accept to client */

                sprintf(buf,"<iq id='%s' type='result'/>", id);          
                write(fd, buf, strlen(buf));

            } else {

                /* password failed */
 
                sprintf(buf,"<iq id='%d' type='error'><query xmlns='jabber:iq:auth'><username>%s</username><resource>%s</resource><digest/><error code='401'>Unauthorized</error></iq>\n", id, username, resource);
                write(fd, buf, strlen(buf));

                free (username);
                free (resource);

                free(client[fd].data);
                client[fd].data=NULL;
            }

            free(stored_password);
        }
    }

    free (id);
    free (type);
    free (password);
    free (digest);

/*
    <<< <iq id='3' type='set'><query xmlns='jabber:iq:auth'><username>jabber</username><resource>Gabber</resource><digest>f4d6efcadbf398e1bf78f0fec9d07feac09c3e0b</digest></query></iq>
    >>> <iq id='3' type='error'><query xmlns='jabber:iq:auth'><username>jabber</username><resource>Gabber</resource><digest sid='3A62E006'>f4d6efcadbf398e1bf78f0fec9d07feac09c3e0b</digest></query><error code='401'>Unauthorized</error></iq>
    >>> <iq id='3' type='result'/>
*/
}

/*
 *  in the login state, people can either login or register a new user
 */

void
client_login(int fd){

    char *xmlns;

    xmlns = xmlget(client[fd].buffer, "iq.query..xmlns");
    if (!strcmp(xmlns,"jabber:iq:auth")) {
        auth(fd);
    } else if (!strcmp(xmlns,"jabber:iq:register")) { 
        register_x(fd);
    } else {
        /* anything else send back an unathorized error */
        //client[fd].state = QUIT; 
    }
    free (xmlns);

}

/*
 * Client actions ran by state machine
 */

void
unknown_msg(int fd){
}

/*
 * Client actions ran by state machine
 */

void
client_actions(int fd){

    char *tag;

    tag=xmlgetfirsttagname(client[fd].buffer);

    switch (client[fd].state) {

        case STREAM: {
            /* setup a new stream */
            printf("STREAM\n");          
            stream(fd);
        } break;

        case LOGIN: {
            /* perform login procedures */
            printf("LOGIN\n");          

            if (!strcmp(tag,"iq"))
                client_login(fd);
            else
                unknown_msg(fd);

        } break;

        case CHAT: {
            printf("CHAT\n");          

            if (!strcmp(tag,"iq"))
                iq(fd);
            else if (!strcmp(tag,"presence"))
                presence(fd);
            else if (!strcmp(tag,"message"))
                message(fd);
            else
                unknown_msg(fd);
        } break;

    } /* end case */

    free(tag);
    
} /* end client actions */

