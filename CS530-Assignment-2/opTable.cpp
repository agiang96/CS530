/*****************************************************************************
 * Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * File Name: opTable.cpp 
 * Description: .cpp file the OpTable, utlized for making references
 *              to the opTable to process XE object code
******************************************************************************/

#include "opTable.h"
/**
* Function Name: opTabs
* Function Prototype: opTable::opTabs::opTabs(parameters)
* Description: Constructor for the opTabs nested class.
*     To create an object with an opCode,Name,and Format.
* Parameters: int newOp, std::string newOpN, int newForms
* Return Values: None
*/
opTable::opTabs::opTabs(int newOp, std::string newOpN, int newForms) {
    opCode = newOp;
    opName = newOpN;
    format = newForms;
     }

opTable::opTable() {
    opTableSize = 59; //sets opTableSize to 59, for all instructions
}
 /**
* Function Name: getOpCode
* Function Prototype: int opTable::getOpCode(int op)
* Description: A getter, takes in an opCode, bit masks it to 
*              receive an XE opCode.
* Parameters: An int of the opCode to be processed.
* Return Values: The XE opCode
*/
int opTable::getOpCode(int op) {
    int newOp = op&0xFC;
    int retOp = 0;
    for(int i=0; i< opTableSize; i++) {
      if(optab[i].opCode==newOp) {
         retOp = optab[i].opCode;
         break;
      }
    }
    return retOp;
}
 /**
* Function Name: getFormat
* Function Prototype: int opTable::getFormat(int op)
* Description: Returns the format of a mneumonic on the opTable.
* Parameters: int of the opCode
* Return Values: An int of the format for the specified opCode
*/
int opTable::getFormat(int op) {
    int retForm = 0;
    int newOp = op&0xFC;
    for(int i=0;i<opTableSize;i++) {
       if(optab[i].opCode==newOp) {
           retForm = optab[i].format;
           break;
       }
    }
    return retForm;
}
/**
* Function Name: getMneumonic
* Function Prototype: std::string opTable::getMneumonic(int op)
* Description: Returns the mneumonic of the opCode.
* Parameters: String of the specified mneumonic
* Return Values: A string of the mneumonic;
*/
std::string opTable::getMneumonic(int op) {
    std::string retMneu;
    int newOp = op&0xFC;
    for(int i=0;i<opTableSize;i++) {
       if(optab[i].opCode==newOp) {
           retMneu = optab[i].opName;
           break;
       }
    }
    return retMneu;
}

 

