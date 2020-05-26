/* Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: Processor.cpp
*/

#include "Processor.h"

Processor::Processor()
{
    progName = "";
    startingAddress = -1;
    lengthOfProg = -1;
    textRecordStartingAddress = -1;
    lengthOfTextRecord = -1;
    objCode = "";
    addressOfFirstExecInstr = -1;
    addrDisp = -1;
    progCounter = 0;
    targetAddress = 0;
    baseCounter = 0;
    charsReading = 0;

    for(int i = 0; i < NUM_OF_FLAGS; i ++)
    {
        flags[i] = false;
    }

    indexCounter = 0;

    int resizeSize = 100;

    nFlagVect.resize(resizeSize);
    iFlagVect.resize(resizeSize);
    xFlagVect.resize(resizeSize);
    bFlagVect.resize(resizeSize);
    pFlagVect.resize(resizeSize);
    eFlagVect.resize(resizeSize);

    opCodeVect.resize(resizeSize);
    formatVect.resize(resizeSize);
    mneumonicVect.resize(resizeSize);

    symVect.resize(resizeSize);
    symDeclVect.resize(resizeSize);
    litVect.resize(resizeSize);
    operandVect.resize(resizeSize);
    modifVect.resize(resizeSize);
    progCounterVect.resize(resizeSize);
    operandVect.resize(resizeSize);
}

void Processor::readRecord(string record,
    vector<Symtab::symbols> symbolVect,
    vector<Symtab::literals> literalVect,
    string nameOfFile)
{
    string tmpRecord = record;
    symTabVect = symbolVect;
    litTabVect = literalVect;
    fileName = nameOfFile;
	
	
    while(true)
    {
        

        if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "H")
        {
  	        readHeaderRecord(tmpRecord);
	        tmpRecord = tmpRecord.substr(HEADER_REC_LEN);
        }
        else if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "T")
        {
  	        readTextRecord(tmpRecord);
            tmpRecord = tmpRecord.substr((lengthOfTextRecord * 2) +
                START_OF_TEXT_RECORD);
        }
        else if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "E")
        {
            readEndRecord(tmpRecord);
            tmpRecord = tmpRecord.substr(END_REC_LEN);
        }
        else if(tmpRecord.substr(FIRST_LETR_IN_REC, FIRST_LETR_LEN) == "M")
        {
            readModifRecord(tmpRecord);
            tmpRecord = tmpRecord.substr(MODIF_REC_LEN);
        }
	
	if(tmpRecord.length() <= 0)
        {
	    //This is where the bug appears to be	    
	    outputSicFile();
	    outputToLIS();
            return;
        }
    }
}

void Processor::readHeaderRecord(string record)
{

    progName = record.substr(1,6);

    istringstream(record.substr(7, 6)) >> hex >> startingAddress;
    istringstream(record.substr(13, 6)) >> hex >> lengthOfProg;
}

void Processor::readTextRecord(string record)
{
    int halfBytesRead = 0; // increment everytime a halfbyte is read
                           // in the object code for the text record

    istringstream(record.substr(1, 6)) >>
	    hex >> textRecordStartingAddress;
    istringstream(record.substr(7, 2)) >> hex >> lengthOfTextRecord;
    istringstream(record.substr(9)) >> hex >> objCode;

    processObjCode(objCode);
}

