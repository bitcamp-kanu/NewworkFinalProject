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
}

bool DBManager::IsSecretKey(string id, char key)
{
	/*Seq	Id	SKey	UDate
	1	testid	a	20161221101010
	2	bitcamp002	b	20161221101011
	3	bitcamp003	c	20161221101012*/
	
	CString strQuery = "";
	strQuery.Format("SELECT Id FROM TB_KEY WHERE Id = '%s' and SKey = '%c' ", id.c_str(), key);
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
		strQuery.Format("insert into TB_KEY (Id, SKey, UDate) values ('%s', '%c', '%s') ", id.c_str(), key, UDate.c_str());
	else
		strQuery.Format("update TB_KEY set SKey = '%c', UDate = '%s' where Id = '%s' ", key, UDate.c_str(), id.c_str());

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

//3. UserId 받으면 ClassId, ClassName, UName 반환해주는 함수 - 패킷 US
string DBManager::SelectStudent(string id)
{
	CString strQuery = "";

	strQuery.Format("SELECT Id, UName, ClassId, ClassName FROM TB_USER LEFT JOIN TB_CLASS ON TB_USER.Id = TB_CLASS.ClassId WHERE ID = '%s'", id.c_str());
	CRecordset rs(m_podb);

	try
	{
		if (!rs.Open(CRecordset::dynaset, strQuery, 0))
		{
			AfxMessageBox("TB_USER 고유아이디 확인 실패");
		}
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		AfxMessageBox(pe->m_strError);
	}
	
	CString Id, UName, ClassId, ClassName, temp;
	string result;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		rs.GetFieldValue("Id", Id);
		rs.GetFieldValue("UName", UName);
		rs.GetFieldValue("ClassId", ClassId);
		rs.GetFieldValue("ClassName", ClassName);
		rs.MoveNext();
	}

	temp = Id + ";" + UName + ";" + ClassId + ";" + ClassName;	
	result = temp.GetBuffer();
	return result;
}

//4. 학생 정보 가져오기 - 조건 - classid, classnum, sname(like)
//로그인 id와 tb_student의 classid가 동일
string* DBManager::SelectStudentInfo(string id, string sname)
{
	CString strQuery = "";

	//???
	//strQuery.Format("SELECT ClassNum, SName, SSex, STel FROM TB_STUDENT \
	//					WHERE ID = '%s' AND SName like '\%%s\%'", id.c_str(), sname.c_str());

	//??? 원래는 쿼리에서 공통된 부분은 같이 쓰고 sname에 값 유무에 따라 where절에 if를 걸지만 표기방법을 모르겠음.
	if(sname == "")
		strQuery.Format("SELECT ClassNum, SName, SSex, STel FROM TB_STUDENT \
						WHERE ClassId = '%s' AND Flag = '1'", id.c_str());
	else
		strQuery.Format("SELECT ClassNum, SName, SSex, STel FROM TB_STUDENT \
						WHERE ClassId = '%s' AND SName like '%s' AND Flag = '1'", id.c_str(), sname.c_str());

	CRecordset rs(m_podb);

	try
	{
		if (!rs.Open(CRecordset::dynaset, strQuery, 0))
		{
			AfxMessageBox("TB_USER 고유아이디 확인 실패");
		}
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		AfxMessageBox(pe->m_strError);
	}

	int rowCnt = 0;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		//rs.GetFieldValue("Id", Id);
		rowCnt++;
		rs.MoveNext();
	}

	rs.MoveFirst();

	CString ClassNum, SName, SSex, STel, temp;
	int row = rowCnt;
	rowCnt = 0;

	string* result = (string*)malloc(sizeof(string)*row);
	for(int i=0; i<row; i++)
	{
		rs.GetFieldValue("ClassNum", ClassNum);
		rs.GetFieldValue("SName", SName);
		rs.GetFieldValue("SSex", SSex);
		rs.GetFieldValue("STel", STel);
		temp = ClassNum + ";" + SName + ";" + SSex + ";" + STel;
		*(result + i) = temp.GetBuffer();			//??? Error
		rowCnt++;
		rs.MoveNext();
	}

	return result;
}

bool DBManager::updateStudentInfo(string id, int classNum, string sName, char sSex, string sTel)
{
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();

	strQuery.Format("update TB_STUDENT set \
			SName = '%s', SSex = '%c', STel = '%s', UDate = '%s' \
			where ClassId = '%s' and ClassNum = %d and Flag = '1' ",
			sName.c_str(), sSex, sTel.c_str(), UDate.c_str(), id.c_str(), classNum);

	try
	{
		m_podb->ExecuteSQL(strQuery);
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		AfxMessageBox(pe->m_strError);
		return false;
	}
	return true;
}

bool DBManager::deleteStudent(string id, int classNum)
{
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();

	strQuery.Format("update TB_STUDENT set \
			Flag = '9', UDate = '%s' \
			where ClassId = '%s' and ClassNum = %d and Flag = '1' ",
			UDate.c_str(), id.c_str(), classNum);

	try
	{
		m_podb->ExecuteSQL(strQuery);
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		AfxMessageBox(pe->m_strError);
		return false;
	}
	return true;
}

bool DBManager::updateStudentGrade(string id, int classNum, int c, int cpp, int csharp, int network, int unity)
{
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();
	int total = c + cpp + csharp + network + unity;
	float avg = total / 5;

	strQuery.Format("update TB_STUDENT set \
			C = %d, Cpp = %d, Csharp = %d, Network = %d, \
			Unity = %d, Total = %d, Avg = %f, UDate = '%s' \
			where ClassId = '%s' and ClassNum = %d and Flag = '1' ",
			c, cpp, csharp, network, unity, total, avg, UDate.c_str(), id.c_str(), classNum);

	try
	{
		m_podb->ExecuteSQL(strQuery);
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		AfxMessageBox(pe->m_strError);
		return false;
	}
	return true;
}