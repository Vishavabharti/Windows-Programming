/*++
Create a function that
	takes input following string
		abaccfafaeaabfbbbbfcf
	output should be
		aaaaaabbbbbbcccefffff
		
Module Name:
		StirngConversion.cpp

Abstract:
		This module handles string conversion.

--*/

#include<stdio.h>
#include<conio.h>
#include<string.h>


int main ()
{
 char szString[100],szTemp;
 int n,i,j;
 printf("Enter string: ");
 scanf("%s",&szString);
 n=strlen(szString);
 for(i=0; i<n-1; i++)
   {
     for(j=i+1; j<n; j++)
      {
         if(szString[i] > szString[j])
           {
             szTemp = szString[i];
             szString[i] = szString[j];
             szString[j] = szTemp;
           }
      }
   }
  printf("output:-%s\n", szString);
  getch();
  return 0;
}
