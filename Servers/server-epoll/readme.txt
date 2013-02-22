Written on 12 July 2012 by James M. Rogers.

I wrote this to learn more about epoll server.  I wrote a very simple webserver a few days ago using epoll and sendfile.  With the code all in a single file it was hard to see where the web server code ended and the network code began.  I had previously written a similar example code for select many years ago and started by copying these files and making all the changes I needed to make it work for epoll.  


This is generic network server code. 

It uses epoll instead of select so it can scale to much greater numbers of connections. This is just sample code 


Improvements:
 o Extend this to get more control over the network connection.
	Server->timeout  // controls how long we wait for data on this connection.  

 o Client info.  So we can get info about the client connection we are currently processing.
	ip
	port

 0 Add return value to newconn() so we can close a connection 


server.c
--------

This contains code that handles all the network operations.

You should not have to make many changes to this file.  All network specific code is in this file, and all your code goes into the client file.

Then you run 

	gcc *.c -o server_example

You run the program by typing 

	./server_example 

In another terminal type 

	telnet localhost 8080


The sample code will print a '+' each time you get a connection, and a '-' each time a connection closes.  

server.h
--------

This file containts the interface to the server object.  Will be completely documented.  Read this file to see how it works.


client.c
--------

Example code.  Demonstrates how to create and configure a single server object with callback functions to handle new connections, requests, and closed connections.  You could set up and run several network objects.

The first callback for a particular client will always be a new connection.  This happens as soon as the connection is accepted.  After this you can get any number of datapackets, and finally the last thing you can get on that connection is a close.  


