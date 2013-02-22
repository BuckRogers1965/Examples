/* Given a set of strings, create a search tree of values */

#ifndef IN_NAMESPACE
typedef void * Node; 
#endif

/*@null@*/ Node * NSCreate ();

           void   NSRelease (Node *);

           int    NSInsert (Node *, char *, long);

           long   NSSearch (Node *, char *);

           int    NSDelete (Node *, char *);
