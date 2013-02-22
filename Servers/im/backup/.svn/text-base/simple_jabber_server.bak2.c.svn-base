
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

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
 
#define BUFFSIZE 4096


#define PRIMARY_TCP_PORT 5222    /* define primary socket */
#define Q_LENGTH     25    /* the length of the message Q */
#define BUFFER         512    /* the largest message */
#define TITLE_BUFFER     128    /* the largest message */
#define ROOM_BUFFER     512    /* the largest message */

#define MAX_CLIENTS    1000    /*  */
#define SOCKET_ERROR    -1    /* assuming a -1 for all socket failures */
#define NEVER_END    1    /* MAIN LOOP NEVER ENDS */

#define MAX_COUNTDOWN    5    /* largest number of countdown timers */
#define MAX_TOKENS      3    /* how many tokens allowed per line */

/* these are the states that the player can be in */
#define NEW_CONNECTION    0    /* Initial value */
#define STREAM    1    /* Initial value */
#define LOGIN    2    /* Initial state to get name */
#define PLAY    3    /* Parses commands and performs actions */
#define QUITING    4    /* Closes connection for person */
#define QUIT    5    /* Closes connection for person */

struct client_data{

    int state;
    char *name;
    char *data;
    char *point_buf;
    size_t  buf_size;
    char *buffer;
};

/*** Global Variables ***/
struct client_data client[MAX_CLIENTS+4];

/*
 *
 */
 
char *
concat(char *string1, char *string2){
 
  int length1, length2;    /* holds length of strings */
 
  /* get the length of the second string */
  length2 = strlen(string2);
 
  /* if the second string is empty, we are done */
  if (length2==0)
       return string1;
 
  /* get the length of the first string */
  length1 = strlen(string1);
 
  /* expand string to hold the extra characters */
  if ((string1 = (char *) realloc(string1, length1 + length2 +1))){
 
    /* copy second string onto end of first string */
    strncpy (&string1[length1], string2, length2);
    string1[length1 + length2] = '\000';
 
    /* return the new string */
    return string1;
 
  } else {
    /* no memory, die */
    exit(1);
  }
 
}
                             

/*
 * Allocate memory for a string, copy the string into the memory and then return the pointer to the memory.
 */
 
char *
strnset (char *string, int length) {
 
  char *pointer_to_string;
 
//    printf("strnset >%d< >%s< \n", length, string);
  if (pointer_to_string = (char *) malloc (length+1))
    {
      strncpy (pointer_to_string, string, length);
      pointer_to_string[length]='\0';
      return (pointer_to_string);
    }
  else
    {
        return strnset("", 0);
    }
}  /* end strset */ 

/*
 *
 */

char *xmlgetdat(char *string) {

    char *begin, *end;
    int i;

    printf("xmlgetdat >%s< \n", string);
    /* Given an XML string return the values inside the tag */
    
    /* Looks like <TAG name="value" > abcd </TAG> */ 
    /* or         <TAG name="value" /> */ 
    /* or         <TAG /> */ 

    /* get the first > */
    begin = strstr(string, ">");

    if (begin==NULL) {
        /* If we can't find beginning, error out */
        /* return the empty string */
    } else if (begin-1 == "/") {
        /* if the previous character is a slash */
        /* return the empty string */
    } else {

        end = strstr(begin, "<");

        if (end != NULL) {
            return strnset(begin+1, end-begin-1);
        }
    }
    return strnset("",1);
}

/*
 *
 */

char *xmlgetval(char *string, char *name) {

    char *begin, *end, *temp;

    printf("xmlgetval >%s< >%s<\n", name, string);
    /* Given an XML string get the value associated with the name given in the location */
    
    /* Looks like <TAG name="value" > abcd </TAG> */ 
    /* or         <TAG name="value" /> */ 
    /* or         <TAG /> */ 

    /* get the first < */
    begin = strstr(string, "<");

    if (begin!=NULL) {

        /* get the first > */
        end = strstr(begin, ">");

        if (end==NULL) {
            /* If we can't find the end, */
            /* return an empty string */
        } else {
            /* we found the first tag and are now going to look for the value */
            /* pull value out temporatily so we don't accedently pull value out of 
               the wrong tag */
            temp=strnset(begin, end-begin);
            begin=strstr(temp, name);

            if (begin != NULL ) {
                begin=begin+strlen(name)+2;
                end=strstr(begin, "\'");
                if (end != NULL) {
                    begin = strnset(begin, end-begin);
                    free(temp);
                    return begin;
                }
            }
            free(temp);
        }
    }
    return strnset("",1);
}

