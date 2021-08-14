/*++

Write an application having two threads, one to print odd numbers and another to 
Print even numbers. The numbers should be print sequentially. 
Apply the thread synchronization for it using following kernel objects.

	1.Critical Sections.
	2.Events.
	3.Mutex.
	4.Semaphore.

Module Name:
			CriticalSection.cpp

Abstract:
		This module handles multi-threading of even odd operation using critical section.
		
--*/

#include<stdio.h>
#include<windows.h>

CRITICAL_SECTION CriticalSection;                       // Global Variable
HANDLE hEvenCriticalSection;
HANDLE hOddCriticalSection;

DWORD WINAPI EvenThread(LPVOID p1)
{
    int number = (int)p1;
	 
    while(number <= 10)
	{
        EnterCriticalSection(&CriticalSection);
        printf("Even Thread : %d\n",number);
        number += 2;
        LeaveCriticalSection(&CriticalSection);
    }
    return 0;
}
DWORD WINAPI OddThread(LPVOID p2)
{
    int number = (int) p2;
	
    while(number <= 10)
    {
        EnterCriticalSection(&CriticalSection);
        printf("Odd Thread : %d\n",number);
        number += 2;
        LeaveCriticalSection(&CriticalSection);
    }
    return 0;
}
int main(int argc, CHAR* argv[])
{
    int evenCount = 0;
    int oddCount = 1;
    DWORD dwETID,dwOTID;
	
 InitializeCriticalSection(&CriticalSection);
      
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

	WaitForSingleObject(hOddThread, INFINITE);
	WaitForSingleObject(hEvenThread, INFINITE);

    CloseHandle(hOddThread);
    CloseHandle(hEvenThread);

	CloseHandle(hOddThread);
    CloseHandle(hEvenThread);
	
	
    getchar();
	return 0;
	DeleteCriticalSection(&CriticalSection);

}
