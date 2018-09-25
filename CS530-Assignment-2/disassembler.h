/******************************************************************************
 * Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * Filename: disassembler.h
 * Description: Header file for disassembler.cpp
 ******************************************************************************/
#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "readFile.h"
#include "symTabReader.h"
#include "RecordReader.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <vector>

class disassembler
{
public:
     /**
    * Function Name: main
    * Function Prototype: int disassembler::main(parameters)
    * Description: The Disassembler. Receives the necessary
    *    .obj file contents from readFile, symTab contents 
    *    from the symTabReader, error checks for any
    *    possible cases, and runs the recordReader to process
    *    the entire object code.
    * Parameters: int argc, the number of arguments
    *             char*argv[], the argument strings
    * Return Values: 0 if failure, 1 if process correctly.
    */
   int main(int argc, char *argv[]);
};

#endif