void Processor::processObjCode(string objCode)
{
    string methodObjCode = objCode;

    while(methodObjCode.length() > 0)
    {
        if(methodObjCode.substr(0, 1) == "M" ||
            methodObjCode.substr(0, 1) == "E" ||
	     methodObjCode.substr(0, 1) == "T")
        {
            return; // return if end of Text Record
        }

        string lenSixObjCode = methodObjCode.substr(0, 6);

        OpcodeTable opTab;
        int addrDisp;
        int opCode = opTab.getOpCode(findObjOpCode(lenSixObjCode));
        int format = opTab.getFormat(opCode);
        string mneumonic = opTab.getMneumonic(opCode);

        if(format == 3 || format == 4)
        {
            setFlags(lenSixObjCode, opCode);
        }

        if(getFlags()[5] == false)
        {
            // e flag = 0
            addrDisp = getAddrDisp(format, lenSixObjCode.substr(3, 3));
        }
        else
        {
            // e flag = 1
            format = 4;
            lenSixObjCode = methodObjCode.substr(0, 8);
            addrDisp = getAddrDisp(format, lenSixObjCode.substr(3, 5));
        }

        charsReading = format * 2; // amount of chars in objcode being read
        targetAddress = getTargetAddress(format, addrDisp);

        if(mneumonic.compare("LDB") == 0)
        {
             baseCounter = targetAddress;
        }

        // O(1) Amortized Array Resizing
        if(indexCounter == nFlagVect.size() - 1)
        {
            // resize all vectors
            nFlagVect.resize(nFlagVect.size() * 2);
            iFlagVect.resize(iFlagVect.size() * 2);
            xFlagVect.resize(xFlagVect.size() * 2);
            bFlagVect.resize(bFlagVect.size() * 2);
            pFlagVect.resize(pFlagVect.size() * 2);
            eFlagVect.resize(eFlagVect.size() * 2);

            opCodeVect.resize(opCodeVect.size() * 2);
            formatVect.resize(formatVect.size() * 2);
            mneumonicVect.resize(mneumonicVect.size() * 2);
            operandVect.resize(operandVect.size() * 2);
            symVect.resize(symVect.size() * 2);
            symDeclVect.resize(symDeclVect.size() * 2);
            litVect.resize(litVect.size() * 2);
            operandVect.resize(operandVect.size() * 2);
            modifVect.resize(modifVect.size() * 2);
            progCounterVect.resize(progCounterVect.size() * 2);
        }

        nFlagVect[indexCounter] = getFlags()[0];
        iFlagVect[indexCounter] = getFlags()[1];
        xFlagVect[indexCounter] = getFlags()[2];
        bFlagVect[indexCounter] = getFlags()[3];
        pFlagVect[indexCounter] = getFlags()[4];
        eFlagVect[indexCounter] = getFlags()[5];

        opCodeVect[indexCounter] = opCode;
        formatVect[indexCounter] = format;
        mneumonicVect[indexCounter] = mneumonic;

        // Format 1, no other calculations,etc. necessary
        // All we need is the mneumonic.
        string registers;

        if(format == 1)
        {
            operandVect[indexCounter] = "";
        }
        else if(format == 2)
        {
            string reg1 = lenSixObjCode.substr(2,1);
            string reg2 = lenSixObjCode.substr(3,1);
            if(reg1.compare("0") == 0) {
               registers="A,";
            } else if(reg1.compare("1") == 0) {
               registers="X,";
            } else if(reg1.compare("2") == 0) {
               registers="L,";
            } else if(reg1.compare("3") == 0) {
               registers="B,";
            } else if(reg1.compare("4") == 0) {
               registers="S,";
            } else if(reg1.compare("5") == 0) {
               registers="T,";
            } else if(reg1.compare("6") == 0) {
               registers="F,";
            }

            //looking at second register
            if(reg2.compare("0") == 0) {
               registers.append("A");
            } else if(reg2.compare("1") == 0) {
               registers.append("X");
            } else if(reg2.compare("2") == 0) {
               registers.append("L");
            } else if(reg2.compare("3") == 0) {
               registers.append("B");
            } else if(reg2.compare("4") == 0) {
               registers.append("S");
            } else if(reg2.compare("5") == 0) {
               registers.append("T");
            } else if(reg2.compare("6") == 0) {
               registers.append("F");
            }
            operandVect[indexCounter] = registers;
        }

        else if(format == 3 || format == 4)
        {
            symFound = checkSymTab(targetAddress);
            litFound = checkLitTab(addrDisp);

            // symbol found or literal found?
            // if symbol, store name into symVect for .sic file
            // if literal, store name into litVect for .sic file
            // add to charsReading due to literal length in obj code

            //final flag check
            bool bpe = getFlags()[5] || getFlags()[4] || getFlags()[3];

            //accounts for simple addressing and indirect addressing
            bpe|=getFlags()[0];

            // one of the bpe bits have to be set to process label
            if(symFound && bpe)
            {
                string symbol = getSymbolName(targetAddress);
                symVect[indexCounter] = symbol;

                if(getFlags()[2]) // indexing
                {
                    symbol.append(",X");
                }
                if(getFlags()[0]&&!getFlags()[1]) // indirect
                {
                    symbol.insert(0, "@");
                }
                if(!getFlags()[0]&&getFlags()[1]) // immediate
                {
                    symbol.insert(0, "#");
                }
                operandVect[indexCounter] = symbol;
                symFound=false;
            }
            else
            {
                if(!getFlags()[0] && getFlags()[1]) // immediate
                {
                   stringstream ss;
                   ss << targetAddress;
                   string immediate;
                   ss >> immediate;
                   immediate.insert(0,"#");
                   operandVect[indexCounter] = immediate;
                }
            }

            if(litFound)
            {
                string litName = getLiteralName(addrDisp);
                litVect[indexCounter] = litName;
                int indexOfQuote = litVect[indexCounter].find("'");
                charsReading +=
                    litVect[indexCounter].substr(3, indexOfQuote).length();
                litFound = false;
                operandVect[indexCounter] = litName;
            }
        }

        //SPECIAL CASE FOR RSUB, DOES NOT TAKE ANY OPERANDS
        if(mneumonic.compare("RSUB") == 0)
        {
            operandVect[indexCounter] = "";
        }

        if(checkSymTab(progCounter))
        {
            for(int i = 0; i < symTabVect.size(); i ++)
            {
                symDeclVect[indexCounter] = getSymbolName(progCounter);
            }
        }

        progCounterVect[indexCounter] = progCounter;

        if(format == 1)
        {
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }
        else if(format == 2)
        {
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }
        else if(format == 3)
        {
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }
        else
        {
            // format == 4
            // e flag = 1, extended means two more halfbytes
            methodObjCode = methodObjCode.substr(charsReading);

            progCounter += ceil(charsReading / 2);
        }

        indexCounter ++;
    }
}

