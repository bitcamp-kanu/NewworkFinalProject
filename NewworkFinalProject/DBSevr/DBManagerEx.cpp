#include "DBManagerEx.h"
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

DBManagerEx::DBManagerEx(void)
{
	m_strConnStr = "DSN=Database;Uid=<username>;Pwd=<password>";
}


DBManagerEx::~DBManagerEx(void)
{
}
DBManagerEx::DBManagerEx(string& connStr)
{
	m_strConnStr = connStr;

}
bool DBManagerEx::Open()
{
	m_podb = new CDatabase();
	if(!m_podb -> OpenEx(m_strConnStr.c_str()))
	{
		throw new exceptionDB("CDatabase Open 실패");
		return false;
	}
	return true;
}
bool DBManagerEx::Open(string& connStr)
{
	m_strConnStr = CString(connStr.c_str());
	return Open();
}

//사용자 아이디를 검증 한다.
bool DBManagerEx::IsUserPasswordEx(string id, string pass)
{
	CString strQuery = "";
	strQuery.Format("SELECT Id , Pass FROM TB_USER WHERE Id = '%s' and Pass = '%s' and Flag = '1' ", id.c_str(), pass.c_str());
	CRecordset rs(m_podb);
	if (!rs.Open(CRecordset::dynaset, strQuery, 0))
	{
		throw new exceptionDB("CRecordset Open 실패");
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

//보안키를 검색 한다.
bool DBManagerEx::IsSecretKeyEx(string id, char key)
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

//보안키를 추가한다.
bool DBManagerEx::InsertSecretKey(string id, char key)
{
	if(InsertSecretKey(id,key))
	{
		_UpdateSecretKey(id,key);
	}
	else
	{
		_InsertSecretKey(id,key);
	}

	return true;
}
bool DBManagerEx::_UpdateSecretKey(string id, char key)
{
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();
	strQuery.Format("update TB_KEY set UDate = '%s' where Id = '%s' AND SKey = '%c' ", UDate.c_str(), id.c_str(),key);
	try
	{
		m_podb->ExecuteSQL(strQuery);

	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		throw exceptionDB(pe->m_strError);		
	}
}
bool DBManagerEx::_InsertSecretKey(string id, char key)
{
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();
	strQuery.Format("insert into TB_KEY (Id, SKey, UDate) values ('%s', '%c', '%s') ", id.c_str(), key, UDate.c_str());
	try
	{
		m_podb->ExecuteSQL(strQuery);

	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		throw exceptionDB(pe->m_strError);		
	}
}



//출석 번호를 생성한다.
int DBManagerEx::SelectStudenClassNum(string classid)
{
	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}
	CString strQuery = "";
	strQuery.Format("SELECT MAX(ClassNum) + 1 FROM TB_STUDENT WHERE ClassId = '%s';", classid.c_str());
	CRecordset rs(m_podb);
	if (!rs.Open(CRecordset::dynaset, strQuery, 0))
	{
		throw new exceptionDB("CRecordset Open 실패");
		return false;
	}
	int rowCnt = 0;
	CString nextClassNum;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		rs.GetFieldValue((short)0,nextClassNum);
		rowCnt++;
		rs.MoveNext();
	}
	//조회값이 NULL 이면 1을 설정 한다.
	if(nextClassNum == "")
	{
		nextClassNum = "1";
	}
	rs.Close();
	return atoi(nextClassNum); 
}

