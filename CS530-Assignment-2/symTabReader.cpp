/******************************************************************************
 * Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * Filename: symTabReader.cpp
 * Description: .cpp for symTabReader. Reads the .sym file and pulls out all
 *    symbols and literals from the symTab and litTab.
 ******************************************************************************/

#include "symTabReader.h"
//symbol vector nested class constructor
symTabReader::symbols::symbols(string n, int a, string f) {
    name = n;
    addr = a;
    flag = f;
}
//literal vector nested class constructor
symTabReader::literals::literals(string s, int l, int a) {
    lit = s;
    length = l;
    addr = a;
}


/**
* Function Name: symTabRead
* Function Prototype: void symTabReader::symTabRead()
* Description: Reads and stores the SYMTAB and LITTAB.
* Parameters: string of the .sym file name
* Return Values: None
*/
void symTabReader::symTabRead(string filename) {

    ifstream file(filename.c_str());

    //skips the table headers
    file.ignore(50,'\n');
    file.ignore(50,'\n');

    string a, b, c;
    int valLen, addr;
    int x = 0;

    if(file.is_open()) {
        //reading symTab
        while(file >> a >> b >> c) {
            //reading literal table
            if(a == "Name") {
                //skips the table headers
                file.ignore(50,'\n');
                file.ignore(50,'\n');
                while(file >> a >> b >> c) {
                    istringstream(b) >> std::hex >> valLen;
                    istringstream(c) >> std::hex >> addr;
                    l.push_back(literals(a,valLen,addr));
                }
            break;
            }

            istringstream(b) >> std::hex >> valLen;
            s.push_back(symbols(a,valLen,c));
        }
    }

    file.close();
}

/**
* Function Name: getSymbolVector
* Function Prototype: void symTabReader::getSymbolVector()
* Description: gets a symbol and its parameters
* Parameters: index of the symbol
* Return Values: symbol name, address, or flag
*/
vector<symTabReader::symbols> symTabReader::getSymbolVector()
{
    return s;
}

/**
* Function Name: getLiteralVector
* Function Prototype: void symTabReader::getLiteralVector()
* Description: gets a literal and its parameters
* Parameters: index of the literal
* Return Values: literal, length, or address
*/
vector<symTabReader::literals> symTabReader::getLiteralVector()
{
    return l;
}

