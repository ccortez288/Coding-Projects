Christian Cortez (cssc1965)
CS 530, Spring 2020
Assignment #2, SIC/XE Disassembler
Filename: README.txt
Files included in this project:

This project includes these files:

- dxe.cpp/.h
- fileReader.cpp/h
- Symtab.cpp/h
- Processor.cpp/h
- OpcodeTable.cpp/h
- makefile
- sample.obj/.sym

## Compilation

In order to compile this program:

 There is a makefile in  ~/cssc1965/a2 named makefile. 

 - Enter the directory by typing the command cd  ~/cssc1965/a2

 - There are two ways to use this makefile: You can compile by using the command make,
   or you can compile it by using make clean, the last one deletes any previous object files
    ,and is perhaps more recommneded.

## Usage

To use the Dissasembler, type the following: 

	dxe <filename>.obj

Note: The sample.obj and sample.sym file must both be included within the same directory as all the files being used for testing in order for this to work right. 

## Design Decision

At first during development, there was files for cataloguing data and a littab that arent included now. During testing and in the process of putting it all together he cataloguing data and processor file were consolidated into the one Processor.cpp. The same process happened with the littab and symtab file. In order to streamline it and make the code less cluttered they were both put into one. Another significant decision made towards the testing phase was to change all our most of the data structures in the code to vectors. This made it easier to pass information from one file to the other since at first there was some variation in this aspect. The OpcodeTable was changed into an array since it made things easier with the getters in the file. Overall these decisions were made to consolidate the code as much as possible and to make it as easy to use as possible.  

## List of all known deficiencies or bugs

The .lis file outputs incorrectly since when it is called after the outputSicFIle(),  the loop that should handle printing the "TABLE RESW 2000" section is getting skipper over. This causes that whole section to be blank and since it skips over the loop it just keeps printing object code that it shouldn't. This only happens when it is called after outputSicFile(), when the outputSicFile() call doesn't precede it it works correctly. The place where this happensis commented in the Processor.cpp file  

## Lessons Learned

A better understanding of data structures in C++. A deeper knowledge of the SIC/XE machine family. Communication and pre planning as a team is crucial to the success of a group project of this type. 
