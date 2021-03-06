﻿#pragma once
#include <stdio.h>
////#include <windows.h>
//#include <afxwin.h> 
//#include <afxdb.h> //ODBC
//#include <cstring>
#include <string>
#include <vector>
using namespace std;

class CDatabase;
class DBManager
{
private:
	CDatabase* m_podb;	
public:

	bool Open();
	//로그인을 검사 한다.
	bool IsUserPassword(string id, string pass);
	bool IsSecretKey(string id, char key);
	bool InsertSecretKey(string id, char key);
	string SelectStudent(string id);
	vector<string> Select(string& query);
	string* SelectStudentInfo(string id, string sname);
	bool updateStudentInfo(string id, int classNum, string sName
						 , char sSex, string sTel);
	bool deleteStudent(string id, int classNum);
	bool updateStudentGrade(string id, int classNum, int c, int cpp, int csharp, int network, int unity);
	DBManager(void);
	//DBManager(CString& str);
	virtual ~DBManager(void);
};

