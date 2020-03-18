#Christian Cortez , cssc1965
# CS530, Spring 2020
#Assignment #1, Hex/Binary Dump
#makefile


CC=g++
CFLAGS=-c
SOURCES=dbx.cpp binaryDump.cpp hexDump.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=dbx 

all: $(SOURCES) $(EXEC) 

$(EXEC): $(OBJECTS)
        $(CC) $(OBJECTS) -o $@

.cpp.o:
        $(CC) $(CFLAGS) $< -o $@

clean:
        rm -rf *o core $(EXEC)
