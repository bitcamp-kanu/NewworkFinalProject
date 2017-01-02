//#include <windows.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "DBManager.h"
#include <afxwin.h>
#include "..\Public\WIUtility.h"
#include "DBManagerEx.h"
using namespace std;

int main()
{

	DBManagerEx oDBEx;
	oDBEx.Open();

	//oDBEx.InsertStudentEx(string(),string(),string());


	//int nIdex = oDBEx.SelectStudenClassNum("class001");
	//MessageBox(NULL,WIUtility::GetFormatString("%d",nIdex).c_str(),"",0);
	
	try
	{
		/*oDBEx.InsertStudentEx("001","강백호","1","111-1111-1111");
		oDBEx.InsertStudentEx("001","서태웅","2","222-2222-2222");
		oDBEx.InsertStudentEx("001","송태섭","3","333-3333-3333");*/


		//oDBEx.UpdateStudentInfoEx("001",1,"강백호2",'1',"555-5555-5555");

		//vector<_Student*> vec = oDBEx.SelectStudent("",0,"학생");
		//
		//for(int i = 0; i <vec.size() ; i++ )
		//{
		//	cout << vec[i]->SName << endl;
		//}
		//} 
		vector<_Tb_Class*> vec = oDBEx.SelectClassInfo("testid");

		for(int i = 0; i <vec.size() ; i++ )
		{
			cout << vec[i]->ClassName << endl;
		}

	}
	catch (exceptionDB e)
	{
		MessageBox(NULL,e.what(),"",0);
	}
	
	




	//DBManager oDb;
	//oDb.Open();
	//CString str;

	//oDb.updateStudentInfo();
	////oDb.Select((CString)"SELECT * FROM TB_CLASS");

	//char buff[255];

	//AfxMessageBox(WIUtility::GetErrorMessage(1).c_str());

	//cout << "test1234" << endl;
	//cin.getline(buff,sizeof(buff));
	//if(oDb.IsUserPassword("tempabc" ,buff))
	//{
	//	::AfxMessageBox("로그인 성공");
	//}
	//else
	//{
	//	::AfxMessageBox("로그인 실패");
	//}
	//Id	Seq	Pass	UName	Tell	UDate	Flag
	//	tempabc	3	test1234	거북이	010-1113-1312	20161216091919	1
	//	tempid	2	test1234	기라성	010-2222-1111	20161215101010	1
	//	testid	1	test1234	홍길동	010-2222-3333	20161213101010	1

	system("pause");
}

