/* Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * Filename: readFile.h
 */

#ifndef READFILE_H
#define READFILE_H
#include <string>
#include <string.h>
using namespace std;

class readFile{
    public:
        /**
         * Function Name: getObj
         * Function Prototype: string getObj()
         * Description: returns the object file
         * Parameters: the file in a char array
         * Return Values: string of the file name 
         */
        string getObj(char []); 
        
        /**
         * Function Name: getObjText
         * Function Prototype: string getObjText()
         * Description: get the contents on the object file
         * Parameters: the object file name in string 
         * Return Values: contents of the object file in string
         */
        string getObjText(std::string);
};

#endif /* READFILE_H */