/*
 *
 */

char *xmlgettag(char *string, char *location) {

    char *begin, *end, *loc_part, *begin_tag, *end_tag;
    int i;

    printf("xmlgettag >%s< >%s<\n", location, string);
    /* Given an XML string, return the tag given in the location */

    /* Looks like <TAG name="value" > abcd </TAG> */
    /* or         <TAG name="value" /> */ 
    /* Or         <TAG /> */
    
    /* setup the tags */
    begin_tag=strnset("<", 1);
    begin_tag=concat(begin_tag,location);
    end_tag=strnset("</",2);
    end_tag=concat(end_tag,location);
    end_tag=concat(end_tag,">");

    end=NULL;

    /* get the beginning of the tag */
    begin = strstr(string, begin_tag);
    free(begin_tag);

    if (begin != NULL) {

        /* get the end of the tag */
        end = strstr(string, end_tag);


        if (end == NULL) {
            /* If we can't find end look for /> ending... */
            end = strstr(begin, "/>")+2;
        } else {
            end=end+strlen(end_tag);
        }
    }

    free(end_tag);
    if (end != NULL) {
        /* we found the tag, return it. */
        return strnset(begin, end-begin);
    }

    return strnset("", 0);
}

/*
 *
 */

char *xmlgetloc(char *location){

    char *next;

//    printf("xmlgetloc >%s<\n", location);

    /* Given an location string in the form of */
    /* "" */
    /* or tag */
    /* or tag.tag */
    /* or tag.tag.tag.. */
    /* or tag.tag.tag..name */
    /* return the first value */

    /* get the next period */
    next = strstr(location+1, ".");


    if (next==NULL){
        if (location[0]=='.'){
            if (location[1]=='\0'){
                return strnset(".", 1);
            } else {
                return strnset(location, strlen(location) );
            }
        } else {
            return strnset(location, strlen(location));
        }
    }

    if (next[0]=='.'&&next[1]=='\0'){
        return strnset(next+1, strlen(next) );
    }

    if (next!=NULL) {
        /* we found the tag, return it. */
        return strnset(location, next-location);
    }

}

/*
 *
 */

char *xmlget(char *string, char *location) {

    char *next_loc, *next_loc_a, *value, *next_tag, *tag;

    tag = strnset(string, strlen(string));

    printf("xmlget >%s<\n", tag);

    while (1) {

        if (tag[0]=='\0')
            return strnset("", 0);
        next_loc = xmlgetloc(location);
        location = location+strlen(next_loc);
        if (location[0]=='.')
                location=location+1;


        if (next_loc[0]=='.'){
            next_loc_a=next_loc;
            next_loc=strnset(next_loc_a+1, strlen(next_loc_a)-1 );
            free(next_loc_a);
            if (next_loc[0] == '\0'){
                value = xmlgetdat(tag);
            } else {
                value = xmlgetval(tag, next_loc);
            }
            free (next_loc);
            free(tag);
            return value;
        } else if (!strcmp(next_loc, "")){
            free (next_loc);
            return tag;
        } else {
            next_tag = xmlgettag(tag, next_loc);
            free (next_loc); 
            free(tag);
            tag=next_tag;
            if (location == "") {
                return tag;
            }
        }
    }
}

/*
 *
 */

