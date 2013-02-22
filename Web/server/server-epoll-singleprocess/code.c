/* James M. Rogers */
/* Copyright 2012  */

#include "server.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>


/* Parse and return file handle for http get request */
int
OpenFile(char * buf, int n){

  int i, j;

  char * index = {"index.html"};

  char path[1024];

  if (buf==NULL || n<10)
	return 0;

  // Ensure that the string starts with "GET "
  if (!buf[0]=='G' || !buf[1]=='E' || !buf[2]=='T' || !buf[3]==' ')
	return 0;

  // copy the string
  for (i=0; i < n && buf[i+4]!=' '; i++)
    path[i]=buf[i+4];  

  // put null on end of path
  path[i]='\x00';

  // if the syntax doesn't have a space following a path then return
  if (buf[i+4]!=' ' || i == 0)
	return 0;

  // if the last char is a slash, append index.html 
  if (path[i-1] == '/')
	for (j=0; j<12; j++)
		path[i+j]=index[j];

  printf("Found path: \"%s\"\n", path);

  // the +1 removes the leading slash
  return (open(path+1, O_RDONLY));
}


void
NewData(int fd, char * buf, int n){

  char badresponse[1024] = {"HTTP/1.1 404 Not Found\r\n\r\n<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n<TITLE>Not Found</TITLE></HEAD><BODY>\r\n<H1>Not Found</H1>\r\n</BODY></HTML>\r\n\r\n"};
  char goodresponse[1024] = {"HTTP/1.1 200 OK\r\n\r\n"};

  int fh; 

//  printf("%d data received: \n%s\n", fd, buf);
  
  fh = OpenFile(buf, n);

  if (fh > 0){

    struct stat stat_buf;  /* hold information about input file */

    send(fd, goodresponse, strlen(goodresponse), 0);

    /* size and permissions of fh */
    fstat(fh, &stat_buf);
    sendfile(fd, fh, NULL, stat_buf.st_size);
    close(fh);

  } else {

    send(fd, badresponse, strlen(badresponse), 0);
  }
  close(fd);
}



void
NewConn (int fd)
{
  printf("+");
  fflush(stdout);
}

/*
void
NewData (int fd, char *data, int size)
{
  //printf("%s\n", data);
  printf(".");
  fflush(stdout);
}
*/

void
ConnClose (int fd)
{
  printf("-");
  fflush(stdout);
}

int
main ()
{
  Server *New;

  New = ServerNew ();

  SetPort (New, 8080, 25);
  SetCallbacks (New, NewConn, NewData, ConnClose);
  ServerOpen (New);
  while(ServerRunning(New)){
    usleep(1000);
    ServerLoop (New);
  }
  ServerClose (New);
  ServerDel (New);
  return 0;
}
