/******************************************************************************
 * Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * Filename: disassembler.cpp
 * Description: .cpp file for readFile. Reads the .obj file and pulls out
 *    contents of it into a string.
 ******************************************************************************/

#include "readFile.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <exception>
using namespace std;

/**
* Function Name: getObj
* Function Prototype: string getObj()
* Description: returns the object file
* Parameters: the file in a char array
* Return Values: string of the file name 
*/
string readFile::getObj(char file[]){
    std:string fileName;
    ifstream objFile(file);
    if(objFile){
        fileName.append(file);
        return fileName;
    }
}

/**
* Function Name: getObjText
* Function Prototype: string getObjText()
* Description: get the contents on the object file
* Parameters: the object file name in string 
* Return Values: contents of the object file in string
*/
string readFile::getObjText(std::string filename){
    string temp;
    string text;
    char *x;
    ifstream objFile(filename.c_str());
    while(objFile.good()){
        getline(objFile, temp);
        text.append(temp);  
    }
    
    return text;
}


