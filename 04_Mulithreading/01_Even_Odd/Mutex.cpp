/*++

Module Name:
			Mutex.cpp

Abstract:
		This module handles multi-threading of even odd operation using mutex.

--*/

#include<stdio.h>
#include<windows.h>

HANDLE hEvenMutex;
HANDLE hOddMutex;

DWORD WINAPI EvenThread(LPVOID p1)
{
    int number = (int)p1;
	 hEvenMutex = CreateMutex(
		NULL,                           // default security attributes
		FALSE,                          // initially not owned
		TEXT("EvenMutex"));             // object name
    while(number <= 10)
    {
        WaitForSingleObject(hOddMutex,INFINITE);
        printf("Even Thread : %d\n",number);
        number += 2;
        ReleaseMutex(hEvenMutex);
    }
    return 0;
}
DWORD WINAPI OddThread(LPVOID p2)
{
    int number = (int) p2;
	 hOddMutex = CreateMutex(
		NULL,                           // default security attributes
		FALSE,                          // initially not owned
		TEXT("OddMutex"));              // object name
    while(number <= 10)
    {
        WaitForSingleObject(hEvenMutex,INFINITE);
        printf("Odd Thread : %d\n",number);
        number += 2;
        ReleaseMutex(hOddMutex);
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
		&dwETID);                       // receive thread identifier
    HANDLE hOddThread = CreateThread(
		NULL,                           // default security parameters
		NULL,                           // stack size
		OddThread,                      // thread function name
		(LPVOID)oddCount,               // thread parameters
		NULL,                           // startup flags
		&dwOTID);                       // receive thread identifier

    CloseHandle(hOddThread);
    CloseHandle(hEvenThread);
    getchar();
    return 0;
}
