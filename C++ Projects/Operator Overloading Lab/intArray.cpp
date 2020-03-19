/*
*Program #5
*Operator Overloading Lab
*CS320-01
*November 18th, 2019
*@Author - Christian Cortez cssc0468
*/

#include "intArray.h"
#include <iostream>
#include <fstream>

using namespace std;
extern ofstream csis;

IntArray::IntArray (){
  size = 10;
  lo = 0;
  hi = size -1;
  pA = new int[hi - lo];
};

IntArray::IntArray (int size) {
  lo = 0;
  hi = size -1;
  pA = new int[hi - lo];
};

IntArray::IntArray (int lowerBound, int upperBound) {
  if(lowerBound > upperBound) {
  cout<<"Illegal array bounds passed. Simulating halt." <<endl;
  }
  else if(lowerBound == upperBound) {
    size = 1;
    lo = lowerBound;
    hi = upperBound;
    pA = new int[size];
}
  else {
    size = (upperBound-lowerBound) + 1;
     lo = lowerBound;
     hi = upperBound;
     pA = new int[size];
}
}

IntArray::IntArray(const IntArray& array){
  name = array.name;
  size = array.size;
  hi = array.hi;
  lo = array.lo;
  pA= new int[size];
  for(int i = 0; i < size; i++) {
    pA[i] = array.pA[i];
  }
}

IntArray::~IntArray(){
  if(size > 0) delete []pA;
 }
 
void IntArray:: setName(const char *n){
  name = n;
}

void IntArray:: getName() {
  cout << name << endl;
}

int IntArray::high() {
  return hi;
}
int IntArray::low() {
  return lo;
}

// Overloaded operators
int IntArray:: operator==(const IntArray& array) {
if(size == array.size) {
for(int i = 0; i < array.size; i++) {
if(pA[i] != array.pA[i]){return 0;}
}
return 1;
} else return 0;
}
int IntArray::operator!=(const IntArray& array){
if(size == array.size) {
for(int i = 0; i < array.size; i++) {
if(pA[i] != array.pA[i]){return 1;}

