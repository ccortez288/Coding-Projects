/* Author: Christian Cortez
 * Class Account: cssc1965
 * CS530, Spring 2020
 * Assignment #1, HexDump/BinDump
 * Filename: binaryDump.cpp
 */

#include <iostream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include "dbx.h"

using namespace std;

string hexToBin(int num);

void binaryDump(unsigned char * buff, long size){
    int add = 0;
    int bytesPR = 6;
    int i = 0;
     //to get each line char by char
  
   //same as hex dump
    for(i = 0; i < size; i++){
        int j = 0;
           //prints ASCII 
        if(i % bytesPR == 0 && i != 0){
          cout << " ";
            for(j = bytesPR; j > 0; j--){
              if(buff[i-j] < ' ' || buff[i-j] > '~')
                  cout << '.';
              else
                  cout<< buff[i-j];
          }
          cout << endl;
        }

        if (i % bytesPR == 0) {
          cout << setfill('0') << setw(7) << hex << add << ": ";
          add += bytesPR;
        }

        //print hex byte in binary
        cout << hexToBin(int(buff[i]));

        //same as hex dump
       if(i == size - 1)   {
            int lastBytes = size % bytesPR;
            int remainingBytes = bytesPR - lastBytes;
            int numSpaces = (remainingBytes * 9) + 3;
            cout << setfill(' ') << setw(numSpaces);

            for(int j = lastBytes - 1; j >= 0; j--){
                if(buff[i-j] < ' ' || buff[i-j] > '~')
                    cout << '.';
                else
                    cout<< buff[i-j];
            }
          }
          cout << " "; 
    }
}

string hexToBin(int num) {
  int i = 0;
  string number = "";
  int numb = num/16;
  for(i = 0; i < 2; i ++) {
    switch(numb) {
      case 0:
          number.append("0000");
          break;
      case 1:
          number.append("0001");
          break;
      case 2:
          number.append("0010");
          break;
      case 3:
          number.append("0011");
          break;
      case 4:
          number.append("0100");
          break;
      case 5:
          number.append("0101");
          break;
      case 6:
          number.append("0110");
          break;
      case 7:
          number.append("0111");
          break;
      case 8:
          number.append("1000");
          break;
      case 9:
          number.append("1001");
          break;
      case 10:
          number.append("1010");
          break;
      case 11:
          number.append("1011");
          break;
      case 12:
          number.append("1100");
          break;
      case 13:
          number.append("1101");
          break;
      case 14:
          number.append("1110");
          break;
      case 15:
          number.append("1111");
          break;
    }
    numb = num%16;
  }
  return number;
}
