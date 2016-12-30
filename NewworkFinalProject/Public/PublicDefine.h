#pragma once
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
//사용할 패킷을 정의 한다.

//pakID
//100 로그인
//	110 로그인 실패.
//	111 로성공
//200 인증관련
// 201 인증 성공
// 200 인증 실패 - 보인키가 없음.
// 210 인증 실패 - 보안키 유효 시간이 초과 되었음. 


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
//prefix All:전체 Student::학생 Grade:성적  Etc:기타 
// 
//

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

//보안키 인증 - 보안키를 확인 한다. EC
struct _SecretKeyChedk
{
	_Header header;
	char	chBSucess; //'T'  성공

	_SecretKeyChedk(char cmd1, char cmd2, int  pakID, char* id, char chBSucess)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		
		chBSucess = chBSucess;
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

	string ToString()
	{
		char buff[1024];
		sprintf(buff,"%c%c pakID[%d] , id [%s], chBSucess [%c] ",header.cmd1,header.cmd2,header.pakID,header.id,chBSucess);
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