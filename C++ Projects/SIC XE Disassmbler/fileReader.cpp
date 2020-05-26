/*Christian Cortez cssc1965
*  CS530, Spring 2020
*  Assignment #2 SIC/XE Dissasembler
*  File: fileReader.cpp
*/
#include "fileReader.h" 
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <exception>
using namespace std;

//Returns string of f
string fileReader::getObj(char file[]){
    string f;
    ifstream objFile(file);
    if(objFile){
        f.append(file);
        return f;
    }
}

//Returns contents of object file in a string
string fileReader::getObjText(std::string f){
    string temp;
    string text;
    char *x;
    ifstream objFile(f.c_str());
    while(objFile.good()){
        getline(objFile, temp);
        text.append(temp);  
    }
    
    return text;
}
