#pragma once
#include <stdio.h>
////#include <windows.h>
//#include <afxwin.h> 
//#include <afxdb.h> //ODBC
//#include <cstring>
#include <string>
#include <vector>
#include "../Public/DefineSchema.h"
using namespace std;

class CDatabase;
class DBManagerEx
{
private:
	CDatabase* m_podb;	
	string	   m_strConnStr;
	/*TB_KEY 
	Seq	Id	SKey	UDate	Flag
	1	bitcamp001	a	20161221101010	1
	2	bitcamp002	b	20161221101011	1
	3	bitcamp003	c	20161221101012	1
	*/ 
	/* TB_CLASS
	Seq	ClassId	ClassName	TName	UDate	Flag
	1	class001	윈도우1	홍길동	20161213101010	1
	2	class002	윈도우2	수호자	20161213101011	1
	3	class003	윈도우3	이순신	20161214101010	1
	*/
	
	/*TB_STUDENT insert , Update , Delete
	//ClassNum	ClassId	Seq	SName	SGender	STelNo	C	CPP	CSharp	Network	Unity	Total	Avg	UDate	Flag
	//1	class001	1	학생1	1	111-1111-1111	0	0	0	0	0	0	0	20161212101010	1
	//1	class002	4	학생3	1	222-2222-2222	0	0	0	0	0	0	0	20161213101013	1
	//2	class001	2	학생2	1	333-3333-3333	0	0	0	0	0	0	0	20161213101012	1
	*/

	/*TB_USER Select
	Id		Seq	Pass		UName	Tell			UDate			Flag
	tempabc	3	test1234	거북이	010-1113-1312	20161216091919	1
	tempid	2	test1234	기라성	010-2222-1111	20161215101010	1
	testid	1	test1234	홍길동	010-2222-3333	20161213101010	1
	*/
public:
	DBManagerEx(void);
	~DBManagerEx(void);
	DBManagerEx(string& connStr);
	bool Open();
	bool Open(string& connStr);

	//사용자 아이디를 검증 한다.
	bool IsUserPasswordEx(string id, string pass);	

	//출석 번호를 생성한다.
	int SelectStudenClassNum(string classid);
	//보안키를 추가한다.
	
	bool InsertSecretKey(string id, char key);
	bool _UpdateSecretKey(string id, char key);
	bool _InsertSecretKey(string id, char key);
	//보안키를 검색 한다.
	bool IsSecretKeyEx(string id, char key);


	
	//학생 정보를 추가 한다. 반 번호는 내부에서 생성 한다.
	bool InsertStudentEx(string classID,string sName, string sex,string tel);
	
	//학생 정보를 업데이트 한다. 검색 조건 classID , classNum 을 가지고 학생 정보를 수정 한다.
	bool UpdateStudentInfoEx(string classID , int classNum, string sName, char sSex, string sTel);
	//학생 정보를 삭제 한다.
	bool DeleteStudentEx(int nSeq,string classId, int classNum);
	//학생 성적을 업데이트 하나.
	bool UpdateStudentGrade( int nSeq	,string classId	,int classNum
							,int c		,int cpp		,int csharp
							,int network, int unity);


	//학생 정보를 검색 한다.
	vector<_Student*> SelectStudent(string classID,int classNum,string sNameLike);

	
	
};

