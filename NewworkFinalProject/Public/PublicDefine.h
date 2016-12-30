﻿#pragma once
#pragma warning(disable: 4996)
#pragma warning(disable: 4081)
#include <iostream>
#include <string>
using namespace std;
//공통으로사용할 define 

//수신 buffer 사이즈 
#define _RECV_BUFFER_SIZE 2048
#define _ID_SIZE_ 20
#define _PASS_SIZE_ 20
#define _CLASSID_SIZE_ 20
//사용할 패킷을 정의 한다.

//pakID
//100 로그인
//	110 로그인 실패.
//	111 로성공
//200 인증관련
// 201 인증 성공
// 200 인증 실패 - 보인키가 없음.
// 210 인증 실패 - 보안키 유효 시간이 초과 되었음. 
//prefix All:전체 Student::학생 Grade:성적  Etc:기타   U 유저
// C 생성 R (읽기,조회) 
//A 전체, S 학생 G 성적
#pragma pack(push,1)


struct _Header
{
	char cmd1;
	char cmd2;
	int  pakID; //111 성공 110 실패  //인증실패 211
		//--- 인증 관련 으로 무조건 필요.
	char id[_ID_SIZE_];	    //자릿 수는 추후 정해야 함.
	char SecretKey; //인증키.
};

//Login AL 서정민
struct _Login
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Login(){};

	int cont;
	_Login(char cmd1, char cmd2, int  pakID, char* id, char* pass)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		strcpy(this->id, id);
		strcpy(this->pass, pass);
		cont = 0;
	}

	//내자신을 초기화 한다.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff 의 내용을 구조체에 채운다.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff,"%c%c key[%d] , id [%s], pass [%s] 순서[%d]",header.cmd1,header.cmd2,header.pakID,id,pass,cont);
		return string(buff);
	}
};

//보안키 인증 - 보안키를 확인 한다. EC
struct _SecretKeyChedk
{
	_Header header;
	char	chBSucess; //'T'  성공

	_SecretKeyChedk()
	{

	}
	_SecretKeyChedk(char cmd1, char cmd2, int  pakID, char* id, char chBSucess)
	{
		chBSucess = chBSucess;
	}
	//내자신을 초기화 한다.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff 의 내용을 구조체에 채운다.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}

	string ToString()
	{
		char buff[1024];
		sprintf(buff, "%c%c pakID[%d] , id [%s], chBSucess [%c] ", header.cmd1, header.cmd2, header.pakID, header.id, chBSucess);
		return string(buff);
	}
};

//US  유저정보요청
struct _DemandUserInfo
{
	_Header header;
	char id[_ID_SIZE_];
	char ClassId[_CLASSID_SIZE_];
	char ClassName[_ID_SIZE_];
	char UName[_ID_SIZE_];
	_DemandUserInfo() {};
	int cont;
	_DemandUserInfo(char cmd1, char cmd2, int pakID, char* id, char SecretKey, char* ClassId, char* ClassName, char* UName)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		header.SecretKey = SecretKey;
		strcpy(ClassId, ClassId);
		strcpy(ClassName, ClassName);
		strcpy(UName, UName);
	}
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}

	//buff 의 내용을 구조체에 채운다.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
};

//학생 조회. SS 
struct _SearchStudent
{
	_Header header;

};

//학생 등록. SC 초롱씨.
struct _CreateStudent
{
	_Header header;
};

//학생 삭제. SD  - 영준
struct _DeleteStudent
{
	_Header header;
};

//학생 수정. SU   - 영준
struct _UpdateStudent
{
	_Header header;
};


//학생정보 가져오기. AA -- 승욱 형님. GU 성적 수정.
struct _WorkData
{
	_Header header;
	char ClassId[_ID_SIZE_];
	int ClassNum;

	char SName[_ID_SIZE_];
	char SSex;
	char STel[_ID_SIZE_];
	int C;
	int CPP;
	int CSharp;
	int Network;
	int Unity;
	int Total;
	DOUBLE Ave;
	int UDate;

	_WorkData(){};
	int cont;

	_WorkData(char cmd1,char cmd2,int  pakID,char* id,char* skey,
		char* mClassId, int mClassNum, char* mSName, char mSSex, char* mSTel,
		int mC, int mCPP,	int mCSharp, int mNetwork, int mUnity,
		int mTotal, DOUBLE mAve, int mUDate)
	{
		header.cmd1		= cmd1;
		header.cmd2		= cmd2;
		header.pakID	= pakID;
		strcpy(header.id,id);
		header.SecretKey,skey;
		//---------------------
		strcpy(ClassId,mClassId);
		ClassNum=mClassNum;
		strcpy(SName,mSName);
		SSex=mSSex;
		strcpy(STel,mSTel);
		
		C=mC;
		CPP=mCPP;
		CSharp=mCSharp;
		Network=mNetwork;
		Unity=mUnity;
		Total=mTotal;
		Ave=mAve;
		UDate=mUDate;

		cont = 0;
	}

	//내자신을 초기화 한다.
	void InitData()
	{
		memset(this,0x00,sizeof(this));
	}
	//buff 의 내용을 구조체에 채운다.
	void SetCopyBuff(char* data)
	{
		memcpy(this,data,sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff,"%c%c pakID[%d] , id[%s], key[%d], 순서[%d] \n \
					ClassId[%s] ClassNum[%d] SName[%s] SSex[%c] STel[%s] \n \
					C[%d] CPP[%d] CSharp[%d] Network[%d] Unity[%d] \n \
					Total[%d] Ave[%.2l] UDate[%s] \n ",
					header.cmd1,header.cmd2,header.pakID,header.id,header.SecretKey, cont, \
					ClassId, ClassNum, SName, SSex, STel, \
					C, CPP, CSharp, Network, Unity, Total, Ave, UDate);

		return string(buff);
	}
};
#pragma pack(pop)