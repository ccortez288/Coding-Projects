/*Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: dxe.h
*/
#ifndef DXE_H
#define DXE_H

#include "fileReader.h"
#include "Symtab.h"
#include "Processor.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <vector>

class dxe
{
public:
     /**
    * The dxe file receives the necessary
    *    .obj file contents from fileReader, symTab contents 
    *    from the Symtab, error checks for any
    *    possible cases, and runs the Processor to process
    *    the entire object code.
    */
   int main(int argc, char *argv[]);
};

#endif
