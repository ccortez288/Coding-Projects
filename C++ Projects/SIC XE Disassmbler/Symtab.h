/* Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: Symtab.h
*/

#ifndef SYMTAB_H
#define SYMTAB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "fileReader.h"

using namespace std;

class Symtab {
    public:
        //symbol vector class
        class symbols {
            public:
                string name;
                int addr;
                string flag;
                symbols(string n, int a, string f);
        };
        //literal vector class
        class literals {
            public:
                string lit;
                int length;
                int addr;
                literals(string li, int le, int a);
        };
    
    // used to store the contents of the SYMTAB
    vector<symbols> s;
    //used to store the contents of the LITTAB
    vector<literals> l;

    /**
     * Function Prototype: void SYMTAB::symTabRead()
     */
         
    void symTabRead(string filename);
    
    /**
     * Description: gets a symbol and its parameters
     */
    vector<symbols> getSymbolVector();
    
    /**
     * Description: gets a literal and its parameters
     */
    vector<literals> getLiteralVector();
};

#endif
