Written on 12 July 2012 by James M. Rogers.

Now that we have the web server running on the new server object we are going to extend the web server to handle all the client connections in a separate thread.

I am going to keep this simple, so it doesn't hide the way the threads are interacting with the main process.   We just want the worker threads to get a copy of the request and work with it.

--

buffer either needs to be copied, or written into the proper location in the first place.  Easiest thing to do is to just let the worker thread do the read and the write itself.  This would speed things up the most as well.  This way the main thread is just managing the connections, the thread lists and passing data requests to the next available thread.

--



We need to have two lists of threads.

	free list
	working list

The free list is made up of threads that are not working on anything.  

The working list is made up of threads that have been given a request to work on. 

This means that we have to create threads in advance.


--

What happens if no threads are available to work requests?  

wait a bit, see if any threads have completed, then continue.

  If we are busy too long, send http response that server is busy.

--

When we get a request, call back and handle the response.  

	Get the data handle for this connection.
	If the connection data is busy, 
		just skip this for now.
		it will come back around again.
	Get next free worker thread.
	place file descriptor in thread.
        place connection data structure in thread. 
	Set flag in worker thread

  // Find connection handle.

  // If connection is busy, return.

  // Get handle for free worker thread.

  // place file descriptor in thread.

  // place connection data structure in thread. 

  // Set flag in worker thread

--

In the main loop, check for completed threads and move them to end of free list.



