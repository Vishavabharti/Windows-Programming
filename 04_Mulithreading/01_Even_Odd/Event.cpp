/*++

Module Name:
			Event.cpp

Abstract:
		This module handles multi-threading of even odd operation using event.
	
--*/

#include<stdio.h>
#include<windows.h>

HANDLE hEvenEvent;
HANDLE hOddEvent;

DWORD WINAPI EvenThread(LPVOID p1)
{
    int number = (int)p1;
    while(number <= 10)
    {
        WaitForSingleObject(hOddEvent,INFINITE);
        printf("Even Thread : %d\n",number);
        number += 2;
        SetEvent(hEvenEvent);
    }
    return 0;
}
DWORD WINAPI OddThread(LPVOID p2)
{
    int number = (int) p2;
    while(number <= 10)
    {
        WaitForSingleObject(hEvenEvent,INFINITE);
        printf("Odd Thread : %d\n",number);
        number += 2;
        SetEvent(hOddEvent);
    }
    return 0;
}
int main(int argc, CHAR* argv[])
{
    int evenCount = 0;
    int oddCount = 1;
    DWORD dwETID,dwOTID;
    hEvenEvent = CreateEvent(
		NULL,                           // default security attributes
		FALSE,                          // manual reset event
		FALSE,                          // initial state is non-signaled
		TEXT("EvenEvent"));             // object name
    hOddEvent = CreateEvent(
		NULL,                           // default security attributes
		FALSE,                          // manual reset event
		TRUE,                           // initial state is signaled
		TEXT("OddEvent"));              // object name
    
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
