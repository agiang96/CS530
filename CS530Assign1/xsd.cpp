/* 
 * Members: Alexander Giang, Shawn Chua 
 * Class Users: cssc0885, cssc0894
 * Class Information: CS530, Spring 2017
 * Assignment #1, HexDump
 * Filename: xsd.cpp
 */

#include <iostream>
#include <bitset>
#include <iomanip>
#include <fstream>
#include "xsd.h"

using namespace std;

int main(int argc, char* argv[]) {    
    string file;
    file = argv[1];

    if(file == "-b"){
        binDump(argv[2]);
    }
    else
        hexDump(argv[1]);
}