void Processor::readModifRecord(string record)
{
    int modifAddress, modifLen, index;

    string strModifAddress = record.substr(1, 6);
    string strModifLen = record.substr(7, 2); // in half bytes

    istringstream(strModifAddress) >> hex >> modifAddress;
    istringstream(strModifLen) >> hex >> modifLen;

    for(int i = 0; i < indexCounter; i ++)
    {
        if(modifAddress == 5 && progCounterVect[i] == (modifAddress - 1))
        {
            modifVect[i] = modifLen;
        }
        else if(modifAddress == 6 && progCounterVect[i] == modifAddress)
        {
            modifVect[i] = modifLen;
        }
    }
}

void Processor::readEndRecord(string record)
{
    istringstream(record.substr(1,6)) >> addressOfFirstExecInstr;
}

int Processor::findObjOpCode(string lenSixObjCode)
{
    int ret;

    istringstream(lenSixObjCode.substr(0, 2)) >> hex >> ret;

    return ret;
}

void Processor::setFlags(string lenSixObjCode, int opCode)
{
    int niFlags, niFlagsVal;
    istringstream(lenSixObjCode.substr(0, 2)) >> hex >> niFlagsVal;
    niFlags = niFlagsVal - opCode;

    if (niFlags == 3)
    {
        flags[0] = true; // n flag
        flags[1] = true; // i flag
    }
    else if (niFlags == 2)
    {
        flags[0] = true; // n flag
        flags[1] = false; // i flag
    }
    else if (niFlags == 1)
    {
        flags[0] = false; // n flag
        flags[1] = true; // i flag
    }

    int xbpeFlags;
    istringstream(lenSixObjCode.substr(2, 1)) >> hex >> xbpeFlags;

    if (xbpeFlags / 8 == 1)
    {
        flags[2] = true; // x flag
        xbpeFlags %= 8;
    }
    else
    {
        flags[2] = false;
        // dont need to do xbpeFlags %= 8;
    }

    if (xbpeFlags / 4 == 1)
    {
        flags[3] = true; // b flag
        xbpeFlags %= 4;
    }
    else
    {
        flags[3] = false;
    }

    if (xbpeFlags / 2 == 1)
    {
        flags[4] = true; // p flag
        xbpeFlags %= 2;
    }
    else
    {
        flags[4] = false;
    }

    if (xbpeFlags / 1 == 1)
    {
        flags[5] = true; // e flag
        xbpeFlags %= 1;
    }
    else
    {
        flags[5] = false;
    }
}

