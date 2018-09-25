Members: Alexander Giang, Shawn Chua 
Class Users: cssc0885, cssc0894 
Class Information: CS530, Spring 2017 
Assignment #1, HexDump 
Filename: README.md 

File manifest: README.md, xsd.cpp, hex.cpp, bin.cpp, xsd.h, makefile

Compile instructions:
	- Type `make` and it will compile everything
		
Operating instructions:
	- Type `xsd <filename>` to execute the hexdump
	- Type `xsd -b <filename>` to execute the binary version
	
List/description of novel/significant design decisions
	- We had everything in the main class, but we decided to 
	split up the hex and binary dumps into different functions 
	with a header file
	
List/description of any extra features/algorithms/functionality you 
included which were not required
	- n/a
	
List/description of all known deficiencies or bugs
	- There may be some warnings during compile, but it will run fine

Lessons Learned
	- Coordination/Communication(ie. learning GitHub), finding 
	information and adapting it to our own program(ie. Learning C++)
