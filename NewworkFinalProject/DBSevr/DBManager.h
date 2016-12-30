#pragma once
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
	bool DBManager::InsertSecretKey(string id, char key);
	vector<string> Select(string& query);
	DBManager(void);
	//DBManager(CString& str);
	virtual ~DBManager(void);
};