/* initializes the client data to a known state */
void initialize(int fd) {
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
	buf[BUFFSIZE];

    switch (client[fd].state) {
        case NEW_CONNECTION: {
            printf("NEW_CONNECTION\n");          
            client[fd].state = STREAM;
            } break;
        case STREAM: {
            /* setup a new stream */
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

                    /* load user data */
                    /* load_user(fd, username) */

                    /* if user is already logged in, refuse new connection */

                    /* if password matches */
                    if (!strcmp(password, "1234")) {
                        printf("login good\n");          
                        /* set state to play */ 
                        client[fd].state = PLAY; 
                        /* return good */
                        sprintf(buf,"<iq id='%s' type='result'/>", id);          
                        write(fd, buf, strlen(buf));

                    /* otherwise, return an error and close connection */
                    } else {
                       
                        printf("login failed\n");          
                        client[fd].state = QUIT; 
                    }

                    free (username);
                    free (password);
                    free (resource);
                    free (digest);

                /* register */
                } else if (!strcmp(xmlns,"jabber:iq:register")) { 
                    /* load user data */
                    username = xmlget(client[fd].buffer, "iq.query.username..");
                    password = xmlget(client[fd].buffer, "iq.query.password..");
                    /* does user already exist ? */
                    /* if no, create user, return good. */
                        sprintf(buf,"<iq id='%s' type='result'/>", id);          
                        write(fd, buf, strlen(buf));
                    /* if yes, return error and close connection */
                /*    client[fd].state = QUIT; */

                    free (username);
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
               /* agents */
               /* vcard-temp */

            /* presence */

            /* close stream */

            /* anything else is an error  */

/*
    <<< <iq type='get' id='4'><query xmlns='jabber:iq:agents'/></iq>
    >>> <iq type='result' id='4' from='six' to='jabber@six/Gabber'><query xmlns='jabber:iq:agents'>
 
        <agent jid='users.jabber.org'>
          <name>Jabber User Directory</name>
          <description>You may register and create a public searchable profile, and search for other registered Jabber users.</description>
          <service>jud</service>
          <register/>
          <search/>
        </agent>
 
        <agent jid='conference.six'>
          <name>The conferencing service on mydomain</name>
          <description>Don&apos;t all talk at once!</description>
          <service>conference</service>
          <groupchat/>
          <register/>
        </agent>
 
      </query></iq>

    <<< <iq type='get'><query xmlns='jabber:iq:roster'/></iq>
    >>> <iq type='result' from='jabber@six/Gabber'><query xmlns='jabber:iq:roster'/></iq>        
*/



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


/*
 *
 */

int main(){

    int primary_socket, new_socket;
    struct sockaddr_in sin, new_sin;
    fd_set rfds, afds;
    int fd, nfds, alen;
    int x;
    char line[BUFFER];
    size_t total_buf_size, buf_size, msg_buffer_length, msg_length;

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
 
        fcntl(new_socket, F_SETFL, O_NONBLOCK); 
        if (new_socket == SOCKET_ERROR){
            printf("FATAL ERROR : Select Error.\n");
            exit(1);
        }
        client[new_socket].state=STREAM;
        printf("New connection on file descriptor %d.\a\n",new_socket);
        FD_SET(new_socket,&afds);
    }

    
    /* Cycle thru all open file descriptors */
    for (fd=0; fd<nfds; ++fd)
        if (fd != primary_socket && FD_ISSET(fd,&rfds)) {

            /* server code goes here */
              client[fd].buffer = (char *) calloc(1,BUFFER);
             /* need to check for a memory allocation error here. */
              msg_buffer_length = BUFFER;
              msg_length = 0;

              while((recv(fd, line, 1, 0))>0) {
                  client[fd].buffer[msg_length]=line[0];
                  if (msg_length > msg_buffer_length-2) {
                      msg_buffer_length = msg_buffer_length + BUFFER;
                      client[fd].buffer=(char *)realloc(client[fd].buffer, msg_buffer_length);
                /* need to check for a memory allocation error here. */
                }
                msg_length++;
//                if (client[fd].buffer[0] == '\n')
//                     break;
               }
            client[fd].buf_size=msg_length;
            client[fd].buffer[msg_length-1]='\000';        

//         printf("read from socket: %d >%s<\n",fd,client[fd].buffer);
    
            if (client[fd].buf_size==0){
                write(fd, "</stream:stream>", 17);
                close(fd);
                FD_CLR(fd,&afds);
                printf("%d Closed Connection\n",fd);
            } else {
                printf("%d >%s<\n",fd,client[fd].buffer);
            } /* end else */
            
        printf("sending to client_actions: %d >%s<\n",fd,client[fd].buffer);
            client_actions(fd);

            if (client[fd].state == QUIT){
                write(fd, "</stream:stream>", 17);
                close(fd);
                FD_CLR(fd,&afds);
                printf("%d Closed Connection\n",fd);
            }

//        printf("freeing this: %d >%s<\n",fd,client[fd].buffer);
            free (client[fd].buffer);

        } /* end server code */
    
/*    update_environment(); */
    
    } /* END WHILE */
} /* END MAIN */
