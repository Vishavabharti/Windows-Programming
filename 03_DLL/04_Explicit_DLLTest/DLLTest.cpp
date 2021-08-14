#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "math.h"
 
typedef int (*MYPROC)(int,int);

int main()
{
     
       HINSTANCE hDLL = LoadLibrary(L"ExplicitDLL.dll");
		
	   MYPROC ProcAddress;

	   int returnValue,a=4,b=1;

       if (hDLL == NULL)  
        {
           printf("Failed to load the library.\n");
        }
		
		ProcAddress = (MYPROC)GetProcAddress(hDLL, "Add"); 

		returnValue = ProcAddress(a, b); 
		printf("%d",returnValue);


		FreeLibrary(hDLL);
		getch();
		return 0;
     
}
