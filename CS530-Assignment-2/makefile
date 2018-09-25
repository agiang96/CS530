################################################################################
# File Name: makefile
# Names: Alex Giang, Michael Yee, Shawn Nehemiah Chua, Tony La
# Class Accounts: cssc0885, cssc0894, cssc0880, cssc0857
# REDID: 818285579, 817662151, 819377332, 817862169
# Date: April 17, 2017
# Description: Makefile for CS530 Assignment #2
#
# -- To use, simply run the line: make -f makefile
# -- The output file will be called "dasm"
###############################################################################

# CC tells makefile to compile using g++ for .cpp files
# FILEX, for X = 1, 2, 3, etc. are the names of the files to be compiled
# OFLAG is the -o flag for g++
# OUT is the name of the output file

CC = g++
FILE1 = "disassembler.cpp"
FILE2 = "readFile.cpp"
FILE3 = "symTabReader.cpp"
FILE4 = "RecordReader.cpp"
FILE5 = "opTable.cpp"
OFLAG = -o
WFLAG = -w
OUT = "dasm"

all:
	$(CC) $(FILE1) $(FILE2) $(FILE3) $(FILE4) $(FILE5) $(WFLAG) $(OFLAG) $(OUT)

