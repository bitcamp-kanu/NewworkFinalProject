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

//A ��ü, S �л� G ����

//Login AL ������
struct _Login
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Login(){};
	char SecretKey; //����Ű.
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

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this,0x00,sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this,data,sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff,"%c%c key[%c] , id [%d] ����[%d]",header.cmd1,header.cmd2,header.pakID,id,cont);
		return string(buff);
	}
};

//�л��˻� SR -- ������
struct _SearchStudent 
{

};

//�л� ���. SC �ʷվ�.
struct _CreateStudent
{

};

//�л� ����. SD  - ����
struct _DeleteStudent
{

};

//�л� ����. SU   - ����
struct _UpdateStudent
{

};

//���� ����. GU  - ����
struct _UpdateGrade
{

};

//���� ���. AA -- �¿� ����.
struct _AverageAll
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_AverageAll(){};
	char SecretKey; //����Ű.
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

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this,0x00,sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this,data,sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff,"%c%c key[%c] , id [%d] ����[%d]",header.cmd1,header.cmd2,header.pakID,id,cont);
		return string(buff);
	}
};