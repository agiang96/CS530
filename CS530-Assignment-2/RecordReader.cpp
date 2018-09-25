/******************************************************************************
* File Name: RecordReader.cpp
* Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
* Class Users: cssc0885, cssc0894, cssc0880, cssc0857
* REDID: 818285579, 817662151, 819377332, 817862169
* Class Information: CS530, Spring 2017
* Assignment #2, XE Disassembler
* Description: RecordReader file that handles reading, processing, and
*     output of the Records in a .obj file.
******************************************************************************/

#include "RecordReader.h"

RecordReader::RecordReader()
{
    progName = "";
    startingAddress = -1;
    lengthOfProg = -1;
    textRecordStartingAddress = -1;
    lengthOfTextRecord = -1;
    objCode = "";
    addressOfFirstExecInstr = -1;
    addrDisp = -1;
    progCounter = 0;
    targetAddress = 0;
    baseCounter = 0;
    charsReading = 0;

    for(int i = 0; i < NUM_OF_FLAGS; i ++)
    {
        flags[i] = false;
    }

    indexCounter = 0;

    int resizeSize = 100;

    nFlagVect.resize(resizeSize);
    iFlagVect.resize(resizeSize);
    xFlagVect.resize(resizeSize);
    bFlagVect.resize(resizeSize);
    pFlagVect.resize(resizeSize);
    eFlagVect.resize(resizeSize);

    opCodeVect.resize(resizeSize);
    formatVect.resize(resizeSize);
    mneumonicVect.resize(resizeSize);

    symVect.resize(resizeSize);
    symDeclVect.resize(resizeSize);
    litVect.resize(resizeSize);
    operandVect.resize(resizeSize);
    modifVect.resize(resizeSize);
    progCounterVect.resize(resizeSize);
    operandVect.resize(resizeSize);
}

void RecordReader::readRecord(std::string record,
    std::vector<symTabReader::symbols> symbolVect,
    std::vector<symTabReader::literals> literalVect,
    std::string nameOfFile)
{
    std::string tmpRecord = record;
    symTabVect = symbolVect;
    litTabVect = literalVect;
    fileName = nameOfFile;

    while(true)
    {
        // placed before logic incase it is finished with reading the record
        if(tmpRecord.length() <= 0)
        {
            outputToSIC();
            return;
        }

        if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "H")
        {
  	        readHeaderRecord(tmpRecord);
	        tmpRecord = tmpRecord.substr(HEADER_REC_LEN);
        }
        else if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "T")
        {
  	        readTextRecord(tmpRecord);
            tmpRecord = tmpRecord.substr((lengthOfTextRecord * 2) +
                START_OF_TEXT_RECORD);
        }
        else if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "E")
        {
            readEndRecord(tmpRecord);
            tmpRecord = tmpRecord.substr(END_REC_LEN);
        }
        else if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "M")
        {
            readModifRecord(tmpRecord);
            tmpRecord = tmpRecord.substr(MODIF_REC_LEN);
        }
    }
}

void RecordReader::readHeaderRecord(std::string record)
{

    progName = record.substr(1,6);

    std::istringstream(record.substr(7, 6)) >> std::hex >> startingAddress;
    std::istringstream(record.substr(13, 6)) >> std::hex >> lengthOfProg;
}

void RecordReader::readTextRecord(std::string record)
{
    int halfBytesRead = 0; // increment everytime a halfbyte is read
                           // in the object code for the text record

    std::istringstream(record.substr(1, 6)) >>
	    std::hex >> textRecordStartingAddress;
    std::istringstream(record.substr(7, 2)) >> std::hex >> lengthOfTextRecord;
    std::istringstream(record.substr(9)) >> std::hex >> objCode;

    processObjCode(objCode);
}

