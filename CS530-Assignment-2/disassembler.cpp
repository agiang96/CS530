/******************************************************************************
 * Members: Alexander Giang, Shawn Chua, Michael Yee, Tony La
 * Class Users: cssc0885, cssc0894, cssc0880, cssc0857
 * REDID: 818285579, 817662151, 819377332, 817862169
 * Class Information: CS530, Spring 2017
 * Assignment #2, XE Disassembler
 * Filename: disassembler.cpp
 * Description: .cpp for disassembler. Prepares everything for disassembly
 *    in the recordReader.
 ******************************************************************************/

#include "disassembler.h"
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
int main(int argc, char *argv[]) {
    if(argc !=  2) { //Incorrect number of arguments
      std::cout << "Usage: dasm <filename>.obj" << std::endl;
      return 0;
    }

    std::string filename(argv[1]);
    int pos = filename.find_last_of(".");
    if(pos == -1) { //First error check to determine if it's
                    //a .obj file.
      std::cout << "Usage: dasm <filename>.obj" << std::endl;
      return 0;
    }
    std::string extension = filename.substr(pos,filename.length()-pos);
    //checks for correct extension
    if(extension.compare(".obj")!=0) {
      std::cout << "Usage: dasm <filename>.obj" << std::endl;
      return 0;
    }

   //Generating the respective .sym file to open
   //in the symTabReader
   std::string symFile = filename.substr(0,pos);
   symFile.append(".sym");

   std::ifstream file;
   file.open(filename.c_str());
   if(!file.good()) {
      std::cout<< "ERROR! " << filename << " does not exist! EXITING!"
               << std::endl;
      return 0;
   }
   file.close();
   file.open(symFile.c_str());
   if(!file.good()) {
      std::cout << "ERROR! " << symFile << " does not exist! EXITING!"
                << std::endl;
      return 0;
   }
   file.close();


   readFile reader;
   reader.getObj(argv[1]);
   std::string fileContents = reader.getObjText(filename);
   //fileContents contains the object code for recordReader

   symTabReader symTR;
   symTR.symTabRead(symFile);
   vector<symTabReader::symbols> symTab = symTR.getSymbolVector();
   vector<symTabReader::literals> litTab = symTR.getLiteralVector();

   //call symTab[index].name/addr/flag for symbols
   //call litTab[index].lit/length/addr for literals

   RecordReader recReader;
   recReader.readRecord(fileContents, symTab, litTab,
      filename.substr(0, pos));

   return 1;
}
