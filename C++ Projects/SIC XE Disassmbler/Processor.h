/* Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: Processor.h
*/
#ifndef PROCESSOR_H
#define PROCESSOR_H

class OpcodeTable;

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "OpcodeTable.h"
#include "Symtab.h"

using namespace std;

const int START_OF_TEXT_RECORD = 9; // the first 9 half bytes read
const int NUM_OF_FLAGS = 6; // number of flags, n, i, x, b, p, e = 6
const int FIRST_LETR_IN_REC = 0; // index for first letter in record
const int FIRST_LETR_LEN = 1; // length of one letter
const int HEADER_REC_LEN = 19; // length of header record (in chars)
const int MODIF_REC_LEN = 9; // length of modification record (in chars)
const int END_REC_LEN = 7; // length of end record (in chars)
const int SPACE_PER_SECTION = 8; // space between sections in .sic file

/**
 * A class that handles the reading, processing, and
 *     output for records.
 */
class Processor : public OpcodeTable
{
private:
    string progName; // program name
    int startingAddress, lengthOfProg; // starting address and length
    int textRecordStartingAddress; // text record starting address
    int  lengthOfTextRecord; // length of text record (in bytes)
    string objCode; // string of obj code
    int addressOfFirstExecInstr; // addr of first executable instruction
    bool flags[6]; // flags n, i, x, b, p, e
    int indexCounter; // line counter for printing .sic file
    int addrDisp; // address of displacement for format 3/4
    int progCounter; // program counter
    int targetAddress; // target address
    int baseCounter; // base counter
    int charsReading; // chars reading in one segment of object code
    string symbolName, symbolFlag; // symbol name/flag
    int symbolAddress; // symbol address
    string literalName; // literal name
    int litLength, litAddress; // literal length and address
    bool symFound, litFound; // bool for if symbol/literal is found
    string fileName; // the file name

    /**
     * Reads and processes the Header Record.
     */
    void readHeaderRecord(string record);

    /**
     * Reads and processes the Text Record.
     */
    void readTextRecord(string record);

    /**
     * Reads and processes the object code given.
     * Reads and processes Text Record until the end of the Record.
     */
    void processObjCode(string objCode);

    /**
     * Reads and processes Modification Records.
     */
    void readModifRecord(string record);

    /**
     * Reads and processes the End Record.
     */
    void readEndRecord(string record);

    /**
     * Finds and returns the OpCode from a segment
     * of object code.
     */
    int findObjOpCode(string lenSixObjCode);

    /**
     * Sets the nixbpe flags in the bool flags[] array.
     */
    void setFlags(string lenSixObjCode, int opCode);

    /**
     * Gets and returns the address/displacement from
     */
    int getAddrDisp(int format, string addrDispObjCode);

    /**
     * Calculates and returns the Target Address.
     */
    int getTargetAddress(int format, int addrDispCode);

    /**
     * Checks if the address/displacement is a symbol address.
     */
    bool checkSymTab(int addrDisp);

    /**
     * Checks if the address/displacement is a literal address.
     */
    bool checkLitTab(int addrDisp);

    /**
     * Handles and outputs processed object code to .sic file.
     */
    void outputSicFile();
    
    void outputToLIS();

public:
    Processor(); // initializer method

    vector<bool> nFlagVect;
    vector<bool> iFlagVect;
    vector<bool> xFlagVect;
    vector<bool> bFlagVect;
    vector<bool> pFlagVect;
    vector<bool> eFlagVect;

    vector<int> opCodeVect;
    vector<int> formatVect;
    vector<string> mneumonicVect;

    // stores symbols for the operands (right side of .sic)
    vector<string> symVect;

    // stores symbols for the declaration (left side of .sic)
    vector<string> symDeclVect;

    vector<string> litVect;

    // stores operands (right side of .sic)
    vector<string> operandVect;

    vector<Symtab::symbols> symTabVect;
    vector<Symtab::literals> litTabVect;

    // stores modification record information
    vector<int> modifVect;

    // stores program counter for each line in .sic
    vector<int> progCounterVect;

    /**
     * Reads the object code.
     */
    void readRecord(string record,
        vector<Symtab::symbols> symbolVect,
        vector<Symtab::literals> literalVect,
        string nameOfFile);

    /**
     * Acquires the program name located in the Header Record.
     */
    string getProgName();

    /**
     * Acquires the starting address of the program in
     * the Header Record.
     */
    int getStartingAddr();

    /**
     * Acquires the length of the program in the Header Record.
     */
    int getLengthOfProg();

    /**
     * Acquires the length of the Text Record.
     */
    int getLengthOfTextRecord();

    /**
     * Acquires the address of the first executable instruction.
     */
    int getAddressOfFirstExecInstr();

    /**
     * Acquires the flags boolean array (nixbpe flags).
     */
    bool* getFlags();


    /**
     * Acquires the index counter.
     */
    int getIndexCounter();

    /**
     * Acquires the program counter.
     */
    string getProgCounter();
    
    char ctoa(char val);
    
    string intToHexString(int val);

    /**
     * Acquires the symbol name at an address/displacement.
     */
    string getSymbolName(int addrDisp);

    /**
     * Acquires the symbol address at an address/displacement.
     */
    int getSymbolAddress(int addrDisp);

    /**
     * Acquires the symbol flag at an address/displacement.
     */
    string getSymbolFlag(int addrDisp);

    /**
     * Acquires the literal name at an address/displacement.
     */
    string getLiteralName(int addrDisp);

    /**
     * Acquires the literal length at an address/displacement.
     */
    int getLiteralLength(int addrDisp);

    /**
     * Acquires the literal address at an address/displacement.
     */
    int getLiteralAddress(int addrDisp);
};
#endif
