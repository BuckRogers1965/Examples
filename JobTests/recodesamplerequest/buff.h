/*
  buff 

  Dynamic Buffer

*/

typedef void * buff;

enum {buff_default=1, buff_FixCarbon, buff_NormalizeLineEnds};

/********************************************
  to create a new buffer
  given an initial size
  returns a pointer to an allocated buff
  or NULL if can't allocate memory
*/

buff
buffCreate (unsigned int size);

/********************************************
  to destroy a buffer that you have previously created
  given a previously allocated buff
  returns a 1 if good, 0 if failed
*/

int
buffDestroy (buff buffer);

/********************************************
  to add a block to the end of the buffer

  given a buff, a pointer to memory and a length

  returns a 1 if added, 0 if failed
  if you get a 0 then the current data in the buffer
  is still good
*/

int
buffAdd (buff buffer, char * pointer, unsigned int length);


/********************************************

  to get a single line from the buffer

  give a buff, and pointer to a pointer

  return length found, or 0 if nothing to find
  pointer is pointed at beginning of string to send, or NULL if error
*/

unsigned int
buffGetLine (buff buffer, char ** pointer);

/********************************************

  to get a block of text from the head of the buffer 

  give a buff, a pointer to a pointer, and a maximum length

  return length found, or 0 if nothing to find 
  pointer is pointed at beginning of block to send, or NULL if error
*/

unsigned int
buffGetBlockFromHead (buff buffer, char ** pointer, unsigned int length);

/********************************************

  to get the entire contents of the buffer

  give a buff, a pointer to a pointer

  return length found, or 0 if nothing to find 
  pointer is pointed at beginning of block to send, or NULL if error
*/

unsigned int
buffGetBuffer (buff buffer, char ** pointer);

/********************************************

  undo the previous get

  Sometimes we can't write to a device yet, so we have to put the data back

  given a buff, and an undo length

  return 0 if we can't back up as far as requested 
  return 1 if we backed up the previous amount

  the buffer is only reset by adding to it.  
  so as long as you read a part of the buffer
  and then undo before any adds you will be able to 
  rewind at least as much as you were just handed
*/

int
buffGetUndoTail (buff buffer, unsigned int length);

int
buffGetUndoHead (buff buffer, unsigned int length);

/********************************************

  to clear the buffer 

  given a buff, reset all internal pointers to empty state 

  return a 0 if a NULL object
  return a 1 if succeeded
*/

int
buffClear (buff buffer);

/********************************************

  to get the size of a buffer

  given a buff

  return current allocated size
*/

unsigned int
buffGetSize (buff buffer);

/********************************************

  to get the length of the contents of the buffer

  given a buff

  return the length of the contents of the buffer
*/

unsigned int
buffGetLength (buff buffer);

/********************************************

  to get the count of the times that the add routine has moved a buffer forward

  given a buff

  return the count
*/

unsigned int
buffCountMovedForward (buff buffer);

/********************************************

  to get the count of the times that the add routine has reset an empty buffer

  given a buff

  return the count
*/

unsigned int
buffCountResetEmpty (buff buffer);

/********************************************

  to get the count of the number of reallocs

  given a buff

  return the count
*/

unsigned int
buffCountReallocs (buff buffer);

/********************************************

  to get the count of the inserts

  given a buff

  return the count
*/

unsigned int
buffCountInserts (buff buffer);

/********************************************

  to get the count of the number of times data has been retrieved

  given a buff

  return the count
*/

unsigned int
buffCountRetrievals (buff buffer);

/********************************************

  to get the count of the number of times data has been retrieved

  given a buff

  return the count
*/

unsigned int
buffTotalCount ();

/********************************************

  to get the total size of all allocated buffers

  given a buff

  return the total allocated buff sizes
*/

unsigned int
buffTotalSize ();

/********************************************
  to resize the block to the given length, or the size of the contents, which ever is bigger

  given a buff, a pointer to memory and a length

  returns a 1 if succeed, 0 if failed
*/

int
buffResize (buff buffer, unsigned int length);

/********************************************

  change the default offset of additional memory allocated when we realloc the buffer

  given a buff and a newSize for the realloc adustment
  default is 4096
  max value is (2^20)MB

  return 1 on success, 0 if new size is out of rante, ot the buffer is NULL
*/

unsigned int
buffReallocAdjustment (buff buffer, unsigned int newSize);

/********************************************

  to get a block of text from the tail of the buffer

  give a buff, a pointer to a pointer, and a maximum length

  return length found, or 0 if nothing to find
  pointer is pointed at beginning of block to send, or NULL if error
*/

unsigned int
buffGetBlockFromTail (buff buffer, char ** pointer, unsigned int length);

/********************************************

  to mark the current position in the buffer

  give a buff

  return 0;
*/

unsigned int
buffMark (buff buffer);

/********************************************

  to rewind to the mark in the buffer

  give a buff

  return 0;
*/

unsigned int
buffRewindToMark (buff buffer);


