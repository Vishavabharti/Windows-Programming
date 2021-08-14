/*++

Thread Synchronization: Write an application to solve the reader writer problem

Module Name:
			Reader_Writer.cpp

Abstract:
		This module handles multi-threading of reader writer mode.

--*/

#include <windows.h>
#include <stdio.h>

HANDLE hMutex;
HANDLE hWriteDone;
HANDLE hReadDone;

int num, state;

int Writer()
{
  for(int x=10; x>=0; x--)
   {
     while (true)
      {
       if (WaitForSingleObject(hMutex, INFINITE) == WAIT_FAILED)
         {
          printf("In writing mode, no mutex!\n");
          ExitThread(0);
         }
      if (state == 0)
         {
          ReleaseMutex(hMutex);
          WaitForSingleObject(hReadDone, INFINITE);
          continue;
         }
      break;
     }
    printf("Write done\n");
    num= x;
    state= 0;
    ReleaseMutex(hMutex);
  }
}

int Reader()
 {
  while(true)
   {
    if (WaitForSingleObject(hMutex, INFINITE) == WAIT_FAILED)
     {
      printf("In reading mode, no mutex!\n");
      ExitThread(0);
     }
    if (state == 1)
     {
      ReleaseMutex(hMutex);
      WaitForSingleObject(hWriteDone, INFINITE);
      continue;
     }
    if (num == 0)
     {
      printf("End of data\n");
      ReleaseMutex(hMutex);
      ExitThread(0);
     }
    else 
	{
      printf("Read done\n");
      state=1;
      ReleaseMutex(hMutex);
    }
  }
}

int main()
{
HANDLE TName[2];
DWORD ThreadID;
state= 1;
hMutex= CreateMutex(
	           NULL,                            // default security attributes
			   FALSE,                           // initially not owned
		       NULL);                           // without object name

hWriteDone= CreateEvent(
	           NULL,                            // default security attributes
			   TRUE,                            // manual reset event
		       FALSE,                           // initial state is non-signled
	           NULL );                          // without object name

hReadDone= CreateEvent(
	          NULL,                             // default security attributes
	          TRUE,                             // manual reset event
	          FALSE,                            // initial state is non-signled
	          NULL);                            // without object name

TName[0]= CreateThread(
	          NULL,                              // default security attributes
	          0,                                 // default stack size
              (LPTHREAD_START_ROUTINE)Writer,    // thread start address
              NULL,                              // thread parameter
              0,                                 // default startup flags
              &ThreadID);                        // receive thread identifier

TName[1]= CreateThread(
	          NULL,                              // default security attributes
	          0,                                 // default stack size
              (LPTHREAD_START_ROUTINE)Reader,    // thread start address
              NULL,                              // thread parameter
              0,                                 // default startup flags
              &ThreadID);                        // receive thread identifier
	          

WaitForMultipleObjects(2, TName, TRUE, INFINITE);
CloseHandle(TName);
return 0;
}