int Processor::getAddrDisp(int format, string addrDispObjCode)
{
    unsigned int ret;

    if(addrDispObjCode.substr(0, 1) == "F")
    {
        for(int i = 0; addrDispObjCode.length() < 8; i ++)
        {
            addrDispObjCode = "F" + addrDispObjCode;
        }
    }

    stringstream strStream;
    strStream << hex << addrDispObjCode;
    strStream >> ret;
    ret = static_cast<int>(ret);

    return ret;
}

int Processor::getTargetAddress(int format, int addrDispCode)
{
    int addressDisp, ret;
    addressDisp = addrDispCode;

    if(format == 3)
    {
        // check if pc relative or base relative
        // calculate targetAddress based off this
        if(flags[4] == true)
        {
            ret = progCounter + 3 + addressDisp;
            // +3 = length of instr
        }
        else if(flags[3] == true)
        {
            ret = baseCounter + addressDisp;
        }
        else
        {
            ret = addressDisp;
        }
    }
    else if(format == 4)
    {
        ret = addressDisp;
    }
    return ret;
}

bool Processor::checkSymTab(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return true;
        }
    }
}

bool Processor::checkLitTab(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return true;
        }
    }
}

//Outputs the .lis file
void Processor::outputToLIS(){
    vector<string> outputVector;
    outputVector.resize(100); // default resize to 100
    int j= 0;
    ofstream outputStream;
    int position = fileName.find_last_of(".");
    fileName.erase(position, 4);
    string lisFileName = fileName.append(".lis");
    outputStream.open(lisFileName.c_str());

    string lastUsedSymbolName = "";
    int lastUsedSymbolIndex = 0;
    
    outputStream << "0000 ";
    outputStream << setw(SPACE_PER_SECTION) << left << progName;
    outputStream << setw(SPACE_PER_SECTION + 1) << " START";
    outputStream << setw(SPACE_PER_SECTION) << startingAddress
        << endl;;
	
    outputStream << "0000 ";
    outputStream << setw(SPACE_PER_SECTION) << symDeclVect[0]; 
    string instruction = " " + mneumonicVect[0];
    outputStream << setw(SPACE_PER_SECTION) << instruction;
    string fullInstr = " " + operandVect[0];
    outputStream << setw(SPACE_PER_SECTION) << fullInstr;
    outputStream << endl;  
    
    for(int i = 1; i < indexCounter; i ++)
    {
    	
//outputStream << getProgCounter() << " ";
        // if last mneumonic was LDB, BASE
        if(i > 0 && mneumonicVect[i - 1] == "LDB")
        {
           
	    outputStream << getProgCounter() << " ";
            string fullInstr = " " + symVect[i - 1];
            outputStream << setw(SPACE_PER_SECTION) << "";
            outputStream << setw(SPACE_PER_SECTION) << " BASE";
            outputStream << setw(SPACE_PER_SECTION) << fullInstr;
	    j+=6;
            outputStream << endl;
        }

        // if last instruction had a literal, LTORG
        if(i > 0 && litVect[i - 1] != "")
        {
	
	    outputStream << getProgCounter() << " ";
            outputStream << setw(SPACE_PER_SECTION) << "";
            outputStream << setw(SPACE_PER_SECTION) << " LTORG";
	    outputStream << "		" << objCode.substr(j, 6);
	    j+=6;
	    progCounter +=3;
            outputStream << endl;
        }
	
	outputStream << getProgCounter() << " ";
        outputStream << setw(SPACE_PER_SECTION) << symDeclVect[i]; 

        if(symDeclVect[i] != "")
        {
            lastUsedSymbolName = symDeclVect[i];
        }

        if(eFlagVect[i] == true)
        {
            //outputStream << getProgCounter() << " "; //Keep
	    string fullInstr = "+" + mneumonicVect[i];
            outputStream << setw(SPACE_PER_SECTION) << fullInstr;
        }
        else
        {
	    //outputStream << getProgCounter() << " ";
            string fullInstr = " " + mneumonicVect[i];
            outputStream << setw(SPACE_PER_SECTION) << fullInstr;
        }

        if(operandVect[i].substr(0, 1) == "#" ||
            operandVect[i].substr(0, 1) == "@" ||
            operandVect[i].substr(0, 1) == "=" ||
            operandVect[i].substr(0, 1) == "+")
        {
	    //outputStream << getProgCounter() << " ";
            outputStream << setw(SPACE_PER_SECTION) << operandVect[i];
	    
        }
        else
        {
            string fullInstr = " " + operandVect[i]; 
	    outputStream << setw(SPACE_PER_SECTION) << fullInstr;
        }
	if(eFlagVect[i] == true){
	 	outputStream << "	" << objCode.substr(j, 8);
	 	progCounter +=4;
        }
	else {
	outputStream << "	" << objCode.substr(j, 6);
	}
	progCounter +=3;
        outputStream << endl;
	j+=6;
	
    }

    
    //This is where the bug is
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].name == lastUsedSymbolName)
        {
            lastUsedSymbolIndex = i;
        }
    }  
    
    progCounter +=3;
    bool firstRun = true;
    int addr, diff;
    
    //lastUsedSymbolIndex and the symTabVect.size() don't get passed in correctly
    // so the program skips this whole loop. Rationelle for this is unknown. 
    
    
    while(lastUsedSymbolIndex < symTabVect.size() - 1)
    {
    	outputStream << getProgCounter() << " ";
        if(indexCounter == progCounterVect.size() - 1)
        {
            progCounterVect.resize(progCounterVect.size() * 2);
        }

        if(firstRun)
        {
            addr = symTabVect[lastUsedSymbolIndex + 1].addr;
            diff = addr - progCounterVect[indexCounter - 1];
            progCounterVect[indexCounter] = addr + diff;
            firstRun = false;
        }
        else
        {
            if(lastUsedSymbolIndex < symTabVect.size() - 2)
            {
                addr = symTabVect[lastUsedSymbolIndex + 2].addr;
                diff = addr - symTabVect[lastUsedSymbolIndex + 1].addr;
                progCounterVect[indexCounter] =
                    symTabVect[lastUsedSymbolIndex + 1].addr;
            }
            else // last symbol
            {
                addr = lengthOfProg; // last symbol, use length of prog
                diff = addr - symTabVect[lastUsedSymbolIndex + 1].addr;
                progCounterVect[indexCounter] =
                    symTabVect[lastUsedSymbolIndex + 1].addr;
            }
        }

        if(indexCounter == symDeclVect.size() - 1)
        {
            symDeclVect.resize(symDeclVect.size() * 2);
        }

        symDeclVect[indexCounter] = symTabVect[lastUsedSymbolIndex + 1].name;
        string symNameOutput = symTabVect[lastUsedSymbolIndex + 1].name;

        outputStream << setw(SPACE_PER_SECTION) << symNameOutput;
        int numOfWords = 0;
	
        if(diff % 3 == 0)
        {
            numOfWords = diff / 3;
            outputStream << setw(SPACE_PER_SECTION + 1) << " RESW";
        }
        else
        {
            outputStream << setw(SPACE_PER_SECTION + 1) << " RESB";
        }

        outputStream << setw(SPACE_PER_SECTION) <<  numOfWords;

        outputStream << endl;

        lastUsedSymbolIndex ++;
        indexCounter ++;
	progCounter *=3;
    }

    	outputStream << "    ";
    	outputStream << " END";
    	outputStream << " "<<setw(SPACE_PER_SECTION) << symTabVect[0].name
        << endl;           
}


