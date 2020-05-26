/*Christian Cortez cssc1965 
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: fileReader.h
*/
#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>
#include <string.h>
using namespace std;

class fileReader{
    public:
        //Returns string of filename
        string getObj(char []); 
        
        //Returns contents of object file in string
        string getObjText(std::string);
};

#endif 
