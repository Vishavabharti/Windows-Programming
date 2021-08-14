/*++

Module Name:
			Semaphore.cpp

Abstract:
		This module handles multi-threading of even odd operation using semaphore
	
--*/

#include<stdio.h>
#include<windows.h>

#define MAX_SEM_COUNT 10

HANDLE hEvenSemaphore;
HANDLE hOddSemaphore;

DWORD WINAPI EvenThread(LPVOID p1)
{
    int number = (int)p1;
	 
    while(number <= 10)
    {
        WaitForSingleObject(hOddSemaphore,0L);
        printf("Even Thread : %d\n",number);
        number += 2;
        ReleaseSemaphore(hEvenSemaphore,0,NULL);
		hEvenSemaphore = CreateSemaphore(
		NULL,                           // default security attributes
		MAX_SEM_COUNT,                  // initial count
        MAX_SEM_COUNT,                  // maximum count
		TEXT("EvenSemaphore"));         // object name
    }
    return 0;
}
DWORD WINAPI OddThread(LPVOID p2)
{
    int number = (int) p2;
	
    while(number <= 10)
    {
        WaitForSingleObject(hEvenSemaphore,0L);
        printf("Odd Thread : %d\n",number);
        number += 2;
        ReleaseSemaphore(hOddSemaphore,0,NULL);
		hOddSemaphore = CreateSemaphore(
		NULL,                           // default security attributes
		MAX_SEM_COUNT,                  // initial count
        MAX_SEM_COUNT,                  // maximum count
		TEXT("OddEvent"));              // object name

    }
    return 0;
}
int main(int argc, CHAR* argv[])
{
    int evenCount = 0;
    int oddCount = 1;
    DWORD dwETID,dwOTID;
    
    HANDLE hEvenThread = CreateThread(
		NULL,                           // default security attributes
		0,                              // default stack size
		EvenThread,                     // thread function name
		(LPVOID)evenCount,              // thread parameters
		0,                              // default startup flags
		&dwETID);    
    HANDLE hOddThread = CreateThread(
		NULL,                           // default security parameters
		NULL,                           // stack size
		OddThread,                      // thread function name
		(LPVOID)oddCount,               // thread parameters
		NULL,                           // startup flags
		&dwOTID);

    CloseHandle(hOddThread);
    CloseHandle(hEvenThread);
    getchar();
    return 0;
}
