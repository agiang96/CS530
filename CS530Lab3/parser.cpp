/* Members: Alexander Giang, Shawn Chua
 * Class Users: cssc0885, cssc0894
 * REDID: 818285579, 817662151
 * Class Information: CS530, Spring 2017
 * Assignment #3, Assignment/Expression Parser
 * Filename: parser.cpp
 */
#include "parser.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <exception>
#include <valarray>
using namespace std;

/*Sets the line to the string*/
void parser::setLine(std::string temp){
    line.clear();
    line.append(temp);
    index = 0;
}
/*Returns the string from the string variable line*/
string parser::getLine(){
    return line;
}
/*Initialize the index variable to zero*/
void parser::initIndex(){
    index = 0;
}

/*Indicates if the assign line is valid*/
bool parser::assign(){
    initEq();
    if(id()){
        if(line[index] == ' '){
            index++;
            if(line[index] == '='){
                eqCount++;
                index++;
                if(line[index] == ' '){
                    index++;
                    if(exp()){
                        if(line[index] == ';'){
                            index++;
                            if(line[index] == ' '){
                                return true;
                            }
                            
                        }
                        
                     
                    }
                }
            }
        }       
    }
    return false;
}


int parser::getIndex(){
   return index;
}


/*checks if expression is valid*/
bool parser::exp(){
    if(line[index] == '('){
        index++;
        if(line[index] == ' '){
            index++;
        }
        if(exp()){
            if(line[index] == ')'){
                if(line[++index] == ' '){
                    index++;
                    
                    if(index <= line.size() -1 && line[index] != ')'){
                        if(exp2()){
                            return true;
                        }
                        return false;  
                    }
                    return true;
                }
            }
        }
    }
    else if(id()){
        if(line[index] == ' '){
            index++;
            if(exp2()){
                return true;
            }
        }  
    }
    return false;
    
    
}

bool parser::exp2(){
    if(line[index] == ';' && eqCount > 0){
        return true;
    }
    if(op()){
        if(line[index] == '('){
            index++;
            if(line[index] == ' '){
                index++;
                
            }
            if(exp()){
                if(line[index] == ')'){
                    if(line[++index] == ' '){
                        index++;
                        if(index <= line.size() -1 && line[index] != ')'){
                            if(exp2()){
                                return true;
                            }
                            return false;
                        }
                        return true;
                    }
                }                
            }
            
        }
        else if(id()){
            if(line[index] == ' '){
                index++;  
                if(index <= line.size()-1 && line[index] != ')'){                   
                   if(exp2()){
                       return true;
                   }
                   return false;
                }
                return true;
            }
            else if(line[index] == ')'){
                if(index <= line.size()-1 && line[index] != ')'){  
                   if(exp2()){
                       return true;
                   }
                   return false;
                }
                return true;
                
            }
        }
    }
    return false;
    
}