void RecordReader::processObjCode(std::string objCode)
{
    std::string methodObjCode = objCode;

    while(methodObjCode.length() > 0)
    {
        if(methodObjCode.substr(0, 1) == "M" ||
            methodObjCode.substr(0, 1) == "E" ||
	     methodObjCode.substr(0, 1) == "T")
        {
            return; // return if end of Text Record
        }

        std::string lenSixObjCode = methodObjCode.substr(0, 6);

        opTable opTab;
        int addrDisp;
        int opCode = opTab.getOpCode(findObjOpCode(lenSixObjCode));
        int format = opTab.getFormat(opCode);
        std::string mneumonic = opTab.getMneumonic(opCode);

        if(format == 3 || format == 4)
        {
            setFlags(lenSixObjCode, opCode);
        }

        if(getFlags()[5] == false)
        {
            // e flag = 0
            addrDisp = getAddrDisp(format, lenSixObjCode.substr(3, 3));
        }
        else
        {
            // e flag = 1
            format = 4;
            lenSixObjCode = methodObjCode.substr(0, 8);
            addrDisp = getAddrDisp(format, lenSixObjCode.substr(3, 5));
        }

        charsReading = format * 2; // amount of chars in objcode being read
        targetAddress = getTargetAddress(format, addrDisp);

        if(mneumonic.compare("LDB") == 0)
        {
             baseCounter = targetAddress;
        }

        // O(1) Amortized Array Resizing
        if(indexCounter == nFlagVect.size() - 1)
        {
            // resize all vectors
            nFlagVect.resize(nFlagVect.size() * 2);
            iFlagVect.resize(iFlagVect.size() * 2);
            xFlagVect.resize(xFlagVect.size() * 2);
            bFlagVect.resize(bFlagVect.size() * 2);
            pFlagVect.resize(pFlagVect.size() * 2);
            eFlagVect.resize(eFlagVect.size() * 2);

            opCodeVect.resize(opCodeVect.size() * 2);
            formatVect.resize(formatVect.size() * 2);
            mneumonicVect.resize(mneumonicVect.size() * 2);
            operandVect.resize(operandVect.size() * 2);
            symVect.resize(symVect.size() * 2);
            symDeclVect.resize(symDeclVect.size() * 2);
            litVect.resize(litVect.size() * 2);
            operandVect.resize(operandVect.size() * 2);
            modifVect.resize(modifVect.size() * 2);
            progCounterVect.resize(progCounterVect.size() * 2);
        }

        nFlagVect[indexCounter] = getFlags()[0];
        iFlagVect[indexCounter] = getFlags()[1];
        xFlagVect[indexCounter] = getFlags()[2];
        bFlagVect[indexCounter] = getFlags()[3];
        pFlagVect[indexCounter] = getFlags()[4];
        eFlagVect[indexCounter] = getFlags()[5];

        opCodeVect[indexCounter] = opCode;
        formatVect[indexCounter] = format;
        mneumonicVect[indexCounter] = mneumonic;

        // Format 1, no other calculations,etc. necessary
        // All we need is the mneumonic.
        std::string registers;

        if(format == 1)
        {
            operandVect[indexCounter] = "";
        }
        else if(format == 2)
        {
            std::string reg1 = lenSixObjCode.substr(2,1);
            std::string reg2 = lenSixObjCode.substr(3,1);
            if(reg1.compare("0") == 0) {
               registers="A,";
            } else if(reg1.compare("1") == 0) {
               registers="X,";
            } else if(reg1.compare("2") == 0) {
               registers="L,";
            } else if(reg1.compare("3") == 0) {
               registers="B,";
            } else if(reg1.compare("4") == 0) {
               registers="S,";
            } else if(reg1.compare("5") == 0) {
               registers="T,";
            } else if(reg1.compare("6") == 0) {
               registers="F,";
            }

            //looking at second register
            if(reg2.compare("0") == 0) {
               registers.append("A");
            } else if(reg2.compare("1") == 0) {
               registers.append("X");
            } else if(reg2.compare("2") == 0) {
               registers.append("L");
            } else if(reg2.compare("3") == 0) {
               registers.append("B");
            } else if(reg2.compare("4") == 0) {
               registers.append("S");
            } else if(reg2.compare("5") == 0) {
               registers.append("T");
            } else if(reg2.compare("6") == 0) {
               registers.append("F");
            }
            operandVect[indexCounter] = registers;
        }

        else if(format == 3 || format == 4)
        {
            symFound = checkSymTab(targetAddress);
            litFound = checkLitTab(addrDisp);

            // symbol found or literal found?
            // if symbol, store name into symVect for .sic file
            // if literal, store name into litVect for .sic file
            // add to charsReading due to literal length in obj code

            //final flag check
            bool bpe = getFlags()[5] || getFlags()[4] || getFlags()[3];

            //accounts for simple addressing and indirect addressing
            bpe|=getFlags()[0];

            // one of the bpe bits have to be set to process label
            if(symFound && bpe)
            {
                std::string symbol = getSymbolName(targetAddress);
                symVect[indexCounter] = symbol;

                if(getFlags()[2]) // indexing
                {
                    symbol.append(",X");
                }
                if(getFlags()[0]&&!getFlags()[1]) // indirect
                {
                    symbol.insert(0, "@");
                }
                if(!getFlags()[0]&&getFlags()[1]) // immediate
                {
                    symbol.insert(0, "#");
                }
                operandVect[indexCounter] = symbol;
                symFound=false;
            }
            else
            {
                if(!getFlags()[0] && getFlags()[1]) // immediate
                {
                   std::stringstream ss;
                   ss << targetAddress;
                   std::string immediate;
                   ss >> immediate;
                   immediate.insert(0,"#");
                   operandVect[indexCounter] = immediate;
                }
            }

            if(litFound)
            {
                std::string litName = getLiteralName(addrDisp);
                litVect[indexCounter] = litName;
                int indexOfQuote = litVect[indexCounter].find("'");
                charsReading +=
                    litVect[indexCounter].substr(3, indexOfQuote).length();
                litFound = false;
                operandVect[indexCounter] = litName;
            }
        }

        //SPECIAL CASE FOR RSUB, DOES NOT TAKE ANY OPERANDS
        if(mneumonic.compare("RSUB") == 0)
        {
            operandVect[indexCounter] = "";
        }

        if(checkSymTab(progCounter))
        {
            for(int i = 0; i < symTabVect.size(); i ++)
            {
                symDeclVect[indexCounter] = getSymbolName(progCounter);
            }
        }

        progCounterVect[indexCounter] = progCounter;

        if(format == 1)
        {
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }
        else if(format == 2)
        {
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }
        else if(format == 3)
        {
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }
        else
        {
            // format == 4
            // e flag = 1, extended means two more halfbytes
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }

        indexCounter ++;
    }
}

