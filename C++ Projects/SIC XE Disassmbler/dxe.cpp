/*Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: dxe.cpp
*/
#include "dxe.h"
using namespace std;

int main(int argc, char *argv[]) {
    if(argc !=  2) { //Incorrect number of arguments
      cout << "Incorrect number of arguments" << endl;
      return 0;
    }

    string filename(argv[1]);
    int position = filename.find_last_of(".");
    if(position == -1) { //First error check to determine if it's
                    //a .obj file.
      cout << "Not a .obj file" << endl;
      return 0;
    }
    
    string exts = filename.substr(position,filename.length()-position);
    //checks for correct extension
    if(exts.compare(".obj")!=0) {
      cout << "Wrong extension for filename" << endl;
      return 0;
    }

   string symtabFile = filename.substr(0,position);
   symtabFile.append(".sym");

   ifstream f;
   f.open(filename.c_str());
   if(!f.good()) {
      cout<< "ERROR:" << filename << " file does not exist."
               << endl;
      return 0;
   }
   f.close();
   
   f.open(symtabFile.c_str());
   if(!f.good()) {
      cout << "Error: " << symtabFile << " file does not exist."
                << endl;
      return 0;
   }
   f.close();


   fileReader r;
   r.getObj(argv[1]);
   string contents = r.getObjText(filename);
   //contents contains the object code for Processor

   Symtab symtabReader;
   symtabReader.symTabRead(symtabFile);
   vector<Symtab::symbols> symTable = symtabReader.getSymbolVector();
   vector<Symtab::literals> litTable = symtabReader.getLiteralVector();


   Processor processRec;
   processRec.readRecord(contents, symTable, litTable,
      filename.substr(0, position));

   return 1;
}