void Processor::outputSicFile()
{
    vector<string> outputVector;
    outputVector.resize(100); // default resize to 100

    ofstream outputStream;
   // int position = fileName.find_last_of(".");
    //fileName.erase(position, 4);
    string sicFileName = fileName.append(".sic");
    outputStream.open(sicFileName.c_str());

    string lastUsedSymName = "";
    int lastUsedSymIndex = 0;

    outputStream << setw(SPACE_PER_SECTION) << left << progName;
    outputStream << setw(SPACE_PER_SECTION + 1) << " START";
    outputStream << setw(SPACE_PER_SECTION) << startingAddress
        << std::endl;

    for(int i = 0; i < indexCounter; i ++)
    {
        // if last mneumonic was LDB, BASE
        if(i > 0 && mneumonicVect[i - 1] == "LDB")
        {
            std::string fullInstr = " " + symVect[i - 1];
            outputStream << setw(SPACE_PER_SECTION) << "";
            outputStream << setw(SPACE_PER_SECTION) << " BASE";
            outputStream << setw(SPACE_PER_SECTION) << fullInstr;
            outputStream << endl;
        }

        // if last instruction had a literal, LTORG
        if(i > 0 && litVect[i - 1] != "")
        {
            outputStream << setw(SPACE_PER_SECTION) << "";
            outputStream << setw(SPACE_PER_SECTION) << " LTORG";
            outputStream << endl;
        }

        outputStream << setw(SPACE_PER_SECTION) << symDeclVect[i];

        if(symDeclVect[i] != "")
        {
            lastUsedSymName = symDeclVect[i];
        }

        if(eFlagVect[i] == true)
        {
            string fullInstr = "+" + mneumonicVect[i];
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
        }
        else
        {
            std::string fullInstr = " " + mneumonicVect[i];
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
        }

        if(operandVect[i].substr(0, 1) == "#" ||
            operandVect[i].substr(0, 1) == "@" ||
            operandVect[i].substr(0, 1) == "=" ||
            operandVect[i].substr(0, 1) == "+")
        {
            outputStream << std::setw(SPACE_PER_SECTION) << operandVect[i];
        }
        else
        {
            string fullInstr = " " + operandVect[i];
            outputStream << std::setw(SPACE_PER_SECTION) << fullInstr;
        }

        outputStream << std::endl;
    }

    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].name == lastUsedSymName)
        {
            lastUsedSymIndex = i;
        }
    }
    
   
    bool fRun = true;
    int address, difference;
    while(lastUsedSymIndex < symTabVect.size() -1)
    {
        if(indexCounter == progCounterVect.size() - 1)
        {
            progCounterVect.resize(progCounterVect.size() * 2);
        }

        if(fRun)
        {
            address = symTabVect[lastUsedSymIndex + 1].addr;
            difference = address - progCounterVect[indexCounter - 1];
            progCounterVect[indexCounter] = address + difference;
            fRun = false;
        }
        else
        {
            if(lastUsedSymIndex < symTabVect.size() - 2)
            {
                address = symTabVect[lastUsedSymIndex + 2].addr;
                difference = address - symTabVect[lastUsedSymIndex + 1].addr;
                progCounterVect[indexCounter] =
                    symTabVect[lastUsedSymIndex + 1].addr;
            }
            else // last symbol
            {
                address = lengthOfProg; // last symbol, use length of prog
                difference = address - symTabVect[lastUsedSymIndex + 1].addr;
                progCounterVect[indexCounter] =
                    symTabVect[lastUsedSymIndex + 1].addr;
            }
        }

        if(indexCounter == symDeclVect.size() - 1)
        {
            symDeclVect.resize(symDeclVect.size() * 2);
        }

        symDeclVect[indexCounter] = symTabVect[lastUsedSymIndex + 1].name;
        string symNameOutput = symTabVect[lastUsedSymIndex + 1].name;


        outputStream << setw(SPACE_PER_SECTION) << symNameOutput;

        int numberOfWords = 0;

        if(difference % 3 == 0)
        {
            numberOfWords = difference / 3;
            outputStream << setw(SPACE_PER_SECTION + 1) << " RESW";
        }
        else
        {
            outputStream << setw(SPACE_PER_SECTION + 1) << " RESB";
        }

        outputStream << setw(SPACE_PER_SECTION) <<  numberOfWords;

        outputStream << endl;

        lastUsedSymIndex ++;
        indexCounter ++;
    }

    outputStream << std::setw(SPACE_PER_SECTION) << "";
    outputStream << std::setw(SPACE_PER_SECTION) << " END";
    outputStream << " "<<std::setw(SPACE_PER_SECTION) << symTabVect[0].name
        << std::endl;


}



