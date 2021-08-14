
/*++

Creating MBCS and UNICODE application.
	Write a structure containing TCHAR string into file.
	  In UNICODE application, read file and convert it into MBCS structure, and write MBCS structure into file..
	  Then read MBCS file using MBCS application.
  
Module Name:
		    MultibyteToUnicode.cpp

Abstract:
			This module handles MBCS to Unicode conversion.

--*/

#include<iostream>
#include<fstream>
#include<string>
#include<tchar.h>
#include<windows.h>
using namespace std;


int main()
{
	string line;
	DWORD minSize,size;
	streampos begin,end;
	ifstream infile("input.txt");     
	ofstream outfile("output.txt");
	begin=infile.tellg();
	infile.seekg (0,infile.end);
	end=infile.tellg();
	size = end-begin;
	infile.seekg(0);
	LPCSTR multiByteStr=(LPCSTR)new TCHAR[size];
	infile.read((char *)multiByteStr,size);
	
	// Get the required size of the buffer that receives the multiByte string. 
	minSize = MultiByteToWideChar(CP_UTF8, 0, multiByteStr, -1, NULL, 0);
	LPWSTR unicodeStr=new TCHAR[minSize];
	MultiByteToWideChar(CP_UTF8, 0, multiByteStr, -1, unicodeStr, minSize); 
	outfile.write((const char *)unicodeStr,minSize);
	delete[] multiByteStr;
	delete[] unicodeStr;
	outfile.close();
	infile.close();
	return 0;
}
