/* 
 * Members: Alexander Giang, Shawn Chua 
 * Class Users: cssc0885, cssc0894
 * Class Information: CS530, Spring 2017
 * Assignment #1, HexDump
 * Filename: hex.cpp
 */

#include <iostream>
#include <bitset>
#include <iomanip>
#include <fstream>
#include "xsd.h"

using namespace std;

void hexDump(char file[50]){
    int address = 0;
    string line_;
    unsigned char ch; //to get each line char by char

    ifstream file_(file);
    if(file_.is_open()){


        cout << hex << setfill('0');

	// until the end of file
        while(file_.good()){
            int j = 0;
	    int x = 0;

           //prints ASCII and address in hex
            for(j = 0; j < 16 && file_ >> noskipws >> ch ; j++ ){
                if (j == 0)
                    cout << setw(7) << address << ":";
                
                if(j % 2 == 0)
                   cout << " ";

                cout<< hex << setw(2) << int(ch);
                
                line_[j] = ch;
            }

            x = j; //won't print end NULL's

            //for output spacing organization
            while(j < 16){
                cout << "  ";
                if(j % 2 == 0)
                    cout << " ";
                
                j++;
            }
            
            //to print out the file text
            cout << "  ";
            for(int i = 0; i < x; i++){
                
		if(line_[i] < 32)
		    cout << ".";
		else
                    cout << line_[i];
                
            }
            for(int i = 0; i < 16; i++)
                line_[i] = NULL;

            cout << endl;
            
            address += 16;
        }
        
        file_.close();
    }
    else
        cout<<"file is not open"<<'\n';    
}
    
