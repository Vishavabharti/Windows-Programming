/*++
Creating MBCS and UNICODE application.
	Write a structure containing TCHAR string into file.
	  In UNICODE application, read file and convert it into MBCS structure, and write MBCS structure into file..
	  Then read MBCS file using MBCS application.
  
Module Name:
			UnicodeToMultibyte.cpp

Abstract:
			This module handles Unicode to multi-byte conversion.
	
--*/


#include<iostream>
#include<fstream>
#include<string.h>
#include<tchar.h>
#include<windows.h>

using namespace std;

int main()
{
	string line;
	DWORD minsize,size;

	streampos begin,end;
	
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	begin=infile.tellg();
	infile.seekg (0,infile.end);
	end=infile.tellg();
	size = end-begin;
	infile.seekg(0);
	LPCWSTR UnicodeStr=new TCHAR[size];
	infile.read((char *)UnicodeStr,size);

	//get the required size of the buffer that receives the multibyte string. 
	minsize = WideCharToMultiByte(CP_UTF8,NULL,UnicodeStr,-1,NULL,0,NULL,false);
	LPSTR MultiByteStr=(LPSTR)new TCHAR[minsize];
	//convert string from Unicode to multi-byte.
	WideCharToMultiByte(CP_UTF8,NULL,UnicodeStr,-1,MultiByteStr,minsize,NULL,false);
	outfile.write(MultiByteStr,minsize);
	delete[] UnicodeStr;
	delete[] MultiByteStr;
	outfile.close();
	infile.close();
	return 0;
}