vector<_Tb_Class*> DBManagerEx::SelectClassInfo(string userId)
{
	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}
	vector<_Tb_Class*> vecClass;

	CString strQuery = "";
	strQuery.Append("SELECT ");
	strQuery.Append(	" TB_CLASS.Seq as seq ");
	strQuery.Append(	",ClassId ");
	strQuery.Append(	",ClassName ");
	strQuery.Append(	",UserID ");
	strQuery.Append(	",TB_CLASS.UDate as UDate ");
	strQuery.Append(	",TB_CLASS.Flag	 ");
	strQuery.Append(	",Pass ");
	strQuery.Append(	",UName ");
	strQuery.Append(	",Tell ");
	strQuery.Append("FROM  ");
	strQuery.Append("TB_USER  ");
	strQuery.Append("LEFT JOIN TB_CLASS  ");
	strQuery.Append("ON TB_USER.Id = TB_CLASS.UserID  ");
	strQuery.AppendFormat("WHERE TB_USER.ID = '%s' ",userId.c_str());


	CRecordset rs(m_podb);
	if (!rs.Open(CRecordset::dynaset, strQuery, 0))
	{
		throw new exceptionDB("CRecordset Open 실패");
		return vecClass;
	}	

	CString seq,ClassId,ClassName,UserID,UDate;
	CString Flag,Pass,UName,Tell;
	_Tb_Class* pData = NULL;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{

		rs.GetFieldValue("seq"		,seq);
		rs.GetFieldValue("ClassId"	,ClassId);
		rs.GetFieldValue("ClassName",ClassName);
		rs.GetFieldValue("UserID"	,UserID);
		rs.GetFieldValue("UDate"	,UDate);
		rs.GetFieldValue("Flag	"	,Flag	);
		rs.GetFieldValue("Pass"		,Pass);
		rs.GetFieldValue("UName"	,UName);
		rs.GetFieldValue("Tell"		,Tell);

		rs.MoveNext();
		pData = new _Tb_Class(seq.GetBuffer(),ClassId.GetBuffer(),ClassName.GetBuffer()
							,UserID.GetBuffer(),UDate.GetBuffer(),Flag.GetBuffer()
							,Pass.GetBuffer(),UName.GetBuffer(),Tell.GetBuffer());
		vecClass.push_back(pData);
	}


	return vecClass;

}
//학생 정보를 추가 한다. 반 번호는 내부에서 생성 한다.
bool DBManagerEx::InsertStudentEx(string classID,string sName, string sex,string tel)
{
	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();
	int classNum = SelectStudenClassNum(classID); //반번호를 구한다.
	strQuery.Append(	"INSERT INTO TB_STUDENT ");
	strQuery.Append(		"(ClassNum 	,ClassId	,SName ");		
	strQuery.Append(		",SSex		,STelNo		,C");
	strQuery.Append(		",CPP		,CSharp		,Network");
	strQuery.Append(		",Unity		,Total		,Avg");	
	strQuery.Append(		",UDate		,Flag) ");
	strQuery.Append(	"VALUES	");
	strQuery.AppendFormat("(  %d, '%s','%s' ",classNum,classID.c_str(),sName.c_str());
	strQuery.AppendFormat("	,'%s','%s',0",sex.c_str(),tel.c_str());
	strQuery.Append(	   ",0,0,0");
	strQuery.Append(	   ",0,0,0");
	strQuery.AppendFormat( ",'%s',1)",UDate.c_str());

	try
	{
		m_podb->ExecuteSQL(strQuery);
		
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		throw exceptionDB(pe->m_strError);		
	}
}

//학생 정보를 업데이트 한다. 검색 조건 classID , classNum 을 가지고 학생 정보를 수정 한다.
bool DBManagerEx::UpdateStudentInfoEx(string id, int classNum, string sName, char sSex, string sTel)
{
	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();

	strQuery.Format("update TB_STUDENT set \
					SName = '%s', SSex = '%c', STelNo = '%s', UDate = '%s' \
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
		throw exceptionDB(pe->m_strError);		
		return false;
	}
	return true;
}
//학생 정보를 삭제 한다.
bool DBManagerEx::DeleteStudentEx(int nSeq,string classId, int classNum)
{
	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();

	strQuery.Format("update TB_STUDENT set \
					Flag = '9', UDate = '%s' \
					where ClassId = '%s' and ClassNum = %d and Flag = '1' ",
					UDate.c_str(), classId.c_str(), classNum);

	try
	{
		m_podb->ExecuteSQL(strQuery);
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		throw exceptionDB(pe->m_strError);		
		return false;
	}
	return true;
}
//학생 성적을 업데이트 하나.
bool DBManagerEx::UpdateStudentGrade( int nSeq	,string classId	,int classNum
	,int c		,int cpp		,int csharp
	,int network, int unity)
{
	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}
	CString strQuery = "";
	string UDate = WIUtility::GetCurTime();
	int total = c + cpp + csharp + network + unity;
	float avg = total / 5;

	strQuery.Format("update TB_STUDENT set \
					C = %d, Cpp = %d, Csharp = %d, Network = %d, \
					Unity = %d, Total = %d, Avg = %f, UDate = '%s' \
					where ClassId = '%s' and ClassNum = %d and Flag = '1' ",
					c, cpp, csharp, network, unity, total, avg, UDate.c_str(), classId.c_str(), classNum);

	try
	{
		m_podb->ExecuteSQL(strQuery);
	}
	catch (CDBException* pe)
	{
		pe->ReportError();
		pe->Delete();
		throw exceptionDB(pe->m_strError);		
		return false;
	}
	return true;
}

