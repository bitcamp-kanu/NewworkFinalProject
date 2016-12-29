#pragma once
#include <iostream>
#include <string>
using namespace std;
//�������λ���� define 

//���� buffer ������ 
#define _RECV_BUFFER_SIZE 2048
#define _ID_SIZE_ 20
#define _PASS_SIZE_ 20
//����� ��Ŷ�� ���� �Ѵ�.

struct _Header
{	
	char cmd1;
	char cmd2;
	int  pakID; //Ack/Nak Ȯ�� ������ ���
		//--- ���� ���� ���� ������ �ʿ�.
	char id[_ID_SIZE_];	    //�ڸ� ���� ���� ���ؾ� ��.
	char SecretKey; //����Ű.
};

struct _Login
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Login(){};
	char SecretKey; //����Ű.
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