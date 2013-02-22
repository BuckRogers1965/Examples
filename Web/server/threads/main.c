

/*

Second version of this program.  

Here we take the basic functionality and extend it to use a pool of worker threads

The main thread will
	manage the connections
	manage the threads
	dispatch network events to the threads

The threads will 
	perform all network and file IO
	process the requests

Threading will be done by 
	creating a pool of free threads in a list
	assigning threads work with a connection number
	move threads to working list.
	loop through working list to find free threads.

Sentinal values will be used to communicate between main and threads.


*/

#include <sys/sendfile.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_CLIENT 5000
#define PORT 8080

#define THREADS 100

void nonblock(int sockfd)
{
  int opts;
  opts = fcntl(sockfd, F_GETFL);
  if(opts < 0)
  {
    perror("fcntl(F_GETFL)\n");
    exit(1);
  }
  opts = (opts | O_NONBLOCK);
  if(fcntl(sockfd, F_SETFL, opts) < 0) 
  {
    perror("fcntl(F_SETFL)\n");
    exit(1);
  }
}


void
Initialize(){

}


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
Respond(int fd, char * buf, int n){

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
Respond_simple( int fd, char * buf, int n){

  char response[1024] = {"HTTP/1.1 200 OK\r\n\r\n<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n<TITLE>301 Moved</TITLE></HEAD><BODY>\r\n<H1>Hello World!</H1>\r\n</BODY></HTML>\r\n\r\n"};
  int y = strlen(response);

  printf("%d data received: \n%s\n", fd, buf);
  send(fd, response, y, 0);
  close(fd);

}

void
Loop(){

  struct epoll_event *events;
  struct sockaddr_in srv;
  struct epoll_event ev;

  int listenfd;
  int epfd;
  int clifd;
  int i;
  int res;

  char buffer[1024];
  int n;

  events = (struct epoll_event *)calloc(MAX_CLIENT, sizeof(struct epoll_event));
  
  if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("error opening socket\n");
    exit(1);
  }

  bzero(&srv, sizeof(srv));
  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = INADDR_ANY;
  srv.sin_port = htons(PORT);

  if( bind(listenfd, (struct sockaddr *) &srv, sizeof(srv)) < 0)
  {
    perror("error binding to socket\n");
    exit(1);
  }
  
  listen(listenfd, 1024);

  int reuse_addr = 1;           /* Used so we can re-bind to our port */
  /* So that we can re-bind to it without TIME_WAIT problems */
  setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr,
              sizeof (reuse_addr));

  epfd = epoll_create(MAX_CLIENT);
  if(!epfd)
  {
    perror("epoll_create\n");
    exit(1);
  }
  ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
  ev.data.fd = listenfd;
  if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0)
  {
    perror("epoll_ctl, failed to add listenfd\n");
    exit(1);
  }


  for( ; ; )
  {
    usleep(8000);
    res = epoll_wait(epfd, events, MAX_CLIENT, 0);
    for(i = 0; i < res; i++)
    {
      if(events[i].data.fd == listenfd)
      {
        clifd = accept(listenfd, NULL, NULL);
        if(clifd > 0)
        {
          printf(".");
          nonblock(clifd);
          ev.events = EPOLLIN | EPOLLET;
          ev.data.fd = clifd;
          if(epoll_ctl(epfd, EPOLL_CTL_ADD, clifd, &ev) < 0)
          {
            perror("epoll_ctl ADD\n");
            exit(1);
          }
        }
      }
      else {

	/* Handle All this in the thread  */
        n = recv(events[i].data.fd, buffer, 1023, 0);
        if(n == 0)  /* closed connection */
        {
          epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
        }
        else if(n < 0)  /* error, close connection */
        {
          //epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
	  close(events[i].data.fd);
        }
        else {  /* got a request, process it. */
          //send(events[i].data.fd, buffer, n, 0);
          //bzero(&buffer, n);
          //printf("%d data received: \n%s\n", events[i].data.fd, buffer);

          //send(events[i].data.fd, response, y, 0);
	  //close(events[i].data.fd);

	  Respond(events[i].data.fd, buffer, n);

        }

      }
    }
  }

}

void Shutdown(){

}

int main (){

  Initialize();
  Loop();
  Shutdown();

  exit(0);
}
