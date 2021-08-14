/*++

Module Name:
			RecordHeaders.h

Abstract:
			This module handles IO operations using linked list.

--*/

/******************************* H E A D E R S **********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

/****************************** G L O B L E S ***********************************/

#define nameSize 20

/***************************** S T R U C T U R E ******************************/
struct StudentRecord
{
	DWORD dwClass;
	DWORD dwRollNumber;
	char szName[nameSize];
	struct StudentRecord *next;
};

