#include "includes.h"

/*
   loads the main data structures from the file specified
   as the first argument from the command line
*/

void configure ( int argc, char *argv[], struct conf_t *conf ) {

    FILE *stream;            /* need a stream pointer of type FILE */ 
    int previous = CONF_LOAD;
    char line[BUFFER];         /* a single line */
    char *token;
    char *keyword;
    struct node_t *current_node;
    struct thread_t *current_thread;

     notify(__FILE__, __LINE__, "Beginning configure");
   /* read command line */

    stream = fopen(argv[1], "r"); 

    if ( stream == (FILE *)0) {
        notify(__FILE__, __LINE__, "Failed to open configuration file");
        exit (1);
    }
   
   /* read configuration file */
    while ( fgets(line, BUFFER, stream) != (char *)NULL ){

        /* break the file into a list of tokens */
        token = "";
        if (strlen(line) > 1){
            /* process the file one token at a time */
            while (1){
                if (strlen(token) == 0){
                    token = (char *) strtok(line, " \t\n");
                } else {
                    token = (char *) strtok( (char *) NULL, " \t\n");
                }
                if (token == (char *) NULL){
                    break;
                }

                /* a state machine to load the configuration file */   

                if (previous == CONF_KEYWORD){
                    if (!strcmp(keyword, "state")){
                       if(!strcmp(token, "stop")){ 
                           conf->state=STOP;
                       } else if(!strcmp(token, "start")){ 
                           conf->state=START;
                       } else if(!strcmp(token, "running")){ 
                           conf->state=RUNNING;
                       } else {
                           conf->state=STOP;
                       }
                    } else if (!strcmp(keyword, "confname")){
                       conf->confname= (char *) strset(token);
                    } else if (!strcmp(keyword, "homedir")){
                       conf->homedir=(char *)strset(token);
                    } else if (!strcmp(keyword, "logdir")){
                       conf->logdir=(char *)strset(token);
                    } else if (!strcmp(keyword, "deamon")){
                        if (!strcmp(token, "yes")){
                            conf->deamon = YES;
                        } else {
                            conf->deamon = NO;
                        }
                    } else if (!strcmp(keyword, "libdir")){
                       conf->libdir=(char *)strset(token);
                    } else if (!strcmp(keyword, "messagesdir")){
                       conf->messagesdir=(char *)strset(token);
                    } else if (!strcmp(keyword, "configure")){
                       conf->confname=(char *)strset(argv[1]);
                    } else {
                        notify(__FILE__, __LINE__, "Incorrect Configuration Syntax");
                    }
                    previous = CONF_LOAD;
                } else if (previous == CONF_LOAD){
                        keyword = token;
                    if (!strcmp(token, "node")){
                        previous = NODE_KEYWORD;
                    } else {
                        previous = CONF_KEYWORD;
                    }
                } else if (previous == NODE_KEYWORD) {
                    /* load the value into the variable just specified */

                    if (!strcmp(keyword, "node")){
                        /* create a new node and add to end of node list */
                        /* keep a pointer to the current node */
                        current_node=conf->nodes;
                        if (current_node == (struct node_t *)NULL){
                            if((conf->nodes=(struct node_t *) malloc(sizeof(struct node_t)))){
                                current_node = conf->nodes;
                                current_node->next=(struct node_t *)NULL;
                                current_thread=(struct thread_t *)NULL;
                            } else {
                            }
                        } else {
                            while(current_node->next!=NULL){
                                current_node=current_node->next;
                            }
                            if((current_node->next=(struct node_t *) malloc(sizeof(struct node_t)))){
                                current_node = current_node->next;
                                current_node->next=(struct node_t *)NULL;
                                current_thread=(struct thread_t *)NULL;
                            } else {
                            }
                        }
                       current_node->name=(char *)strset(token);
                    } else if (!strcmp(keyword, "state")){
                       if(!strcmp(token, "stop")){ 
                           current_node->state=STOP;
                       } else if(!strcmp(token, "start")){ 
                           current_node->state=START;
                       } else if(!strcmp(token, "running")){ 
                           current_node->state=RUNNING;
                       } else {
                           current_node->state=STOP;
                       }
                    } else {
                        notify(__FILE__, __LINE__, "Incorrect Configuration Syntax");
                        printf("Ignoring this keyword value pair: %s %s\n", keyword, token);
                    }
                    previous = NODE_LOAD;
                } else if (previous == THREAD_KEYWORD) {
                    if (!strcmp(keyword, "thread")){
                        /* create a new thread and add to end of the */
                        /* thread list for the current node */
                        /* keep a pointer to the current thread */
                        if (current_thread == (struct thread_t *)NULL){
                            if((current_node->threads=(struct thread_t *) malloc(sizeof(struct thread_t)))){
                                current_thread = current_node->threads;
                            } else {
                                /* die */
                            }
                        } else {
                            while(current_thread->next!=(struct thread_t *)NULL){
                                current_thread=current_thread->next;
                                current_thread->next=(struct thread_t *)NULL;
                            }
                            if((current_thread->next=(struct thread_t *) malloc(sizeof(struct thread_t)))){
                                current_thread = current_thread->next;
                                current_thread->next=(struct thread_t *)NULL;
                            } else {
                                /* die */
                            }
                        }
                       if(!strcmp(token, "source")){ 
                           current_thread->direction=SOURCE;
                       } else if(!strcmp(token, "dest")){ 
                           current_thread->direction=DEST;
                       } else {
                           current_thread->direction=DEST;
                       }
                       current_thread->filename=(char *)NULL;
                       current_thread->name=(char *)strset(token);
                    } else if (!strcmp(keyword, "timeout")){
                       current_thread->timeout=atoi(token);
                    } else if (!strcmp(keyword, "port")){
                       current_thread->port=atol(token);
                    } else if (!strcmp(keyword, "ack")){
                       if(!strcmp(token, "yes")){ 
                           current_thread->ack=YES;
                       } else if(!strcmp(token, "no")){ 
                           current_thread->ack=NO;
                       } else {
                           current_thread->ack=YES;
                       }
                    } else if (!strcmp(keyword, "type")){
                       if(!strcmp(token, "tcp")){ 
                           current_thread->type=TCP;
                       } else if(!strcmp(token, "file")){ 
                           current_thread->type=DISK;
                       } else {
                           current_thread->type=TCP;
                       }
                    } else if (!strcmp(keyword, "direction")){
                    } else if (!strcmp(keyword, "model")){
                       if(!strcmp(token, "server")){ 
                           current_thread->model=SERVER;
                       } else if(!strcmp(token, "client")){ 
                           current_thread->model=CLIENT;
                       } else {
                           current_thread->model=SERVER;
                       }
                    } else if (!strcmp(keyword, "host")){
                       current_thread->host=(char *)strset(token);
                    } else if (!strcmp(keyword, "dbname")){
                       current_thread->dbname=(char *)strset(token);
                    } else if (!strcmp(keyword, "host")){
                       current_thread->host=(char *)strset(token);
                    } else if (!strcmp(keyword, "filename")){
                       current_thread->filename=(char *)strset(token);
                    } else {
                        notify(__FILE__, __LINE__, keyword);
                        notify(__FILE__, __LINE__, "Incorrect Configuration Syntax");
                        printf("Ignoring this keyword value pair: %s %s\n", keyword, token);
                    }
                    previous = THREAD_LOAD;
                } else {
		    /* just hit a keyword */
                    keyword = token;
                    if (!strcmp(token, "thread")){
                        previous = THREAD_KEYWORD;
                    } else if (!strcmp(token, "node")){
                        previous = NODE_KEYWORD;
                    } else if (!strcmp(token, "configure")){
                        previous = CONF_KEYWORD;
                    } else {
                        /* still working with previous configuration level */
                        if (previous == THREAD_LOAD){
                            previous = THREAD_KEYWORD;
                        } else if (previous == NODE_LOAD){
                            previous = NODE_KEYWORD;
                        } else if (previous == CONF_LOAD){
                            previous = CONF_KEYWORD;
                        } else {
                            /* Should never get here */
                            notify(__FILE__, __LINE__, "Bizare State Machine State.");
                            exit (0);
                        }
                    }
                }
            }
        }
    }
    if ( previous != THREAD_LOAD) {
       notify(__FILE__, __LINE__, "Incorrect Configuration Syntax.");
       notify(__FILE__, __LINE__, "Values must be entered as Key Value pairs seperated by whitespace.");
       exit (1);
    }
    fclose(stream);
}  /* end configuration */

