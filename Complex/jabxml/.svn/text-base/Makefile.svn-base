# Generated automatically from Makefile.in by configure.
CC=gcc 

SOURCE= $(wildcard *.c)

OBJECTS= $(subst .c,.o,$(SOURCE))

%.o : %.c
	$(CC) -O6 -I/usr/local/jabber/include -c $< -o $@

all: $(OBJECTS) xml_test

xml_test: $(OBJECTS)
	$(CC)  -L/usr/local/jabber/lib -lxode $(OBJECTS) -o xml_test

clean:
	rm *.o 
	rm xml_test

depend:
	makedepend -Y $(SOURCE) > /dev/null 2>&1

# DO NOT DELETE

