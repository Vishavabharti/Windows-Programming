
/*++
Write a menu driven program for file handling. Menu should contain following entries.
	1.Add
	2.Remove
	3.Update
	4.Display
	5.Exit

File should contain record header & student records.
	a.struct RecordHeader
		  {
	DWORD dwTotalRecords;
		  };

	b.struct StudentRecord
		  {
	DWORD dwRollNumber;
	DWORD dwClass;
	char szName[20];
		  };
		  
Module Name:
			FileHandling.cpp

Abstract:
			This module handles IO operations using linked list.
			1.ADD Record
			2.REMOVE Record
			3.UPDATE Record
			4.DISPLAY Record
			5.EXIT Record
			
--*/


/*************************** H E A D E R S **************************************/

#include"RecordHeader.h"

/********************************************************************************/

void addRecord(StudentRecord **studPtr, DWORD dwRollNumber, DWORD dwClass, char szName[nameSize]);

void removeRecord(StudentRecord **stud_Ptr, DWORD dwRollNumber);

void updateRecord(StudentRecord **studPtr, DWORD dwRollNumber);

void displayRecord(StudentRecord *studPtr);

void saveRecord(StudentRecord *stud_Ptr, char *file_Name);

void freeRecord(StudentRecord **stud_Ptr);

void fileRecord(char *fileName, StudentRecord **studPtr);


/************************** M A I N  F U N C T I O N ***************************/

int main()
{
	DWORD dwRoll;
	DWORD dwClass;
	char szName[nameSize];
	int iOption;
	
	StudentRecord *stud_Ptr;
	stud_Ptr=(StudentRecord*)malloc(sizeof(StudentRecord));
	stud_Ptr->next=NULL;
	
fileRecord("StudentRecord.txt",&stud_Ptr);
	do
	{
		printf("\n Student Record");
		printf("\n1. Add \n2. Remove \n3. Update \n4. Display \n5. Exit \n Enter Option:- ");
		scanf("%d",&iOption);
		switch(iOption)
		{
			case 1:
					printf("\n Enter roll number:- ");
					scanf_s("%d",&dwRoll,sizeof(int));
					printf("\n Enter the class:-  ");
					scanf_s("%d",&dwClass,sizeof(int));
					printf("\n Enter the name :- ");
					scanf_s("%s",szName,nameSize);
					addRecord(&stud_Ptr,dwRoll,dwClass,szName);
					break;
            case 2:
					printf("\n Enter roll number:-");
					scanf_s("%d",&dwRoll,sizeof(int));
					removeRecord(&stud_Ptr,dwRoll);
					break;
			case 3:
					printf("\nEnter roll number:-");
					scanf_s("%d",&dwRoll,sizeof(int));
					updateRecord(&stud_Ptr,dwRoll);
					break;
		    case 4:
					displayRecord(stud_Ptr);
					break;
			case 5:
					saveRecord(stud_Ptr,"StudentRecord.txt");
					exit(0);
			default:
					printf("\n Invalid Option");
		}
	}while(iOption!=6);
	freeRecord(&stud_Ptr);
	stud_Ptr=NULL;
	return 0;
}

/********************************** FILE RECORD *****************************************/

void fileRecord(char *fileName,
			    StudentRecord **studPtr)
{
	StudentRecord *tempPtr=*studPtr;
	FILE *filePtr;
	filePtr = fopen(fileName,"r");
	if (NULL == filePtr)
	{
		printf("\n File not found");
	}
	while(!feof(filePtr))
	{
		tempPtr->next=(StudentRecord*)malloc(sizeof(StudentRecord));
		tempPtr=tempPtr->next;
		tempPtr->next=NULL;
		fscanf(filePtr,"\t%d\t%d\t%s\n",&tempPtr->dwClass,&tempPtr->dwRollNumber,tempPtr->szName);
	}
	fclose(filePtr);
}

/********************************* ADD RECORD ****************************************/

void addRecord(StudentRecord **studPtr,
				DWORD dwRollNumber,
				DWORD dwClass,
				char szName[nameSize])
{	
	StudentRecord *newPtr;
	StudentRecord *tempPtr = *studPtr;
	newPtr = (StudentRecord*)malloc(sizeof(StudentRecord));
	newPtr->next = NULL;
	newPtr->dwRollNumber = dwRollNumber;
	newPtr->dwClass = dwClass;
	strcpy(newPtr->szName,szName);
	if (NULL == tempPtr->next)
	{
		tempPtr->next = newPtr;
	}
	else
	{
		while(NULL != tempPtr->next)
		{
			tempPtr = tempPtr->next;
		}
		tempPtr->next = newPtr;
	}
}

/******************************** REMOVE RECORD *************************************/

void removeRecord(StudentRecord **stud_Ptr,
				  DWORD dwRollNumber)
{
	StudentRecord *temp_Ptr = (*stud_Ptr)->next;
	StudentRecord *temp_Ptr1;

	for (;temp_Ptr!=NULL;)
	{
		if (temp_Ptr->dwRollNumber == dwRollNumber)
		{
			for(temp_Ptr1=*stud_Ptr; temp_Ptr1->next!=temp_Ptr;temp_Ptr1=temp_Ptr1->next);
			temp_Ptr1->next=temp_Ptr->next;
			free(temp_Ptr);
			break;
		}
		temp_Ptr=temp_Ptr->next;
	}
}

/******************************** UPDATE RECORD *************************************/

void updateRecord(StudentRecord **studPtr,
			      DWORD dwRollNumber)
{
	StudentRecord *tempPtr = (*studPtr)->next;
	for (;tempPtr != NULL; tempPtr=tempPtr->next)
	{
		if (dwRollNumber == tempPtr->dwRollNumber )
		{
			printf("\n Enter class and name");
			scanf("%d%s",&tempPtr->dwClass,tempPtr->szName);	
			break;
		}
	}
}

/******************************* DISPLAY RECORD **************************************/

void displayRecord(StudentRecord *studPtr)
{
	studPtr = studPtr->next;
	while (NULL != studPtr)
	{
		printf("\n %d\t %d \t %s ",studPtr->dwRollNumber,studPtr->dwClass,studPtr->szName);
		studPtr = studPtr->next;
	}
}

/********************************* SAVE RECORD ******************************************/ 

void saveRecord(StudentRecord *stud_Ptr,
		        char *file_Name)
{
	FILE *file_Ptr;
	file_Ptr = fopen("StudentRecord.txt","w");
	if (NULL == file_Ptr)
	{
		printf(" Not created");
	}
	stud_Ptr=stud_Ptr->next;
	while (NULL != stud_Ptr )
	{
		fprintf(file_Ptr,"\n\t%d\t\t\t%d\t\t\t%s",stud_Ptr->dwRollNumber,stud_Ptr->dwClass,stud_Ptr->szName);
		stud_Ptr = stud_Ptr->next;
	}
	fclose(file_Ptr);
}

/*********************************** FREE RECORD *****************************************/

void freeRecord(StudentRecord **stud_Ptr)
{
	StudentRecord *temp_Ptr = (*stud_Ptr)->next;
	while(NULL != *stud_Ptr)
	{
		printf("\n %s\t",temp_Ptr->szName);
		(*stud_Ptr)->next = temp_Ptr->next;
		free(temp_Ptr);
		temp_Ptr = (*stud_Ptr)->next;
		if (NULL == temp_Ptr)
		{
			break;
		}
	}
	free(*stud_Ptr);
}
