# Generated automatically from Makefile.in by configure.
CC=gcc 

SOURCE= $(wildcard *.c)

OBJECTS= $(subst .c,.o,$(SOURCE))

%.o : %.c
	$(CC) -O2 -c $< -o $@

all: $(OBJECTS) router

router: $(OBJECTS)
	$(CC) -O2 $(OBJECTS) -o router

clean:
	rm *.o 
	rm router

depend:
	makedepend -Y $(SOURCE) > /dev/null 2>&1

# DO NOT DELETE

