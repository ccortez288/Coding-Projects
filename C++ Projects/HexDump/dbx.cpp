/* Author: Christian Cortez
 * Class Account: cssc1965
 * CS530, Spring 2020
 * Assignment #1, HexDump/BinDump
 * Filename: dbx.cpp
 */

#include <iostream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include "dbx.h"

using namespace std;


int main(int argc, char* argv[]) {
 
  //find the index of the file  
  int findex = (argc == 3)? 2:1;
  long sz;

  FILE * f;

  //open file to read binary bytes in

  f = fopen(argv[findex], "rb");
  if (f == NULL) {
    fputs("Error, file is NULL", stderr);
    cout << endl;
    exit (1);
  }

  fseek(f, 0, SEEK_END);
  sz = ftell(f);
  rewind(f);

  unsigned char * buff = (unsigned char*) malloc (sizeof(char)*sz);

  fread(buff, 1, sz, f);
  fclose(f);

 if(argc == 3) {
  binaryDump(buff, sz); 
 }
 
 hexDump (buff, sz);
 
cout << endl;

 free(buff);
 return 0;
}
