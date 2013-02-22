#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sched.h>
#include <pthread.h>


typedef struct thread
{
  int Running;
  int fd;
  pthread_t thread;
  char buffer[1024];
  struct thread *next;
  struct thread *prev;
} thread;


struct thread *freelist;
struct thread *worklist;


/* Parse and return file handle for http get request */
int
OpenFile (char *buf, int n)
{

  int i, j;
  char *index = { "index.html" };
  char path[1024];

  if (buf == NULL || n < 10)
    return 0;

  // Ensure that the string starts with "GET "
  if (!buf[0] == 'G' || !buf[1] == 'E' || !buf[2] == 'T' || !buf[3] == ' ')
    return 0;

  // copy the string
  for (i = 0; i < n && buf[i + 4] != ' '; i++)
    path[i] = buf[i + 4];

  // put null on end of path
  path[i] = '\x00';

  // if the syntax doesn't have a space following a path then return
  if (buf[i + 4] != ' ' || i == 0)
    return 0;

  // if the last char is a slash, append index.html 
  if (path[i - 1] == '/')
    for (j = 0; j < 12; j++)
      path[i + j] = index[j];

  printf ("Found path: \"%s\"\n", path);

  // the +1 removes the leading slash
  return (open (path + 1, O_RDONLY));
}

void
HandleResonse (int fd, char *buf, int n)
{
  char badresponse[1024] =
    {
"HTTP/1.1 404 Not Found\r\n\r\n<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n<TITLE>Not Found</TITLE></HEAD><BODY>\r\n<H1>Not Found</H1>\r\n</BODY></HTML>\r\n\r\n"
};
  char goodresponse[1024] = { "HTTP/1.1 200 OK\r\n\r\n" };
  int fh;
  fh = OpenFile (buf, n);

  if (fh > 0)
    {
      struct stat stat_buf;	/* hold information about input file */
      send (fd, goodresponse, strlen (goodresponse), 0);
      /* size and permissions of fh */
      fstat (fh, &stat_buf);
      sendfile (fd, fh, NULL, stat_buf.st_size);
      close (fh);
    }
  else
    {
      send (fd, badresponse, strlen (badresponse), 0);
    }
}

void *
handleRequest (void *arg)
{

  struct thread *t = (thread *) arg;
  int n;

  for (;;)
    {

      while (!t->Running)
	{
	  usleep (2000);
	}

      n = recv (t->fd, t->buffer, 1023, 0);

      if (n > 0)
	{  // got a request, process it.
	  HandleResonse (t->fd, t->buffer, n);
	}
	
      close (t->fd);
      t->Running = 0;
    }
}

void
ThreadInitialize (int ThreadCount)
{

  struct thread *t;
  int i;

  freelist = worklist = NULL;

  for (i = 0; i < ThreadCount; i++)
    {
      t = (struct thread *) calloc (sizeof (thread), 1);

      // add new thread structure to freelist 
      t->next = freelist;
      t->prev = NULL;
      freelist = t;

      if (pthread_create (&t->thread, NULL, &handleRequest, t) == -1)
	{
	  perror ("pthread create failed\n");
	  exit (1);
	}
    }

}


void
ThreadCheck ()
{
  struct thread *t = freelist;

  // If a thread on the worklist is not running, move it to the head of the freelist;

  if(!t->Running) {
  
  // remove thread structure from worklist 


  if (worklist == t)
    worklist = t->next;
  if (t->next)
    if (t->prev)
      t->prev->next = t->next;
    else 
      t->next->prev = NULL;
  if (t->prev)
    if (t->next)
      t->next->prev = t->prev;
    else
      t->prev->next = NULL;

  // add thread structure to freelist 
  t->next = freelist;
  if (t->next)
    t->next->prev = t;  
  t->prev = NULL;
  freelist = t;
  }

}


void
ThreadHandleResponse (int fd)
{

  struct thread *t;

  /* wait for any child process to free up */
  while (freelist == NULL)
    {
      ThreadCheck ();
      sched_yield();
    }

  // remove thread structure from freelist 
  t = freelist;
  freelist = t->next;
  if (t->next)
    t->next->prev = NULL;
  t->prev = NULL;

  // add thread structure to worklist 
  t->next = worklist;
  if (t->next)
    t->next->prev = t;  
  t->prev = NULL;
  worklist = t;

  // setup thread and run it
  t->fd = fd;
  t->Running = 1;

}
