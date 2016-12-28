#pragma once
#include <string>
#include <iostream>
#define NAME_LEN		20
#define TEL_LEN			20
#define MAX_PERSON_NUM	100

#define _BUFF_SIZE_ 4096
#define PACKSET_BUFF_SIZE 1024
#define CMD_SIZE  2

using namespace std;


struct _Header
{
	char chCmd[CMD_SIZE]; //CMD 종류
	short nCmdSize;  // CMD 전체 크기.
	short nCmdIndex; // CMD 순서

	_Header()
	{
		memset(this,0x00,sizeof(_Header));
	}
	_Header(const _Header& item)
	{
		memcpy(chCmd,item.chCmd,CMD_SIZE);
		nCmdSize = item.nCmdSize;  // CMD 전체 크기.
		nCmdIndex = item.nCmdIndex; // CMD 순서
	}

	bool SetData(char* buffer)
	{
		memcpy(this,buffer,sizeof(_Header));
		return true;
	}
};


//문자열 전송시 사용.
struct Packet
{
	_Header header;
	short	nlen;
	char	key;
	char	buff[PACKSET_BUFF_SIZE];

	Packet()
	{
		Init();
	}

	void Init()
	{
		memset(this,0x00,sizeof(Packet));
	}
	void SetCmd(char* cmd )
	{
		header.chCmd[0] = cmd[0];
		header.chCmd[1] = cmd[1];
	}

	void SetStr(const char* str)
	{
		strcpy(buff,str);
		nlen = strlen(str);
	}

	void InitStr()
	{
		memset(buff,0x00,sizeof(buff));
	}
	bool SetDataCopy(Packet* buffer)
	{
		memcpy(this,buffer,sizeof(Packet));
		return true;
	}
	void Print()
	{
		for(int i = 0 ; i <nlen ; i++ )
		{
			cout << buff[i];
		}
	}
	string GetStr()
	{
		char tmpBuff[1024] = {0};
		sprintf(tmpBuff,"Cmd[%c%c] ,Len[%d] STR[%s]",header.chCmd[0],header.chCmd[1],nlen,buff);
		return string(tmpBuff);
	}
};




/*
Client -> Server
"HE" 도움말 요청
"SX" 화면표시 문자열.
"ID" Insert
"DD" Delete 메세지 요청
"SD" Search 메세지 요청
"PD" Pring 메세지 요청
"ED" Exit 메세지 요청
"IO" Insert
"DO" Delete
"SO" Search
"PO" Pring
"EO" Exit

Server -> Client
'SM' 메뉴목록. (ShowMenu)
'SS' 메뉴목록. (메뉴 선택 메세지.)
'EE' 에러.



'D' 메뉴 선택 목록.
*/
