#include "DBManager.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <afxwin.h>
#include <afxdb.h> //ODBC
#include <afxwin.h> 
//#include <afx.h>
//#include <windows.h>
#include <iostream>
#include <vector>


#include "..\Public\WIUtility.h"


using namespace std;


DBManager::DBManager(void)
{
	//m_strConnect = "DSN=bitcamp;Uid=<username>;Pwd=<password>";
}
//DBManager::DBManager(CString& str)
//{
//	//m_strConnect = str;
//}
DBManager::~DBManager(void)
{
	if(m_podb != NULL)
	{
		m_podb->Close();
		delete m_podb;
		m_podb = NULL;
	}
	
}

bool DBManager::Open()
{
	m_podb = new CDatabase();
	return m_podb -> OpenEx("DSN=Database;Uid=<username>;Pwd=<password>");
	//return m_podb -> OpenEx("DSN=bitcamp;Uid=<username>;Pwd=<password>");
}

vector<string> DBManager::Select(string& query)
{
	vector<string> rgVector;
	CRecordset rs(m_podb);
	
	CString str(query.c_str());
	if(!rs.Open(CRecordset::dynaset,str,0))		
	{
		AfxMessageBox("오픈실패");
	}
	//조회된 데이터에 컬럽 숫자를 반환 한다. ;
	int nColCnt = rs.m_nResultCols;

	while(!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		CString str;
		CString newStr;
		CString strValue;
		for(int i = 0 ; i < nColCnt ; i++)
		{
			rs.GetFieldValue(i,strValue);
			newStr.Format("%-20s,",strValue);
			str += newStr;
		}
		//rgVector.push_back(str);
		rs.MoveNext();
	}	
	rs.Close();
	return rgVector;
}


bool DBManager::IsUserPassword(string id, string pass)
{

	/*Id	Seq	Pass	UName	Tell	UDate	Flag
	tempabc	3	test1234	거북이	010-1113-1312	20161216091919	1
	tempid	2	test1234	기라성	010-2222-1111	20161215101010	1
	testid	1	test1234	홍길동	010-2222-3333	20161213101010	1
	*/
	CString strQuery = "";
	strQuery.Format("SELECT Id , Pass FROM TB_USER WHERE Id = '%s' and Pass = '%s' and Flag = '1' ", id.c_str(), pass.c_str());
	CRecordset rs(m_podb);
	if (!rs.Open(CRecordset::dynaset, strQuery, 0))
	{
		AfxMessageBox("오픈실패");
		return false;
	}
	int rowCnt = 0;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		rowCnt++;
		rs.MoveNext();
	}
	rs.Close();
	return (rowCnt == 1) ? true : false;
	return true;

}


bool DBManager::InsertSecretKey(string id, char key)
{
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();

	strQuery.Format("SELECT Id FROM TB_KEY WHERE Id = '%s' ", id.c_str());
	CRecordset rs(m_podb);

	if (!rs.Open(CRecordset::dynaset, strQuery, 0))
	{
		AfxMessageBox("TB_USER 고유아이디 확인 실패");
		return false;
	}
	int rowCnt = 0;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		rowCnt++;
		rs.MoveNext();
	}
	rs.Close();

	if (rowCnt == 0)
		strQuery.Format("insert into TB_KEY (Id, SKey, UDate) values ('%s', '%c', '%s') ", id.c_str(), key, UDate);
	else
		strQuery.Format("update TB_KEY set SKey = '%c', UDate = '%s' where Id = '%s' ", key, UDate, id.c_str());


	try
	{
		m_podb->ExecuteSQL(strQuery);
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		AfxMessageBox(pe->m_strError);
	}
	return true;
}