void RecordReader::readModifRecord(std::string record)
{
    int modifAddress, modifLen, index;

    std::string strModifAddress = record.substr(1, 6);
    std::string strModifLen = record.substr(7, 2); // in half bytes

    std::istringstream(strModifAddress) >> std::hex >> modifAddress;
    std::istringstream(strModifLen) >> std::hex >> modifLen;

    for(int i = 0; i < indexCounter; i ++)
    {
        if(modifAddress == 5 && progCounterVect[i] == (modifAddress - 1))
        {
            modifVect[i] = modifLen;
        }
        else if(modifAddress == 6 && progCounterVect[i] == modifAddress)
        {
            modifVect[i] = modifLen;
        }
    }
}

void RecordReader::readEndRecord(std::string record)
{
    std::istringstream(record.substr(1,6)) >> addressOfFirstExecInstr;
}

int RecordReader::findObjOpCode(std::string lenSixObjCode)
{
    int ret;

    std::istringstream(lenSixObjCode.substr(0, 2)) >> std::hex >> ret;

    return ret;
}

void RecordReader::setFlags(std::string lenSixObjCode, int opCode)
{
    int niFlags, niFlagsVal;
    std::istringstream(lenSixObjCode.substr(0, 2)) >> std::hex >> niFlagsVal;
    niFlags = niFlagsVal - opCode;

    if (niFlags == 3)
    {
        flags[0] = true; // n flag
        flags[1] = true; // i flag
    }
    else if (niFlags == 2)
    {
        flags[0] = true; // n flag
        flags[1] = false; // i flag
    }
    else if (niFlags == 1)
    {
        flags[0] = false; // n flag
        flags[1] = true; // i flag
    }

    int xbpeFlags;
    std::istringstream(lenSixObjCode.substr(2, 1)) >> std::hex >> xbpeFlags;

    if (xbpeFlags / 8 == 1)
    {
        flags[2] = true; // x flag
        xbpeFlags %= 8;
    }
    else
    {
        flags[2] = false;
        // dont need to do xbpeFlags %= 8;
    }

    if (xbpeFlags / 4 == 1)
    {
        flags[3] = true; // b flag
        xbpeFlags %= 4;
    }
    else
    {
        flags[3] = false;
    }

    if (xbpeFlags / 2 == 1)
    {
        flags[4] = true; // p flag
        xbpeFlags %= 2;
    }
    else
    {
        flags[4] = false;
    }

    if (xbpeFlags / 1 == 1)
    {
        flags[5] = true; // e flag
        xbpeFlags %= 1;
    }
    else
    {
        flags[5] = false;
    }
}

