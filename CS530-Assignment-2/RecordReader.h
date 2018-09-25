/******************************************************************************
 * Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * File Name: RecordReader.h
 * Description: Header file for RecordReader.
******************************************************************************/

#ifndef RECORDREADER_H
#define RECORDREADER_H

class opTable;

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "opTable.h"
#include "symTabReader.h"


const int START_OF_TEXT_RECORD = 9; // the first 9 half bytes read
const int NUM_OF_FLAGS = 6; // number of flags, n, i, x, b, p, e = 6
const int FIRST_LETR_IN_REC = 0; // index for first letter in record
const int FIRST_LETR_LEN = 1; // length of one letter
const int HEADER_REC_LEN = 19; // length of header record (in chars)
const int MODIF_REC_LEN = 9; // length of modification record (in chars)
const int END_REC_LEN = 7; // length of end record (in chars)
const int SPACE_PER_SECTION = 8; // space between sections in .sic file

/**
 * Class Name: Record Reader
 * Description: A class that handles the reading, processing, and
 *     output for records.
 */
class RecordReader : public opTable
{
private:
    std::string progName; // program name
    int startingAddress, lengthOfProg; // starting address and length
    int textRecordStartingAddress; // text record starting address
    int  lengthOfTextRecord; // length of text record (in bytes)
    std::string objCode; // string of obj code
    int addressOfFirstExecInstr; // addr of first executable instruction
    bool flags[6]; // flags n, i, x, b, p, e
    int indexCounter; // line counter for printing .sic file
    int addrDisp; // address of displacement for format 3/4
    int progCounter; // program counter
    int targetAddress; // target address
    int baseCounter; // base counter
    int charsReading; // chars reading in one segment of object code
    std::string symbolName, symbolFlag; // symbol name/flag
    int symbolAddress; // symbol address
    std::string literalName; // literal name
    int litLength, litAddress; // literal length and address
    bool symFound, litFound; // bool for if symbol/literal is found
    std::string fileName; // the file name

    /**
     * Function Name: readHeaderRecord
     * Function Prototype: RecordReader::readHeaderRecord(std::string record)
     * Description: Reads and processes the Header Record.
     * Parameters: record - the string that holds all the records
     * Return Values: None
     */
    void readHeaderRecord(std::string record);

    /**
     * Function Name: readTextRecord
     * Function Prototype: void RecordReader::readTextRecord(
     *     std::string record)
     * Description: Reads and processes the Text Record.
     * Parameters: record - the string that holds all the records
     * Return Values: None
     */
    void readTextRecord(std::string record);

    /**
     * Function Name: processObjCode
     * Function Prototype: void RecordReader::processObjCode(
     *     std::string objCode)
     * Description: Reads and processes the object code given.
     *     Reads and processes Text Record until the end of the Record.
     * Parameters: objCode - contains the contents of the Record and the
     * remaining object code in the .obj file
     * Return Values: None
     */
    void processObjCode(std::string objCode);

    /**
     * Function Name: readModifRecord
     * Function Prototype: void RecordReader::readModifRecord(
     *     std::string record)
     * Description: Reads and processes Modification Records.
     * Parameters: record - contains the contents of the Modification
     * Record and the remaining object code in the .obj file
     * Return Values: None
     */
    void readModifRecord(std::string record);

    /**
     * Function Name: readEndRecord
     * Function Prototype: void RecordReader::readEndRecord(
     *     std::string record)
     * Description: Reads and processes the End Record.
     * Parameters: record - contains the contents of the Record.
     * Return Values: None
     */
    void readEndRecord(std::string record);

    /**
     * Function Name: findObjOpCode
     * Function Prototype: int RecordReader::findObjOpCode(
     *     std::string lenSixObjCode)
     * Description: Finds and returns the OpCode from a segment
     *     of object code.
     * Parameters: lenSixObjCode - six char long object code
     * Return Values: int of the OpCode
     */
    int findObjOpCode(std::string lenSixObjCode);

