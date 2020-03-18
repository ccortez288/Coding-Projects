/* Author: Christian Cortez
 * Class Account: cssc1965
 * CS530, Spring 2020
 * Assignment #1, HexDump/BinDump
 * Filename: hexDump.cpp
 */

#include <iostream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include "dbx.h"

using namespace std;

void hexDump(unsigned char * buff, long size){
    int add = 0;
    int bytesPR = 16;
    //to get each line char by char

    for(int i = 0; i < size; i++){
        int x, j = 0;
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
        cout << setfill('0') << setw(2) << hex << int(buff[i]);

        //for output spacing 
        if((i % 2) - 1 == 0){
            cout<< " ";
        }

            //to print out the file text
          if(i == size - 1)   {
            int lastBytes = size % bytesPR;
            int remainingBytes = bytesPR - lastBytes;
            int offs = (remainingBytes % 2);
            int spaces = remainingBytes / 2;
            int numSpaces = (remainingBytes * 2) + spaces + offs + 2;
            cout << setfill(' ') << setw(numSpaces);

            for(int j = lastBytes - 1; j >= 0; j--){
                if(buff[i-j] < ' ' || buff[i-j] > '~')
                    cout << '.';
                else
                    cout<< buff[i-j];
            }
          } 
    }
   
}