int RecordReader::getAddrDisp(int format, std::string addrDispObjCode)
{
    unsigned int ret;

    if(addrDispObjCode.substr(0, 1) == "F")
    {
        for(int i = 0; addrDispObjCode.length() < 8; i ++)
        {
            addrDispObjCode = "F" + addrDispObjCode;
        }
    }

    std::stringstream strStream;
    strStream << std::hex << addrDispObjCode;
    strStream >> ret;
    ret = static_cast<int>(ret);

    return ret;
}

int RecordReader::getTargetAddress(int format, int addrDispCode)
{
    int addressDisp, ret;
    addressDisp = addrDispCode;

    if(format == 3)
    {
        // check if pc relative or base relative
        // calculate targetAddress based off this
        if(flags[4] == true)
        {
            ret = progCounter + 3 + addressDisp;
            // +3 = length of instr
        }
        else if(flags[3] == true)
        {
            ret = baseCounter + addressDisp;
        }
        else
        {
            ret = addressDisp;
        }
    }
    else if(format == 4)
    {
        ret = addressDisp;
    }
    return ret;
}

bool RecordReader::checkSymTab(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return true;
        }
    }
}

bool RecordReader::checkLitTab(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return true;
        }
    }
}

void RecordReader::outputToSIC()
{
    std::vector<string> outputVector;
    outputVector.resize(100); // default resize to 100

    ofstream outputStream;
    std::string sicFileName = fileName.append(".sic");
    outputStream.open(sicFileName.c_str());

    std::string lastUsedSymbolName = "";
    int lastUsedSymbolIndex = 0;

    outputStream << std::setw(SPACE_PER_SECTION) << left << progName;
    outputStream << std::setw(SPACE_PER_SECTION + 1) << " START";
    outputStream << std::setw(SPACE_PER_SECTION) << startingAddress
        << std::endl;;

    for(int i = 0; i < indexCounter; i ++)
    {
        // if last mneumonic was LDB, BASE
        if(i > 0 && mneumonicVect[i - 1] == "LDB")
        {
            std::string fullInstr = " " + symVect[i - 1];
            outputStream << std::setw(SPACE_PER_SECTION) << "";
            outputStream << std::setw(SPACE_PER_SECTION) << " BASE";
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
            outputStream << std::endl;
        }

        // if last instruction had a literal, LTORG
        if(i > 0 && litVect[i - 1] != "")
        {
            outputStream << std::setw(SPACE_PER_SECTION) << "";
            outputStream << std::setw(SPACE_PER_SECTION) << " LTORG";
            outputStream << std::endl;
        }

        outputStream << std::setw(SPACE_PER_SECTION) << symDeclVect[i];

        if(symDeclVect[i] != "")
        {
            lastUsedSymbolName = symDeclVect[i];
        }

        if(eFlagVect[i] == true)
        {
            std::string fullInstr = "+" + mneumonicVect[i];
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
        }
        else
        {
            std::string fullInstr = " " + mneumonicVect[i];
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
        }

        if(operandVect[i].substr(0, 1) == "#" ||
            operandVect[i].substr(0, 1) == "@" ||
            operandVect[i].substr(0, 1) == "=" ||
            operandVect[i].substr(0, 1) == "+")
        {
            outputStream << std::setw(SPACE_PER_SECTION) << operandVect[i];
        }
        else
        {
            std::string fullInstr = " " + operandVect[i];
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
        }

        outputStream << std::endl;
    }

    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].name == lastUsedSymbolName)
        {
            lastUsedSymbolIndex = i;
        }
    }

    bool firstRun = true;
    int addr, diff;
    while(lastUsedSymbolIndex < symTabVect.size() - 1)
    {
        if(indexCounter == progCounterVect.size() - 1)
        {
            progCounterVect.resize(progCounterVect.size() * 2);
        }

        if(firstRun)
        {
            addr = symTabVect[lastUsedSymbolIndex + 1].addr;
            diff = addr - progCounterVect[indexCounter - 1];
            progCounterVect[indexCounter] = addr + diff;
            firstRun = false;
        }
        else
        {
            if(lastUsedSymbolIndex < symTabVect.size() - 2)
            {
                addr = symTabVect[lastUsedSymbolIndex + 2].addr;
                diff = addr - symTabVect[lastUsedSymbolIndex + 1].addr;
                progCounterVect[indexCounter] =
                    symTabVect[lastUsedSymbolIndex + 1].addr;
            }
            else // last symbol
            {
                addr = lengthOfProg; // last symbol, use length of prog
                diff = addr - symTabVect[lastUsedSymbolIndex + 1].addr;
                progCounterVect[indexCounter] =
                    symTabVect[lastUsedSymbolIndex + 1].addr;
            }
        }

        if(indexCounter == symDeclVect.size() - 1)
        {
            symDeclVect.resize(symDeclVect.size() * 2);
        }

        symDeclVect[indexCounter] = symTabVect[lastUsedSymbolIndex + 1].name;
        std::string symNameOutput = symTabVect[lastUsedSymbolIndex + 1].name;


        outputStream << std::setw(SPACE_PER_SECTION) << symNameOutput;

        int numOfWords = 0;

        if(diff % 3 == 0)
        {
            numOfWords = diff / 3;
            outputStream << std::setw(SPACE_PER_SECTION + 1) << " RESW";
        }
        else
        {
            outputStream << std::setw(SPACE_PER_SECTION + 1) << " RESB";
        }

        outputStream << std::setw(SPACE_PER_SECTION) <<  numOfWords;

        outputStream << std::endl;

        lastUsedSymbolIndex ++;
        indexCounter ++;
    }

    outputStream << std::setw(SPACE_PER_SECTION) << "";
    outputStream << std::setw(SPACE_PER_SECTION) << " END";
    outputStream << " "<<std::setw(SPACE_PER_SECTION) << symTabVect[0].name
        << std::endl;

}

std::string RecordReader::getProgName()
{
    return progName;
}

int RecordReader::getStartingAddr()
{
    return startingAddress;
}

int RecordReader::getLengthOfProg()
{
    return lengthOfProg;
}

int RecordReader::getLengthOfTextRecord()
{
    return lengthOfTextRecord;
}

int RecordReader::getAddressOfFirstExecInstr()
{
    return addressOfFirstExecInstr;
}

bool* RecordReader::getFlags()
{
    return flags;
}

int RecordReader::getIndexCounter()
{
    return indexCounter;
}

int RecordReader::getProgCounter()
{
    return progCounter;
}

std::string RecordReader::getSymbolName(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return symTabVect[i].name;
        }
    }
}

int RecordReader::getSymbolAddress(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return symTabVect[i].addr;
        }
    }
}

std::string RecordReader::getSymbolFlag(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return symTabVect[i].flag;
        }
    }
}

std::string RecordReader::getLiteralName(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return litTabVect[i].lit;
        }
    }
}

int RecordReader::getLiteralLength(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return litTabVect[i].length;
        }
    }
}

int RecordReader::getLiteralAddress(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return litTabVect[i].addr;
        }
    }
}
