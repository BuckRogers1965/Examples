# Generated automatically from Makefile.in by configure.
CC=gcc 

SOURCE= $(wildcard *.c)

OBJECTS= $(subst .c,.o,$(SOURCE))

%.o : %.c
	$(CC) -O6 -c $< -o $@

all: $(OBJECTS) jim

jim: $(OBJECTS)
	$(CC) $(OBJECTS) -o jim

clean:
	rm *.o 
	rm jim

depend:
	makedepend -Y $(SOURCE) > /dev/null 2>&1

# DO NOT DELETE