//학생 정보를 검색 한다.
vector<_Student*> DBManagerEx::SelectStudent(string classID,int classNum,string sNameLike)
{

	if(!m_podb->IsOpen() || m_podb == NULL)
	{
		throw exceptionDB("CDatabase 객체를 초기화 하세요.");
	}

	vector<_Student*> vecStudents;

	CString strQuery = "";
	strQuery.Append("SELECT ");
	strQuery.Append(	" ClassNum	,ClassId	,Seq ");
	strQuery.Append(	",SName,SSex,STelNo ");
	strQuery.Append(	",C,CPP,CSharp ");
	strQuery.Append(	",Network,Unity,Total ");
	strQuery.Append(	",Avg,UDate,Flag ");
	strQuery.Append("FROM TB_STUDENT ");
	strQuery.Append("WHERE 1 = 1 ");
	if(classID.size() > 0)
	{
		strQuery.AppendFormat(" AND ClassId = '%s' ",classID.c_str());
	}
	if(classNum > 0)
	{
		strQuery.AppendFormat(" AND ClassNum = %d ",classNum);
	}
	if(sNameLike.size() > 0)
	{
		strQuery.AppendFormat(" AND SName LIKE '%%%s%%' ",sNameLike.c_str());
	}

	CRecordset rs(m_podb);
	if (!rs.Open(CRecordset::dynaset, strQuery, 0))
	{
		throw new exceptionDB("CRecordset Open 실패");
		return vecStudents;
	}	
	
	CString ClassNum ,ClassId,Seq,SName,SSex,STelNo,C,CPP,CSharp;
	CString Network	,Unity ,Total,Avg,UDate,Flag;
	_Student* pData = NULL;
	while (!rs.IsEOF()) //데이터의 끝까지 읽어라.
	{
		
		rs.GetFieldValue("ClassNum"	,ClassNum	);
		rs.GetFieldValue("ClassId"	,ClassId	);
		rs.GetFieldValue("Seq"		,Seq		);
		rs.GetFieldValue("SName"	,SName		);
		rs.GetFieldValue("SSex"		,SSex		);
		rs.GetFieldValue("STelNo"	,STelNo	);
		rs.GetFieldValue("C"		,C			);
		rs.GetFieldValue("CPP"		,CPP		);
		rs.GetFieldValue("CSharp"	,CSharp	);
		rs.GetFieldValue("Network"	,Network	);
		rs.GetFieldValue("Unity"	,Unity		);
		rs.GetFieldValue("Total"	,Total		);
		rs.GetFieldValue("Avg"		,Avg		);
		rs.GetFieldValue("UDate"	,UDate		);
		rs.GetFieldValue("Flag"		,Flag);
		

		rs.MoveNext();
		pData = new _Student(ClassNum.GetBuffer()	,ClassId.GetBuffer()	,Seq.GetBuffer()
							,SName.GetBuffer()		,SSex.GetBuffer()		,STelNo.GetBuffer()
							,C.GetBuffer()			,CPP.GetBuffer()		,CSharp.GetBuffer()
							,Network.GetBuffer()	,Unity.GetBuffer()		,Total.GetBuffer()
							,Avg.GetBuffer()		,UDate.GetBuffer()		,Flag.GetBuffer());
		vecStudents.push_back(pData);
	}


	return vecStudents;
}