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

struct _Login
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Login(){};
	char SecretKey; //인증키.
	_Login(char cmd1,char cmd2,int  pakID,char* id,char* pass)
	{
		header.cmd1		= cmd1;
		header.cmd2		= cmd2;
		header.pakID	= pakID;
		strcpy(header.id,id);
		strcpy(this->id,id);
		strcpy(this->pass,pass);
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff,"%c%c key[%c] , id [%d]",header.cmd1,header.cmd2,header.pakID,id);
		return string(buff);
	}
};