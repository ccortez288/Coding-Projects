/*Christian Cortez cssc1965 
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: OpcodeTable.h
*/
#ifndef OPCODETABLE_H
#define OPCODETABLE_H

#include <string>
using namespace std;

class OpcodeTable {
  private:
    //Function to store opcode, format, and mneumonic into one //object file to turn into array for the OpcodeTable
    class opTabs {
      public:
        int opCode; 
        string opName; 
        int format; 
        opTabs(int newOp, string newOpN, int newForms);
    };

  public:
    OpcodeTable();
      //A getter that takes in opCode and bit masks it to  receive an XE opCode.
    int getOpCode(int op);
      //Returns format of mneumonic
    int getFormat(int op);
     //Returns the mneumonic of the opCode.
    string getMneumonic(int op);
    int OpcodeTableSize; 

    //Contents of the OpcodeTable
    opTabs optab[59] = { 
      opTabs(0x18,"ADD",3),opTabs(0x58,"ADDF",3),opTabs(0x90,"ADDR",2),
      opTabs(0x40,"AND",3),opTabs(0xB4,"CLEAR",2),opTabs(0x28,"COMP",3),
      opTabs(0x88,"COMPF",3),opTabs(0xA0,"COMPR",2),opTabs(0x24,"DIV",3),
      opTabs(0x64,"DIVF",3),opTabs(0x9C,"DIVR",2),opTabs(0xC4,"FIX",1),
      opTabs(0xC0,"FLOAT",1),opTabs(0xF4,"HIO",1),opTabs(0x3C,"J",3),
      opTabs(0x30,"JEQ",3),opTabs(0x34,"JGT",3),opTabs(0x38,"JLT",3),
      opTabs(0x48,"JSUB",3),opTabs(0x00,"LDA",3),opTabs(0x68,"LDB",3),
      opTabs(0x50,"LDCH",3),opTabs(0x70,"LDF",3),opTabs(0x08,"LDL",3),
      opTabs(0x6C,"LDS",3),opTabs(0x74,"LDT",3),opTabs(0x04,"LDX",3),
      opTabs(0xD0,"LPS",3),opTabs(0x20,"MUL",3),opTabs(0x60,"MULF",3),
      opTabs(0x98,"MULR",2),opTabs(0xC8,"NORM",1),opTabs(0x44,"OR",3),
      opTabs(0xD8,"RD",3),opTabs(0xAC,"RMO",2),opTabs(0x4C,"RSUB",3),
      opTabs(0xA4,"SHIFTL",2),opTabs(0xA8,"SHIFTR",2),opTabs(0xF0,"SIO",1),
      opTabs(0xEC,"SSK",3),opTabs(0x0C,"STA",3),opTabs(0x78,"STB",3),
      opTabs(0x54,"STCH",3),opTabs(0x80,"STF",3),opTabs(0xD4,"STI",3),
      opTabs(0x14,"STL",3),opTabs(0x7C,"STS",3),opTabs(0xE8,"STSW",3),
      opTabs(0x84,"STT",3),opTabs(0x10,"STX",3),opTabs(0x1C,"SUB",3),
      opTabs(0x5C,"SUBF",3),opTabs(0x94,"SUBR",2),opTabs(0xB0,"SVC",2),
      opTabs(0xE0,"TD",3),opTabs(0xF8,"TIO",1),opTabs(0x2C,"TIX",3),
      opTabs(0xB8,"TIXR",2),opTabs(0xDC,"WD",3)
      };
};

#endif
