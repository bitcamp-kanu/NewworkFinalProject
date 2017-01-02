#pragma once
//#include <afxwin.h> 
#include "PublicDefine.h"


class exceptionDB : public std::exception
{
public:
	exceptionDB(const char* message):exception(message)
	{

	}
	exceptionDB(const string message):exception(message.c_str())
	{

	}
};
//학생 정보를 저장할 구조체.
struct _Student
{	
	//문제가 생기면 string 로 변환 해서사용.
	string ClassNum;
	string ClassId;
	string Seq;
	string SName;
	string SSex;
	string STelNo;
	string C;
	string CPP;
	string CSharp;
	string Network;
	string Unity;
	string Total;
	string Avg;
	string UDate;
	string Flag;
	_Student()
	{

	}
	_Student(char* ClassNum		,char* ClassId		,char* Seq
			,char* SName		,char* SSex			,char* STelNo
			,char* C			,char* CPP			,char* CSharp
			,char* Network		,char* Unity		,char* Total
			,char* Avg			,char* UDate		,char* Flag)
	{
		this->ClassNum	= string(ClassNum);
		this->ClassId	= string(ClassId);
		this->Seq		= string(Seq);
		this->SName		= string(SName);
		this->SSex		= string(SSex);
		this->STelNo	= string(STelNo);
		this->C			= string(C);
		this->CPP		= string(CPP);
		this->CSharp	= string(CSharp);
		this->Network	= string(Network);
		this->Unity		= string(Unity);
		this->Total		= string(Total);
		this->Avg		= string(Avg);
		this->UDate		= string(UDate);
		this->Flag		= string(Flag);
	}
	void SetData(char* ClassNum		,char* ClassId		,char* Seq
		,char* SName		,char* SSex			,char* STelNo
		,char* C			,char* CPP			,char* CSharp
		,char* Network		,char* Unity		,char* Total
		,char* Avg			,char* UDate		,char* Flag)
	{
		this->ClassNum	= string(ClassNum);
		this->ClassId	= string(ClassId);
		this->Seq		= string(Seq);
		this->SName		= string(SName);
		this->SSex		= string(SSex);
		this->STelNo	= string(STelNo);
		this->C			= string(C);
		this->CPP		= string(CPP);
		this->CSharp	= string(CSharp);
		this->Network	= string(Network);
		this->Unity		= string(Unity);
		this->Total		= string(Total);
		this->Avg		= string(Avg);
		this->UDate		= string(UDate);
		this->Flag		= string(Flag);
	}
};

//char ClassId[_CLASSID_SIZE_];
//char ClassName[_ID_SIZE_];
//char UName[_ID_SIZE_];
struct _Tb_Class
{
	string Seq;
	string ClassId;
	string ClassName;
	string UserID;
	string UDate;
	string Flag	;
	string Pass;
	string UName;
	string Tell;

	_Tb_Class(char* Seq		,char* ClassId		,char* ClassName
		,char* UserID	,char* UDate		,char* Flag	
		,char* pass	,char* UName	,char* Tell)
	{

		this->Seq		= string(Seq);
		this->ClassId	= string(ClassId);
		this->ClassName	= string(ClassName);
		this->UserID	= string(UserID);
		this->UDate		= string(UDate);
		this->Flag		= string(Flag);
		this->Pass		= string(Pass);
		this->UName		= string(UName);
		this->Tell		= string(Tell);
	}

	void SetData(char* Seq		,char* ClassId		,char* ClassName
				,char* UserID	,char* UDate		,char* Flag	
				,char* pass	,char* UName	,char* Tell)
	{
		
		this->Seq		= string(Seq);
		this->ClassId	= string(ClassId);
		this->ClassName	= string(ClassName);
		this->UserID	= string(UserID);
		this->UDate		= string(UDate);
		this->Flag		= string(Flag);
		this->Pass		= string(Pass);
		this->UName		= string(UName);
		this->Tell		= string(Tell);
	}


};
