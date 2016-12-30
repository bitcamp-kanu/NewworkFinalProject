#pragma once
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


struct _Header
{
	char cmd1;
	char cmd2;
	int  pakID; //Ack/Nak 확인 용으로 사용
		//--- 인증 관련 으로 무조건 필요.
	char id[_ID_SIZE_];	    //자릿 수는 추후 정해야 함.
	char SecretKey; //인증키.
};

//A 전체, S 학생 G 성적 U 유저
#pragma pack(push ,1)

//Login AL 서정민
struct _Login
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Login(){};
	char SecretKey; //인증키.

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

////US  유저정보요청
struct _DemandUserInfo
{
	_Header header;
	char id[_ID_SIZE_];
	char ClassId[_CLASSID_SIZE_];
	_DemandUserInfo() {};
	int cont;
	_DemandUserInfo(char cmd1, char cmd2, int pakID, char* id, char SecretKey, char* ClassId)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		strcpy(this->id, id);
		header.SecretKey = SecretKey; 
		strcpy(this->ClassId, ClassId);
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
			sprintf(buff, "%c%c key[%d] , id [%s], SecretKey [%c], ClassId [%s] 순서[%d]", header.cmd1, header.cmd2, header.pakID, id, header.SecretKey, ClassId, cont);
			return string(buff);
		}
};



struct _SearchStudent
{

};

//학생 등록. SC 초롱씨.
struct _CreateStudent
{

};

//학생 삭제. SD  - 영준
struct _DeleteStudent
{
	
};

//학생 수정. SU   - 영준
struct _UpdateStudent
{

};

struct _UpdateGrade
{

};

//과목별 평균. AA -- 승욱 형님.
struct _AverageAll
{

};

#pragma pack(pop)