string Processor::getProgName()
{
    return progName;
}

int Processor::getStartingAddr()
{
    return startingAddress;
}

int Processor::getLengthOfProg()
{
    return lengthOfProg;
}

int Processor::getLengthOfTextRecord()
{
    return lengthOfTextRecord;
}

int Processor::getAddressOfFirstExecInstr()
{
    return addressOfFirstExecInstr;
}

bool* Processor::getFlags()
{
    return flags;
}

int Processor::getIndexCounter()
{
    return indexCounter;
}


string Processor::getProgCounter() {
  std::string returnState = "0000";
		std::string temp = intToHexString(progCounter);
		for (char j = 0; j <= 4; j++) {
			returnState[j] = temp[j + 2];
		}
		return returnState;
}
char Processor ::ctoa(char val){
  //converts numerical value to ascii value
		if (val >= 0 && val < 10) {
			val += 48;
		}
		else if (val >= 10 && val < 16) {
			val += 55;
		}
		return val;
}
    /**
     * Acquires the program counter.
     */


string Processor::intToHexString(int val) {
  //given an integer, will convert to six character hexidecimal string
		std::string returnState = "000000";
		char temp = 0;
		if (val >= 268435456) {
			//16^7
			char temp = val / 268435456;
			val -= temp * 268435456;
		}
		if (val >= 16777216) {
			//16^6
			char temp = val / 16777216;
			val -= temp * 16777216;
		}
		if (val >= 1048576) {
			//16^5
			char temp = val / 1048576;
			val -= temp * 1048576;
			temp = ctoa(temp);
			returnState[0] = temp;
		}
		if (val >= 65536) {
			//16^4
			char temp = val / 65536;
			val -= temp * 65536;
			temp = ctoa(temp);
			returnState[1] = temp;
		}
		if (val >= 4096) {
			//16^3
			char temp = val / 4096;
			val -= temp * 4096;
			temp = ctoa(temp);
			returnState[2] = temp;
		}
		if (val >= 256) {
			//16^2
			char temp = val / 256;
			val -= temp * 256;
			temp = ctoa(temp);
			returnState[3] = temp;
		}
		if (val >= 16) {
			//16^1
			char temp = val / 16;
			val -= temp * 16;
			temp = ctoa(temp);
			returnState[4] = temp;
		}
		if (val != 0) {
			//16^0
			char temp = val;
			val -= temp; //should be 0
			temp = ctoa(temp);
			returnState[5] = temp;
		}
		return returnState;
}

string Processor::getSymbolName(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return symTabVect[i].name;
        }
    }
}

int Processor::getSymbolAddress(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return symTabVect[i].addr;
        }
    }
}

string Processor::getSymbolFlag(int addrDisp)
{
    for(int i = 0; i < symTabVect.size(); i ++)
    {
        if(symTabVect[i].addr == addrDisp)
        {
            return symTabVect[i].flag;
        }
    }
}

string Processor::getLiteralName(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return litTabVect[i].lit;
        }
    }
}

int Processor::getLiteralLength(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return litTabVect[i].length;
        }
    }
}

int Processor::getLiteralAddress(int addrDisp)
{
    for(int i = 0; i < litTabVect.size(); i ++)
    {
        if(litTabVect[i].addr == addrDisp)
        {
            return litTabVect[i].addr;
        }
    }
}
