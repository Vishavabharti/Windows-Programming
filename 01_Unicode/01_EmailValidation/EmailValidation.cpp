
/*++

Validating email: 
	Write a function that will validate email ID.  The conditions for validation are as:
		Alpha numeric characters are allowed.
		No special character except dot (.), underscore (_) and at rate (@), is allowed.
		Only one (@) symbol is allowed.
		Before @, maximum530 characters are allowed.
		After @, maximum 60 characters are allowed.
		There should not be only dot/underscore before/after @ symbol.
		
Create embedded string, and read it.
	For example, a single buffer can hold multiple string, each string separated by ‘\0’.  
	The last string in buffer is followed by two NULL characters. 
		
Module Name:
			EmailValidation.cpp

Abstract:
			This module handles String operations ex; Email Validation and embedded String.
	
--*/


#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>


int Email_Validation(char email[], int length);
int Embedded_String(int Embedded_String, char Buffer[]);

int main()
{
   int iOption;
   int Length, string, r;
   char String[1000];
  do
	{
		printf("\n1.Email Validation");
		printf("\n2.Embedded String");
		printf("\nEnter option 1/2: ");
		scanf("%d", &iOption);
		switch(iOption)
		{
			case 1 :
					printf("Enter email : ");
					fflush(stdin);
					gets(String);
					Length=strlen(String);
					r= Email_Validation(String,Length);
					if(1 == r)
					{
						printf(" Valid");
					}
					else
					{
						printf(" Invalid");
					}
					break;
			case 2 :
					printf("Enter number of string to store in buffer: ");
					scanf("%d",&string);
					fflush(stdin);
					r = Embedded_String(string, String);
					if(1 == r)
					{
						printf("\nStrings are embedded");
					}
					else
					{
						printf("Strings are Not embedded");
					}
					break;
		}
	}while(printf("\nEnter option 1/2"));
	getch();
	return 0;
}

int Email_Validation(char email[],int length)
{
	int i, a, d, flag=0;
	int countB=0, count=0, countA=0,countAfterD=0;

	for (i = 0; i < length-1; i++)
	{
		if(!('_' == email[i]   ||
			 '.' == email[i]   || 
			 '@' == email[i]   || 
			 isalpha(email[i]) || 
			 isdigit(email[i])))
		{
			flag=1;
			break;
		}
		if(email[i]=='@')
		{
			a = i;
			count++;
			if('_' == email[i-1]  || 
				'.' == email[i-1] || 
				'_' == email[i+1] || 
				'.' == email[i+1])
			{
				flag = 1;
				break;
			}
			countA = length-i-1;
		}
		if(count==0)
		{
		   countB++;
		}
	}	
	for (i = a; i < countA-1; i++)
	{
		if('.' == email[i])
		{
	       countAfterD++;
		   d = i;	
		}
	}
	if( 530 < countB || 
		 1 != count  || 
		 60 < countA || 
		 1 == flag   || 
		 0 < countAfterD)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}	

int Embedded_String(int Embedded_String,char Buffer[])
	{
	  char str[100];
	  int i, k, iLength, icount=0;

	  for(i = 0;i < Embedded_String; i++)
		{
			printf("\nEnter string[%d] :",i+1);
			gets(str);
			iLength = strlen(str);
			printf("Length : %d ", iLength);
			int j=0;
			while('\0' != str[j])
			{
				Buffer[icount] = str[j];
				icount++;
				j++;
			}
			Buffer[icount] = '\0';
			icount++;
			printf("\nCount : %d ", icount);
		}
	  for(k = 0; k < icount; k++)
		{
			if('\0' == Buffer[k] && k != icount-1)
			{
				printf(" ");
			}
			else if('\0' != Buffer[k])
			{
				if(0 == k)
				{
					printf("\n");
				}
				printf("%c",Buffer[k]);
	        }
		}
	   return 1;
	}
	