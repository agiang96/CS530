Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
Class Users: cssc0885, cssc0894, cssc0880, cssc0857
REDID: 818285579, 817662151, 819377332, 817862169
Class Information: CS530, Spring 2017 
Assignment #2, XE Disassembler 
Filename: README.txt
Due Date: April 17, 2017

File manifest: README.txt, makefile, RecordReader.cpp, RecordReader.h,
disassembler.cpp, disassembler.h, opTable.cpp, opTable.h, readFile.cpp, 
readFile.h, symTabReader.cpp, symTabReader.h

Compile instructions:
	- On the command prompt, call make -f makefile to compile the entire program.
		
Operating instructions:
	- Type `dasm <filename>` to execute the disassembler,
	  where <filename> is a .obj file to process. If the file is not 
	  an .obj file, the program will declare an ERROR and promptly exit.
	  Having the accompanying .sym file is necessary as well or the program
	  will not run.
	
List/description of novel/significant design decisions
        - We first looked at the sample object code provided and attempted to
	  disassemble the entire thing by hand. From there as we disassembled
	  each instruction, we came up with various algorithms to deal with 
	  specific cases such as register to register instructions in format 2
	  and differentiating formats 3 and 4 as well as determining the 
	  accompanying flags.
	- Our initial approach was to have each member design the code for 
	  individual parts of the program such as taking the object code and
	  storing it into a string, find all symbols and literals with their 
	  accompanying addresses and other data associated with them, 
	  creating an opTable to refer to pull out the respective mneumonics of
	  each opCode, and finally a RecordReader which processes the Header,
	  Text, Modification, and End Records.
	- We first thought of having public global variables to call from other classes,
	  but we ended up creating get() methods instead, which makes more sense
	  and easier to implement.
	- Once the symTabReader and readFile was finished, they were tied together
	  into the disassembler.cpp which deals with error cases in order to make
	  preparations for the RecordReader such as pulling out all symbols, literals,
	  and the object code.
	- The RecordReader is where all of our work links together for the finished
	  .sic file.
	
List/description of any extra features/algorithms/functionality you 
included which were not required
	- We used the c++ helper class, <vector> in order to store all of our data
	  as opposed to using an array because we wanted this program to work for
	  any objectCode other than the sample.obj file provided. If we had a
	  fixed-sized array, there will be potential error cases.
	- We also used nested classes in which we had vectors of. For example, the 
	  symTabReader uses a nested class which simply holds the Symbol Name,
	  it's Address, and Flag and so we created a vector that stores multiples
	  of these in order to keep everything organized. We followed the same 
	  approach with the opTable as well, to contain the respective opCode,
	  mneumonic, and format.
	
List/description of all known deficiencies or bugs
	- n/a

Lessons Learned
	- Communication is Key, especially while working in a team
	- Setting deadlines for each other so that we could progress as a whole.
	- GitHub practice
	- Proper Research(learning more C++)
	- Software Engineering
	- Increased our knowledge of the SIC/XE Machine
	
