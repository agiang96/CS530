/* Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * Filename: symTabReader.h
 */

#ifndef SYMTABREADER_H
#define SYMTABREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "readFile.h"

using namespace std;

class symTabReader {
    public:
        //symbol vector class
        class symbols {
            public:
                string name;
                int addr;
                string flag;
                symbols(string n, int a, string f);
        };
        //literal vector class
        class literals {
            public:
                string lit;
                int length;
                int addr;
                literals(string li, int le, int a);
        };
    
    // used to store the contents of the SYMTAB
    vector<symbols> s;
    //used to store the contents of the LITTAB
    vector<literals> l;

    /**
     * Function Name: symTabRead
     * Function Prototype: void symTabReader::symTabRead()
     * Description: Reads and stores the SYMTAB and LITTAB.
     * Parameters: string of the .sym file name
     * Return Values: None
     */
    void symTabRead(string filename);
    
    /**
     * Function Name: getSymbolVector
     * Function Prototype: void symTabReader::getSymbolVector()
     * Description: gets a symbol and its parameters
     * Parameters: index of the symbol
     * Return Values: symbol name, address, or flag
     */
    vector<symbols> getSymbolVector();
    
    /**
     * Function Name: getLiteralVector
     * Function Prototype: void symTabReader::getLiteralVector()
     * Description: gets a literal and its parameters
     * Parameters: index of the literal
     * Return Values: literal, length, or address
     */
    vector<literals> getLiteralVector();
};

#endif
