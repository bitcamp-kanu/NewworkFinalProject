
#include <stdio.h>
#include <string.h>

#define NAME_LEN		20
#define TEL_LEN			20
#define MAX_PERSON_NUM	100

typedef struct _Person
{
	char name[NAME_LEN];
	char phone[TEL_LEN];
} Person;

void ShowMenu();
void InsertTelInfo(Person* parr, int* pnum);
void PrintAll(Person* parr, int num);
void DeleteTelInfo(Person* parr, int* pnum);
void SearchTelInfo(Person* parr, int num);

void main()
{
	int choice=0;
	Person perArr[MAX_PERSON_NUM];
	int createPerNum=0;
	int perNum=0;

	while(1)
	{
		ShowMenu();
		printf("Choose the item : ");
		scanf("%d", &choice);

		switch(choice)
		{
		case 1:
			InsertTelInfo(perArr, &perNum);
			break;
		case 2:
			DeleteTelInfo(perArr, &perNum);
			break;
		case 3:
			SearchTelInfo(perArr, perNum);
			break;
		case 4:
			PrintAll(perArr, perNum);
			break;
		case 5:
			free(perArr);
			return;
			break;
		default:
			printf("illegal selection...\n");
			break;
		}
	}
}

void ShowMenu()
{
	printf("\n--------- Menu ---------\n");
	printf("	1. Insert \n");
	printf("	2. Delete \n");
	printf("	3. Search \n");
	printf("	4. Print All \n");
	printf("	5. Exit \n");
}

void InsertTelInfo(Person* parr, int* pnum)
{
	char name[NAME_LEN];
	char phone[TEL_LEN];

	printf("[ INSERT ]\n");
	printf("Input Name : ");		scanf("%s", name);
	printf("Input Tel Number : ");	scanf("%s", phone);

	strcpy(parr[*pnum].name, name);
	strcpy(parr[*pnum].phone, phone);
	(*pnum)++;

	printf("-----------> Data Inserted..........\n");
}

void DeleteTelInfo(Person* parr, int* pnum)
{
	int i=0, j=0;
	char name[NAME_LEN];
	printf("[ Delete ]\n");
	printf("Input Name for Removing : "); scanf("%s", name);
	for(i=0;i<*pnum;i++)
	{
		if(strcmp(parr[i].name, name)==0)
		{
			for(j=i+1;j<*pnum;j++)
			{
				strcpy(parr[j-1].name, parr[j].name);
				strcpy(parr[j-1].phone, parr[j].phone);
			}
			(*pnum)--;
			return;
		}
	}

	printf("-------------> Data Not Found............\n");
}

void SearchTelInfo(Person* parr, int num)
{
	int i=0;
	char name[NAME_LEN];

	printf("[ Search ]\n");
	printf("Input Name for Searching : "); scanf("%s", name);

	for(i=0;i<num;i++)
	{
		if(strcmp(parr[i].name, name)==0)
		{
			printf("-----> Name : %s / Tel : %s \n", 
				parr[i].name, parr[i].phone);
			return;
		}
	}

	printf("------------> Data Not Found.............\n");
}

void PrintAll(Person* parr, int num)
{
	int i;
	printf("[ Print All Data ]\n");
	for(i=0;i<num;i++)
		printf("Name : %s / Tel : %s \n", parr[i].name, parr[i].phone);
}