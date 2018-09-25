/* 
 * Members: Alexander Giang, Shawn Chua 
 * Class Users: cssc0885, cssc0894
 * Class Information: CS530, Spring 2017
 * Assignment #1, HexDump
 * Filename: bin.cpp
 */

#include <iostream>
#include <bitset>
#include <iomanip>
#include <fstream>
#include "xsd.h"

using namespace std;

void binDump(char file[50]){
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
            
            //prints out binary & address
            for(j = 0; j < 6 && file_ >> noskipws >> ch ; j++ ){
                if (j == 0)
                    cout << setw(7) << address << ": ";
                cout<< bitset<8>(ch) <<" ";
                line_[j] = ch;
            }
            
            x = j; //won't print end NULL's

            //for output spacing organization
            while(j < 6){
                cout << "         ";
                j++;
            }
            
            //to print out the file text
            cout << " ";
            for(int i = 0; i < x; i++){
		if(line_[i] < 32)
		    cout << ".";
		else
                    cout << line_[i];
            }

            for(int i = 0; i < 6; i++)
                line_[i] = NULL;
            
            cout << endl;
            
            address += 6;
        }
        
        file_.close();
    }
    else
        cout<<"file is not open"<<'\n';    
}
