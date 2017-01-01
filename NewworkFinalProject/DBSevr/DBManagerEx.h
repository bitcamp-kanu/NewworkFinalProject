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
	1	class001	������1	ȫ�浿	20161213101010	1
	2	class002	������2	��ȣ��	20161213101011	1
	3	class003	������3	�̼���	20161214101010	1
	*/
	
	/*TB_STUDENT insert , Update , Delete
	//ClassNum	ClassId	Seq	SName	SGender	STelNo	C	CPP	CSharp	Network	Unity	Total	Avg	UDate	Flag
	//1	class001	1	�л�1	1	111-1111-1111	0	0	0	0	0	0	0	20161212101010	1
	//1	class002	4	�л�3	1	222-2222-2222	0	0	0	0	0	0	0	20161213101013	1
	//2	class001	2	�л�2	1	333-3333-3333	0	0	0	0	0	0	0	20161213101012	1
	*/

	/*TB_USER Select
	Id		Seq	Pass		UName	Tell			UDate			Flag
	tempabc	3	test1234	�ź���	010-1113-1312	20161216091919	1
	tempid	2	test1234	���	010-2222-1111	20161215101010	1
	testid	1	test1234	ȫ�浿	010-2222-3333	20161213101010	1
	*/
public:
	DBManagerEx(void);
	~DBManagerEx(void);
	DBManagerEx(string& connStr);
	bool Open();
	bool Open(string& connStr);

	//����� ���̵� ���� �Ѵ�.
	bool IsUserPasswordEx(string id, string pass);	

	//�⼮ ��ȣ�� �����Ѵ�.
	int SelectStudenClassNum(string classid);
	//����Ű�� �߰��Ѵ�.
	
	bool InsertSecretKey(string id, char key);
	bool _UpdateSecretKey(string id, char key);
	bool _InsertSecretKey(string id, char key);
	//����Ű�� �˻� �Ѵ�.
	bool IsSecretKeyEx(string id, char key);


	
	//�л� ������ �߰� �Ѵ�. �� ��ȣ�� ���ο��� ���� �Ѵ�.
	bool InsertStudentEx(string classID,string sName, string sex,string tel);
	
	//�л� ������ ������Ʈ �Ѵ�. �˻� ���� classID , classNum �� ������ �л� ������ ���� �Ѵ�.
	bool UpdateStudentInfoEx(string classID , int classNum, string sName, char sSex, string sTel);
	//�л� ������ ���� �Ѵ�.
	bool DeleteStudentEx(int nSeq,string classId, int classNum);
	//�л� ������ ������Ʈ �ϳ�.
	bool UpdateStudentGrade( int nSeq	,string classId	,int classNum
							,int c		,int cpp		,int csharp
							,int network, int unity);


	//�л� ������ �˻� �Ѵ�.
	vector<_Student*> SelectStudent(string classID,int classNum,string sNameLike);

	
	
};