    /**
     * Function Name: setFlags
     * Function Prototype: void RecordReader::setFlags(
     *     std::string lenSixObjCode, int opCode)
     * Description: Sets the nixbpe flags in the bool flags[] array.
     * Parameters: lenSixObjCode - six char long object code
     *      opCode - the OpCode for the six char long object code
     * Return Values: None
     */
    void setFlags(std::string lenSixObjCode, int opCode);

    /**
     * Function Name: getAddrDisp
     * Function Prototype: int RecordReader::getAddrDisp(int format,
     *     std::string addrDispObjCode)
     * Description: Gets and returns the address/displacement from
     *     the address/displacement string. Checks if the
     *     address/displacement is negative and converts it if so.
     * Parameters: format - format the instruction is in
     *     addrDispObjCode - address/displacement of object code
     * Return Values: int of the address/displacement
     */
    int getAddrDisp(int format, std::string addrDispObjCode);

    /**
     * Function Name: getTargetAddress
     * Function Prototype: int RecordReader::getTargetAddress(int format,
     *     int addrDispCode)
     * Description: Calculates and returns the Target Address.
     * Parameters: format - format the instruction is in
     *     addrDispCode - address/displacement of object code
     * Return Values: int of the target address
     */
    int getTargetAddress(int format, int addrDispCode);

    /**
     * Function Name: checkSymTab
     * Function Prototype: bool RecordReader::checkSymTab(int addrDisp)
     * Description: Checks if the address/displacement is a symbol address.
     * Parameters: addrDisp - the address/displacement to check
     * Return Values: bool if address/displacement matches a symbol address
     */
    bool checkSymTab(int addrDisp);

    /**
     * Function Name: checkLitTab
     * Function Prototype: bool RecordReader::checkLitTab(int addrDisp)
     * Description: Checks if the address/displacement is a literal address.
     * Parameters: addrDisp - the address/displacement to check
     * Return Values: bool if address/displacement matches a literal address
     */
    bool checkLitTab(int addrDisp);

    /**
     * Function Name: outputToSIC
     * Function Prototype: void RecordReader::outputToSIC()
     * Description: Handles and outputs processed object code to .sic file.
     * Parameters: None
     * Return Values: None
     */
    void outputToSIC();

public:
    RecordReader(); // initializer method

    std::vector<bool> nFlagVect;
    std::vector<bool> iFlagVect;
    std::vector<bool> xFlagVect;
    std::vector<bool> bFlagVect;
    std::vector<bool> pFlagVect;
    std::vector<bool> eFlagVect;

    std::vector<int> opCodeVect;
    std::vector<int> formatVect;
    std::vector<std::string> mneumonicVect;

    // stores symbols for the operands (right side of .sic)
    std::vector<std::string> symVect;

    // stores symbols for the declaration (left side of .sic)
    std::vector<std::string> symDeclVect;

    std::vector<std::string> litVect;

    // stores operands (right side of .sic)
    std::vector<std::string> operandVect;

    std::vector<symTabReader::symbols> symTabVect;
    std::vector<symTabReader::literals> litTabVect;

    // stores modification record information
    std::vector<int> modifVect;

    // stores program counter for each line in .sic
    std::vector<int> progCounterVect;

    /**
     * Function Name: readRecord
     * Function Prototype: void RecordReader::readRecord()
     * Description: Reads the object code.
     * Parameters: string of the object code, symbol and literal vector
     * Return Values: None
     */
    void readRecord(std::string record,
        std::vector<symTabReader::symbols> symbolVect,
        std::vector<symTabReader::literals> literalVect,
        std::string nameOfFile);

    /**
     * Function Name: getProgName
     * Function Prototype: std::string RecordReader::getProgName()
     * Description: Acquires the program name located in the Header Record.
     * Parameters: None
     * Return Values: string of the program name
     */
    std::string getProgName();