/*Checks if the given operation is valid*/
bool parser::op(){
    if(line[index] == '/'||line[index] == '*'||line[index] == '-'||line[index] == '+'||line[index] == '%'){
        index++;
        //return true;
        if(index <= line.size()-1){
            if(line[index] == ' '){
                index++;
                return true;
            }
        }
        else return false;
    }    
    else return false;
    /*TODO: error explain
     */
    
    
}
/*checks if the given id is valid*/
bool parser::id(){
    bool isValid = false;
    if(line[index] == ' '){
            index++;
    }
    if(line[index] == 'a'||line[index] == 'b'||line[index] == 'c'||line[index] == 'd'||line[index] == 'e'|
            line[index] == 'f'||line[index] == 'g'||line[index] == 'h'||line[index] == 'i'||line[index] == 'j'|
            line[index] == 'k'||line[index] == 'l'||line[index] == 'm'||line[index] == 'n'||line[index] == 'o'|
            line[index] == 'p'||line[index] == 'q'||line[index] == 'r'||line[index] == 's'||line[index] == 't'|
            line[index] == 'u'||line[index] == 'v'||line[index] == 'w'||line[index] == 'x'||line[index] == 'y'|
            line[index] == 'z'|
            line[index] == 'A'||line[index] == 'B'||line[index] == 'C'||line[index] == 'D'||line[index] == 'E'|
            line[index] == 'F'||line[index] == 'G'||line[index] == 'H'||line[index] == 'I'||line[index] == 'J'|
            line[index] == 'K'||line[index] == 'L'||line[index] == 'M'||line[index] == 'N'||line[index] == 'O'|
            line[index] == 'P'||line[index] == 'Q'||line[index] == 'R'||line[index] == 'S'||line[index] == 'T'|
            line[index] == 'U'||line[index] == 'V'||line[index] == 'W'||line[index] == 'X'||line[index] == 'Y'|
            line[index] == 'Z'||
            line[index] == '_'){
        index++;
        isValid = true;
    }
    else return false;
    /*TODO: explain error*/
    if(isValid && index <= line.size()-1){//if it is an id and there is more to check go to id2()
            //id2();
            if(id2()) return true;
            else return false;
            /*TODO
             */
    }
    if(isValid) return true;
}
/*A continuation for checking id*/
bool parser::id2(){
    bool isValid = false;
    if(line[index] == ' '||line[index] == '='||line[index] == '/'||line[index] == '*'||line[index] == '-'|
            line[index] == '+'||line[index] == '%'||line[index] == ')'||line[index] == '('){
        return true; //shows that this is not an id, done checking id, 
                     //and should go check for another function
    } 
    else if(line[index] == 'a'||line[index] == 'b'||line[index] == 'c'||line[index] == 'd'||line[index] == 'e'||
            line[index] == 'f'||line[index] == 'g'||line[index] == 'h'||line[index] == 'i'||line[index] == 'j'|
            line[index] == 'k'||line[index] == 'l'||line[index] == 'm'||line[index] == 'n'||line[index] == 'o'|
            line[index] == 'p'||line[index] == 'q'||line[index] == 'r'||line[index] == 's'||line[index] == 't'|
            line[index] == 'u'||line[index] == 'v'||line[index] == 'w'||line[index] == 'x'||line[index] == 'y'|
            line[index] == 'z'|
            line[index] == 'A'||line[index] == 'B'||line[index] == 'C'||line[index] == 'D'||line[index] == 'E'|
            line[index] == 'F'||line[index] == 'G'||line[index] == 'H'||line[index] == 'I'||line[index] == 'J'|
            line[index] == 'K'||line[index] == 'L'||line[index] == 'M'||line[index] == 'N'||line[index] == 'O'|
            line[index] == 'P'||line[index] == 'Q'||line[index] == 'R'||line[index] == 'S'||line[index] == 'T'|
            line[index] == 'U'||line[index] == 'V'||line[index] == 'W'||line[index] == 'X'||line[index] == 'Y'|
            line[index] == 'Z'|
            line[index] == '_'|
            line[index] == '0'||line[index] == '1'||line[index] == '2'||line[index] == '3'||line[index] == '4'|
            line[index] == '5'||line[index] == '6'||line[index] == '7'||line[index] == '8'||line[index] == '9'){
        index++;
        isValid = true;     
    }
    else return false;
    /**TODO: error explain*/
    if(isValid && index <= line.size()-1){
            //id2();
            if(id2()) return true;
            else return false;
            /*TODO
             */
    } 
    if(isValid) return true;
}

int parser::getEq(){
    return eqCount;
}


string parser::error(string err) {
    if(err == "assign")
        return "Invalid Assignment";
    if(err == "exp")
        return "Invalid Expression";
    if(err == "op")
        return "Invalid Op";
    if(err == "id")
        return "Invalid ID";
    if(err == "eq")
        return "Too many equal signs";
    if(err == "space")
        return "Invalid spacing";
}


bool parser::isExp(string in){
    string line = in;
    for(int i = 0; i < line.size(); i++) 
        if(line[i] == '=') 
            return false;
    return true;
}


void parser::initEq(){
    eqCount == 0;
}


int main(int argc, char *argv[]) {

    if(argc !=  2) { //Incorrect number of arguments
        std::cout << "Usage: parse <filename>.txt" << std::endl;
        return 0;
    }

    std::string filename(argv[1]);
    int pos = filename.find_last_of(".");

    if(pos == -1) { //First error check to determine if it's
                    //a .obj file.
        std::cout << "Usage: parse <filename>.txt" << std::endl;
        return 0;
    }
    std::string extension = filename.substr(pos,filename.length()-pos);
    //checks for correct extension
    if(extension.compare(".txt")!=0) {
        std::cout << "Usage: parse <filename>.txt" << std::endl;
        return 0;
    }

    //input file
    std::ifstream file;
    file.open(filename.c_str());

    //output file
    std::ofstream out("out.txt");

    parser p;
    std::string line;

    //walkthrough the file
    if(file) {
        while(getline(file, line)) {

            //output the line
            p.setLine(line); 
            out << p.getLine() << " ";

            // error managing
            if(p.isExp(line)){
                p.initIndex();
                if(!p.exp())
                    out << "FAIL: " << p.error("exp");
                else
                    out << "PASS";
                out << endl;
            }
            else {
                p.initIndex();
                if(!p.assign())
                    out << "FAIL: " << p.error("assign");
                else
                    out << "PASS";
                out << endl;
            }

        }//while(getline())

    }//if(file)

    file.close();
    out.close();
    return 0;
}


