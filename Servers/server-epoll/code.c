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



void
NewConn (int fd)
{
  printf("+");
  fflush(stdout);
}


void
NewData (int fd, char *data, int size)
{
  //printf("%s\n", data);
  printf(".");
  fflush(stdout);
}


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
    usleep(8000);
    ServerLoop (New);
  }
  ServerClose (New);
  ServerDel (New);
  return 0;
}
