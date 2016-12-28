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
	char chCmd[CMD_SIZE]; //CMD ����
	short nCmdSize;  // CMD ��ü ũ��.
	short nCmdIndex; // CMD ����

	_Header()
	{
		memset(this,0x00,sizeof(_Header));
	}
	_Header(const _Header& item)
	{
		memcpy(chCmd,item.chCmd,CMD_SIZE);
		nCmdSize = item.nCmdSize;  // CMD ��ü ũ��.
		nCmdIndex = item.nCmdIndex; // CMD ����
	}

	bool SetData(char* buffer)
	{
		memcpy(this,buffer,sizeof(_Header));
		return true;
	}
};


//���ڿ� ���۽� ���.
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
"HE" ���� ��û
"SX" ȭ��ǥ�� ���ڿ�.
"ID" Insert
"DD" Delete �޼��� ��û
"SD" Search �޼��� ��û
"PD" Pring �޼��� ��û
"ED" Exit �޼��� ��û
"IO" Insert
"DO" Delete
"SO" Search
"PO" Pring
"EO" Exit

Server -> Client
'SM' �޴����. (ShowMenu)
'SS' �޴����. (�޴� ���� �޼���.)
'EE' ����.



'D' �޴� ���� ���.
*/
