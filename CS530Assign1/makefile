#Members: Alexander Giang, Shawn Chua
#Class Users: cssc0885, cssc0894
#Class Information: CS530, Spring 2017
#Assignment #1, HexDump
#Filename: makefile

CC=g++
CFLAGS=-c
SOURCES=xsd.cpp bin.cpp hex.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=xsd

all: $(SOURCES) $(EXEC) 

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o core $(EXEC)
