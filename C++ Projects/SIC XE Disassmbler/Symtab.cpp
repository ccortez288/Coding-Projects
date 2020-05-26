/* Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: Symtab.cpp
*/

#include "Symtab.h"

//symbol vector nested class constructor
Symtab::symbols::symbols(string n, int a, string f) {
    name = n;
    addr = a;
    flag = f;
}
//literal vector nested class constructor
Symtab::literals::literals(string s, int l, int a) {
    lit = s;
    length = l;
    addr = a;
}


/**
*Reads and stores the SYMTAB and LITTAB.
*/
void Symtab::symTabRead(string filename) {

    ifstream file(filename.c_str());

    //skip headers
    file.ignore(50,'\n');
    file.ignore(50,'\n');

    string a, b, c;
    int valLen, addr;
    int x = 0;

    if(file.is_open()) {
        //reading symTab
        while(file >> a >> b >> c) {
            //reading literal table
            if(a == "Name") {
                file.ignore(50,'\n');
                file.ignore(50,'\n');
                while(file >> a >> b >> c) {
                    istringstream(b) >> std::hex >> valLen;
                    istringstream(c) >> std::hex >> addr;
                    l.push_back(literals(a,valLen,addr));
                }
            break;
            }

            istringstream(b) >> std::hex >> valLen;
            s.push_back(symbols(a,valLen,c));
        }
    }

    file.close();
}

/**
* Description: gets a symbol and its parameters
*/
vector<Symtab::symbols> Symtab::getSymbolVector()
{
    return s;
}

/**
* Description: gets a literal and its parameters
*/
vector<Symtab::literals> Symtab::getLiteralVector()
{
    return l;
}
