

typedef void * Connect;

/*  Will set up the datastructures to support int connections*/
void ConnectInitialize (int);

/* Clear the buffers for that connection */
int ConnectClear (int);

/* Check to see if the Connection is busy */
int ConnectBusy (Connect *);

/* Set the connection to busy */
int IsConnectBusy (Connect *);

/* Clear the busy flag in the connection */
int ConnectClearBusy (Connect *);

/* Given a File Descriptor, get the data handle for that fd */
Connect * ConnectGet(int);

/* Get the databuffer for the connection */
char * ConnectGetBuf(Connect *);

/* Clean up a little, set to busy */
int ConnectClose (int);

