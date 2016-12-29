#pragma once
#include <iostream>
#include <string>
using namespace std;
//공통으로사용할 define 

//수신 buffer 사이즈 
#define _RECV_BUFFER_SIZE 2048
#define _ID_SIZE_ 20
#define _PASS_SIZE_ 20
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

//A 전체, S 학생 G 성적

//Login AL 서정민
struct _Login
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Login(){};
	char SecretKey; //인증키.
	int cont;
	_Login(char cmd1,char cmd2,int  pakID,char* id,char* pass)
	{
		header.cmd1		= cmd1;
		header.cmd2		= cmd2;
		header.pakID	= pakID;
		strcpy(header.id,id);
		strcpy(this->id,id);
		strcpy(this->pass,pass);
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
		sprintf(buff,"%c%c key[%c] , id [%d] 순서[%d]",header.cmd1,header.cmd2,header.pakID,id,cont);
		return string(buff);
	}
};

//학생검색 SR -- 서정민
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

//성적 수정. GU  - 영준
struct _UpdateGrade
{

};

//과목별 평균. AA -- 승욱 형님.
struct _AverageAll
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_AverageAll(){};
	char SecretKey; //인증키.
	int cont;
	_AverageAll(char cmd1,char cmd2,int  pakID,char* id,char* pass)
	{
		header.cmd1		= cmd1;
		header.cmd2		= cmd2;
		header.pakID	= pakID;
		strcpy(header.id,id);
		strcpy(this->id,id);
		strcpy(this->pass,pass);
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
		sprintf(buff,"%c%c key[%c] , id [%d] 순서[%d]",header.cmd1,header.cmd2,header.pakID,id,cont);
		return string(buff);
	}
};