/* Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: OpcodeTable.cpp
*/
#include "OpcodeTable.h"

OpcodeTable::opTabs::opTabs(int newOp, string newOpN, int newForms) {
    opCode = newOp;
    opName = newOpN;
    format = newForms;
     }

OpcodeTable::OpcodeTable() {
    OpcodeTableSize = 59; //sets OpcodeTableSize to 59, for all instructions
}
 
int OpcodeTable::getOpCode(int op) {
    int newOp = op&0xFC;
    int retOp = 0;
    for(int i=0; i< OpcodeTableSize; i++) {
      if(optab[i].opCode==newOp) {
         retOp = optab[i].opCode;
         break;
      }
    }
    return retOp;
}
 
int OpcodeTable::getFormat(int op) {
    int retForm = 0;
    int newOp = op&0xFC;
    for(int i=0;i<OpcodeTableSize;i++) {
       if(optab[i].opCode==newOp) {
           retForm = optab[i].format;
           break;
       }
    }
    return retForm;
}

string OpcodeTable::getMneumonic(int op) {
    string retMneu;
    int newOp = op&0xFC;
    for(int i=0;i<OpcodeTableSize;i++) {
       if(optab[i].opCode==newOp) {
           retMneu = optab[i].opName;
           break;
       }
    }
    return retMneu;
}
