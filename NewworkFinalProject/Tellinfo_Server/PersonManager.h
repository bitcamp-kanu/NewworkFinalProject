#pragma once

#include <istream>
#include <vector>
#include <string>
#include <list>
#include "..\header\Protocol.h"
using namespace std;

#define _BUFFER_SIZE_ 2048

class Person
{
public:
	char m_szName[NAME_LEN];
	char m_szPhone[TEL_LEN];
	Person(char* name, char* phone)
	{
		strcpy(m_szName,name);
		strcpy(m_szPhone,phone);
	};
	Person(string name, string phone)
	{
		strcpy(m_szName,name.c_str());
		strcpy(m_szPhone,phone.c_str());
	};
	Person(const Person& item)
	{
		strcpy(m_szName,item.m_szName);
		strcpy(m_szPhone,item.m_szPhone);
	};
	Person()
	{
		memset(m_szName,0x00,sizeof(m_szName));
		memset(m_szPhone,0x00,sizeof(m_szPhone));
	}
	~Person()
	{

	}
	string ToString()
	{
		char buffer[1024] = {0};
		sprintf(buffer,"이름: %-20s ,전화번호: %s" ,m_szName, m_szPhone);
		return string(buffer);
	}
};

class PersonManager
{	
	int m_choice;//=0;
	list<Person> m_rgList;
public:	
	void InsertTelInfo(Person& person);
	vector<Person> DeleteTelInfo(string& name);
	vector<Person> SearchTelInfo(string& name);
	vector<Person> GetAllData();

	PersonManager(void);
	~PersonManager(void);
};

