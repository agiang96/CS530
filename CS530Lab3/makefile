#Members: Alexander Giang, Shawn Chua
#Class Users: cssc0885, cssc0894
#REDID: 818285579, 817662151
#Class Information: CS530, Spring 2017 
#Assignment #3, Assignment/Expression Parser
#Filename: makefile

CC=g++
CFLAGS=-c
SOURCES=parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=parse

all: $(SOURCES) $(EXEC) 

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o core $(EXEC)