    /**
     * Function Name: getStartingAddr
     * Function Prototype: int RecordReader::getStartingAddr()
     * Description: Acquires the starting address of the program in
     *              the Header Record.
     * Parameters: None
     * Return Values: int of the starting address of the program (in bytes)
     */
    int getStartingAddr();

    /**
     * Function Name: getLengthOfProg
     * Function Prototype: int RecordReader::getLengthOfProg()
     * Description: Acquires the length of the program in the Header Record.
     * Parameters: None
     * Return Values: int of the length of the program (in bytes)
     */
    int getLengthOfProg();

    /**
     * Function Name: getLengthOfTextRecord
     * Function Prototype: int RecordReader::getLengthOfTextRecord()
     * Description: Acquires the length of the Text Record.
     * Parameters: None
     * Return Values: int of the length of the text record (in bytes)
     */
    int getLengthOfTextRecord();

    /**
     * Function Name: getAddressOfFirstExecInstr
     * Function Prototype: int RecordReader::getAddressOfFirstExceInstr()
     * Description: Acquires the address of the first executable instruction.
     * Parameters: None
     * Return Values: int of the address of the first executable instructions
     *                (in bytes)
     */
    int getAddressOfFirstExecInstr();

    /**
     * Function Name: getFlags
     * Function Prototype: bool* RecordReader::getFlags()
     * Description: Acquires the flags boolean array (nixbpe flags).
     * Parameters: None
     * Return Values: bool array of the 'nixbpe' flags
     */
    bool* getFlags();


    /**
     * Function Name: getIndexCounter
     * Function Prototype: int RecordReader::getIndexCounter()
     * Description: Acquires the index counter.
     * Parameters: None
     * Return Values: int of index counter
     */
    int getIndexCounter();

    /**
     * Function Name: getProgCounter
     * Function Prototype: int RecordReader::getProgCounter()
     * Description: Acquires the program counter.
     * Parameters: None
     * Return Values: int of program counter
     */
    int getProgCounter();

    /**
     * Function Name: getSymbolName
     * Function Prototype: std::string RecordReader::getSymbolName(
     *     int addrDisp)
     * Description: Acquires the symbol name at an address/displacement.
     * Parameters: addrDisp - address/displacement to get symbol name from.
     * Return Values: string of the symbol name
     */
    std::string getSymbolName(int addrDisp);

    /**
     * Function Name: getSymbolAddress
     * Function Prototype: int RecordReader::getSymbolAddress(int addrDisp)
     * Description: Acquires the symbol address at an address/displacement.
     * Parameters: addrDisp - address/displacement to get symbol address from.
     * Return Values: int of the symbol address
     */
    int getSymbolAddress(int addrDisp);

    /**
     * Function Name: getSymbolFlag
     * Function Prototype: std::string RecordReader::getSymbolFlag(
     *     int addrDisp)
     * Description: Acquires the symbol flag at an address/displacement.
     * Parameters: addrdisp - address/displacement to get symbol flag from.
     * Return Values: string of the symbol flag
     */
    std::string getSymbolFlag(int addrDisp);

    /**
     * Function Name: getLiteralName
     * Function Prototype: std::string RecordReader::getLiteralName(
     *     int addrDisp)
     * Description: Acquires the literal name at an address/displacement.
     * Parameters: addrDisp - address/displacement to get literal name from
     * Return Values: string of the literal name
     */
    std::string getLiteralName(int addrDisp);

    /**
     * Function Name: getLiteralLength
     * Function Prototype: int RecordReader::getLiteralLength(int addrDisp)
     * Description: Acquires the literal length at an address/displacement.
     * Parameters: addrDisp - address/displacement to get literal length from
     * Return Values: int of the literal length
     */
    int getLiteralLength(int addrDisp);

    /**
     * Function Name: getLiteralAddress
     * Function Prototype: int RecordReader::getLiteralAddress(int addrDisp)
     * Description: Acquires the literal address at an address/displacement.
     * Parameters: addrDisp - address/displacement to get literal address from
     * Return Values: int of the literal address
     */
    int getLiteralAddress(int addrDisp);
};
#endif
