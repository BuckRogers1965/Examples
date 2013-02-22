#include "jab.h"

/*** Global Variables ***/
extern struct client_data client;

/* initializes the client data to a known state */
void initialize(int fd) {
    client[fd].buffer = NULL;
    client[fd].data   = NULL;
    client[fd].name   = NULL;
    client[fd].msg_buf_length = 0;
    client[fd].msg_length     = 0;
}

/*
 * initializes the buffer data 
 */

void init_buf(int fd) {

    client[fd].buffer         = (char *) calloc(1, BUFFER);
    client[fd].msg_buf_length = BUFFER;
    client[fd].msg_length     = 0;
}

/*
 *  free the user data
 */

void deallocate_user(int fd) {

    free (client[fd].buffer);
    free (client[fd].data);
    free (client[fd].name);
    client[fd].msg_buf_length = 0;
    client[fd].msg_length     = 0;
}

/*
 *
 */


/* Client actions go here */
void client_actions(int fd){

    char *tag,
	*xmlns,
	*username,
	*password,
	*id,
	*type,
	*resource,
	*digest,
	buf[BUFFER];

    switch (client[fd].state) {
        case NEW_CONNECTION: {
            printf("NEW_CONNECTION\n");          
            client[fd].state = STREAM;
            } break;
        case STREAM: {
            /* setup a new stream */
            /* Ignore what we are given and just tell the client about the stream */
            printf("STREAM\n");          
            sprintf(buf,"<?xml version='1.0'?><stream:stream xmlns:stream='http://etherx.jabber.org/streams' id='%d' xmlns='jabber:client' from='%s'>\n", fd, "hostname");          
            write(fd, buf, strlen(buf));
            client[fd].state = LOGIN; 
            } break;
        case LOGIN: {
            /* perform login procedures */
            printf("LOGIN\n");          

            /* iq */
            tag = xmlget(client[fd].buffer, "iq");
            printf("get the iq >%s<\n",tag);          
            if (strcmp(tag,"")) {

                id   = xmlget(client[fd].buffer, "iq..id");
                type = xmlget(client[fd].buffer, "iq..type");
                xmlns = xmlget(client[fd].buffer, "iq.query..xmlns");

                /* auth */
                if (!strcmp(xmlns,"jabber:iq:auth")) {

                    username = xmlget(client[fd].buffer, "iq.query.username..");
                    password = xmlget(client[fd].buffer, "iq.query.password..");
                    resource = xmlget(client[fd].buffer, "iq.query.resource..");
                    digest   = xmlget(client[fd].buffer, "iq.query.digest..");
                    printf("username >%s< password >%s< digest >%s< resource >%s< \n", username, password, digest, resource);

                    /* if user is already logged in, refuse new connection */

                    if (isloggedin(username)){
                        free (username);
                        free (resource);
                    } else {
                        /* load user data */
                        client[fd].data=load_user(username)

                        if (!strcmp(client[fd].data)){
                        } else {
                            /* user exists */

                            stored_password=xmlget(client[fd].data, "xml.auth.password..");
                            printf("login good\n");          
                            /* set state to play */ 
                            client[fd].state = PLAY; 
                            client[fd].name  = username;
                            client[fd].name  = resource;
                            /* return accept to client */
                            sprintf(buf,"<iq id='%s' type='result'/>", id);          
                            write(fd, buf, strlen(buf));
                        }
                    }

                    /* store name in clientdata and moveon */

//                    /* if password matches */
//                    if (!strcmp(password, "1234")) {
//                        printf("login good\n");          
//                        /* set state to play */ 
//                        client[fd].state = PLAY; 
//                        /* return good */
//                        sprintf(buf,"<iq id='%s' type='result'/>", id);          
//                        write(fd, buf, strlen(buf));
//
//                    /* otherwise, return an error to the client */
//                    } else {
//                        free (resource);
//                        free (username);
//                        sprintf(buf,"<iq id='%d' type='error'><query xmlns='jabber:iq:auth'><username>%s</username><resource>%s</resource><digest/><error code='401'>Unauthorized</error></iq>\n", id, username, resource);
//                        write(fd, buf, strlen(buf));
//                    }

                    free (password);
                    free (digest);

                /* register */
                } else if (!strcmp(xmlns,"jabber:iq:register")) { 

                    username = xmlget(client[fd].buffer, "iq.query.username..");
                    password = xmlget(client[fd].buffer, "iq.query.password..");

                    /* load user data */
                    client[fd].data=load_user(username)

                    /* if the user doesn't exist */
                    if (!strcmp(client[fd].data,"")){
                        /* if no, create user, return good. */
                        createuser(username, client[fd].data);
                        client[fd].name=username;
                        sprintf(buf,"<iq id='%s' type='result'/>", id);          
                        write(fd, buf, strlen(buf));
                    } else{
                        /* if yes, return error and close connection */
                        sprintf(buf,"<iq id='%d' type='error'><query xmlns='jabber:iq:auth'><username>%s</username><resource>%s</resource><digest/><error code='401'>Unauthorized</error></iq>\n", id, username, resource);
                        write(fd, buf, strlen(buf));
                        free (username);
                    }
                /*    client[fd].state = QUIT; */

                    free (password);

                }

                free (id);
                free (type);
                free (xmlns);

            } else {
                /* anything else we are done */
                client[fd].state = QUIT; 
            }
/*
    <<< <iq id='0' type='set'><query xmlns='jabber:iq:auth'><username>jabber</username><resource>Gabber</resource><digest>f4d6efcadbf398e1bf78f0fec9d07feac09c3e0b</digest></query></iq>
    >>> <iq id='0' type='error'><query xmlns='jabber:iq:auth'><username>jabber</username><resource>Gabber</resource><digest sid='3A62E006'>f4d6efcadbf398e1bf78f0fec9d07feac09c3e0b</digest></query><error code='401'>Unauthorized</error></iq>

    <<< <iq id='2' type='set'><query xmlns='jabber:iq:register'><username>jabber</username><resource>Gabber</resource><password>1234</password></query></iq>
    >>> <iq id='2' type='result'/>

    <<< <iq id='3' type='set'><query xmlns='jabber:iq:auth'><username>jabber</username><resource>Gabber</resource><password>1234</password></query></iq>
    >>> <iq id='3' type='result'/>
*/
            free (tag);
            } break;
        case PLAY: {
            printf("PLAY\n");          
            printf(">>>%s<\n", client[fd].buffer);          
            /* parse the client communication */

            /* iq */
               /* roster */
/* this is what we get: "<iq type='get'><query xmlns='jabber:iq:roster'/></iq>" */
/*    sprintf(buf, "<iq type='result' id='%d' from='jrogers@localhost/test'><query xmlns='jabber:iq:roster'><item jid='test@localhost' subscription='both' name='test'/></query></iq>",);
               /* agents */
/*    sprintf(buf, "<iq type='result' id='%d' from='%s' to='%s@%s/%s'><query xmlns='jabber:iq:agents' /></iq>",id,hostname,username,resource); */
               /* vcard-temp */

            /* presence */

            /* close stream */

            /* anything else is an error  */


            /* presence and subscription */

/*
    <<< <iq id='5' to='buck@six' type='get'><vCard prodid='-//HandGen//NONSGML vGen v1.0//EN' version='3.0' xmlns='vcard-temp'/></iq>
    >>> <iq id='5' to='gandalf@six/Gabber' type='result' from='buck@six'/>

    <<< <iq type='set'><query xmlns='jabber:iq:roster'><item jid='buck@six' name='buck'/></query></iq>
    >>> <presence to='buck@six' type='subscribe'/>

    <<< <iq type='set'><query xmlns='jabber:iq:roster'><item jid='buck@six' subscription='none' name='buck'/></query></iq><iq type='result' from='gandalf@six/Gabber' to='gandalf@six/Gabber'/><iq type='set'><query xmlns='jabber:iq:roster'><item jid='buck@six' subscription='none' name='buck' ask='subscribe'/></query></iq>
    >>> <presence/>

    <<< <iq id='5' to='gandalf@six' type='get'><vCard prodid='-//HandGen//NONSGML vGen v1.0//EN' version='3.0' xmlns='vcard-temp'/></iq>
    >>> <iq id='5' to='buck@six/Gabber' type='result' from='gandalf@six'/>

    <<< <iq type='set'><query xmlns='jabber:iq:roster'><item jid='gandalf@six' name='gandalf'/></query></iq>
    >>> <presence to='gandalf@six' type='subscribe' from='buck@six'/>

    <<< <presence to='gandalf@six' type='subscribe'/>
    >>> <iq type='set'><query xmlns='jabber:iq:roster'><item jid='gandalf@six' subscription='none' name='gandalf'/></query></iq><iq type='result' from='buck@six/Gabber' to='buck@six/Gabber'/><iq type='set'><query xmlns='jabber:iq:roster'><item jid='gandalf@six' subscription='none' name='gandalf' ask='subscribe'/></query></iq>
    >>> <presence/>

    <<< <presence to='buck@six' type='subscribed'/>
    >>> <presence to='buck@six' type='subscribed' from='gandalf@six'/>

    >>> <iq type='set'><query xmlns='jabber:iq:roster'><item jid='gandalf@six' subscription='to' name='gandalf'/></query></iq><presence from='gandalf@six/Gabber' to='buck@six'><x xmlns='jabber:x:delay' from='gandalf@six/Gabber' stamp='20010115T11:54:19'/></presence>
    <<< <iq id='6' to='buck@six' type='get'><vCard prodid='-//HandGen//NONSGML vGen v1.0//EN' version='3.0' xmlns='vcard-temp'/></iq>

    >>> <iq type='set'><query xmlns='jabber:iq:roster'><item jid='buck@six' subscription='from' name='buck' ask='subscribe'/></query></iq><iq id='6' to='gandalf@six/Gabber' type='result' from='buck@six'/>
    <<< <iq type='set'><query xmlns='jabber:iq:roster'><item jid='buck@six' name='buck'/></query></iq>

    <<< <presence to='buck@six' type='subscribe'/>
    >>> <presence to='buck@six' type='subscribe' from='gandalf@six'/>    
*/

            /* messaging */                        
            /* server must add from reference into the incoming message, then route the message */

/*

messaging

    <<< <message to='buck@six/Gabber' type='normal'><body>This is a sample message.</body></message>
    >>> <message to='buck@six/Gabber' type='normal' from='gandalf@six/Gabber'><body>This is a sample message.</body></message>

    <<< <message to='gandalf@six/Gabber' type='normal'><body>This is a responce back</body></message>
    >>> <message to='gandalf@six/Gabber' type='normal' from='buck@six/Gabber'><body>This is a responce back </body></message>     

*/

/*

chat

    <<< <message to='buck@six/Gabber' type='chat'><body>chat test...</body></message>
    >>> <message to='buck@six/Gabber' type='chat' from='gandalf@six/Gabber'><body>chat test...</body></message>

    <<< <message to='gandalf@six/Gabber' type='chat'><body>what a test...</body></message>
    >>> <message to='gandalf@six/Gabber' type='chat' from='buck@six/Gabber'><body>what a test...</body></message>

*/

            } break;
    } /* end case */
} /* end client actions */

