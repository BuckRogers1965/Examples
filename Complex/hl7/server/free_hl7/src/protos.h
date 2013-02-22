/* logging functions */

void notify(char *, int , char *);


/* parent functions */ 

void configure ( int , char *[], struct conf_t * );
void initialize ( struct conf_t * ) ;
void become_deamon ( struct conf_t * ) ;
void shutdown_main ( struct conf_t * ) ;
int spawn_children ( struct conf_t * ) ;


/* child functions */

void child_loop (struct conf_t *, struct node_t *);


/* interprocess comunication functions */

int init_ipc (struct node_t *);
int init_parent_ipc (struct node_t *);
int clear_parent_ipc (struct node_t *);
int init_child_ipc (struct node_t *);
int write_to_child (struct node_t *, char *);
int write_to_parent (struct node_t *, char *);
int read_from_child (struct conf_t *);
int read_from_parent (struct node_t *);
int parse_command (struct conf_t *, struct node_t *);
int communicate (struct conf_t *);


/* open protocol */

int protocol_open (struct node_t *);
char * protocol_get (struct node_t *);
int protocol_put (struct node_t *, char *);
int protocol_close (struct node_t *);

char * strset (char *);
char * strtok(char *, const char *);               
