CC=gcc
CFLAGS=-c -g -Wall 
LDFLAGS=
SOURCES=myspell.c linearsearch.c binarysearch.c hashsearch.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=myspell

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.myspell: clean

clean:
	rm -rf *.o myout.txt myspell
