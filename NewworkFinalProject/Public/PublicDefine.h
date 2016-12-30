#pragma once
#include <iostream>
#include <string>
using namespace std;
//�������λ���� define 

//���� buffer ������ 
#define _RECV_BUFFER_SIZE 2048
#define _ID_SIZE_ 20
#define _PASS_SIZE_ 20

//[LYJ ����]
#define _CLASSID_SIZE_ 20
#define _NAME_SIZE_ 20
#define _DATE_SIZE_ 16
//[LYJ ��]
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
	_Login() {};
	char SecretKey; //����Ű.
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

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff, "%c%c key[%c] , id [%d] ����[%d]", header.cmd1, header.cmd2, header.pakID, id, cont);
		return string(buff);
	}
};

//Gate AL �̿���
struct _Gate
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Gate() {};
	char SecretKey; //����Ű.
	int cont;
	_Gate(char cmd1, char cmd2, int  pakID, char* id, char* pass)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		strcpy(this->id, id);
		strcpy(this->pass, pass);
		cont = 0;
	}

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff, "%c%c key[%c] , id [%d] ����[%d]", header.cmd1, header.cmd2, header.pakID, id, cont);
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

//�л� ����. SD  - ���� // ���� �ʿ���� �÷� ������.
struct _DeleteStudent
{
	_Header header;
	int ClassNum;
	char ClassId[_CLASSID_SIZE_];
	int Seq;
	char SName[_NAME_SIZE_];
	int C_Score;
	int Cpp_Score;
	int Cshart_Score;
	int Network_Score;
	int Unity_Score;
	int Total;
	float Avg;
	char UDate[_DATE_SIZE_];
	char Flag;
	_DeleteStudent() {};
	int cont;
	_DeleteStudent(char cmd1, char cmd2, int  pakID, char* id,
		int ClassNum, char* ClassId, int Seq, char* SName, int C_Score, int Cpp_Score,
		int Cshart_Score, int Network_Score, int Unity_Score, int Total, float Avg,
		char* UDate, char Flag)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		this->ClassNum = ClassNum;
		strcpy(this->ClassId, ClassId);
		this->Seq = Seq;
		strcpy(this->SName, SName);
		this->C_Score = C_Score;
		this->Cpp_Score = Cpp_Score;
		this->Cshart_Score = Cshart_Score;
		this->Network_Score = Network_Score;
		this->Unity_Score = Unity_Score;
		this->Total = Total;
		this->Avg = Avg;
		strcpy(this->UDate, UDate);
		this->Flag = Flag;
		cont = 0;
	}

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff, "%c%c key[%c] , id [%d] ����[%d]", header.cmd1, header.cmd2, header.pakID,
			ClassNum, ClassId, Seq, SName, C_Score, Cpp_Score, Cshart_Score, Network_Score,
			Unity_Score, Total, Avg, UDate, Flag);
		return string(buff);
	}
};

//�л� ����. SU   - ���� // ���� �ʿ���� �÷� ������.
struct _UpdateStudent
{
	_Header header;
	int ClassNum;
	char ClassId[_CLASSID_SIZE_];
	int Seq;
	char SName[_NAME_SIZE_];
	int C_Score;
	int Cpp_Score;
	int Cshart_Score;
	int Network_Score;
	int Unity_Score;
	int Total;
	float Avg;
	char UDate[_DATE_SIZE_];
	char Flag;
	_UpdateStudent() {};
	int cont;
	_UpdateStudent(char cmd1, char cmd2, int  pakID, char* id,
		int ClassNum, char* ClassId, int Seq, char* SName, int C_Score, int Cpp_Score,
		int Cshart_Score, int Network_Score, int Unity_Score, int Total, float Avg,
		char* UDate, char Flag)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		this->ClassNum = ClassNum;
		strcpy(this->ClassId, ClassId);
		this->Seq = Seq;
		strcpy(this->SName, SName);
		this->C_Score = C_Score;
		this->Cpp_Score = Cpp_Score;
		this->Cshart_Score = Cshart_Score;
		this->Network_Score = Network_Score;
		this->Unity_Score = Unity_Score;
		this->Total = Total;
		this->Avg = Avg;
		strcpy(this->UDate, UDate);
		this->Flag = Flag;
		cont = 0;
	}

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff, "%c%c key[%c] , id [%d] ����[%d]", header.cmd1, header.cmd2, header.pakID,
			ClassNum, ClassId, Seq, SName, C_Score, Cpp_Score, Cshart_Score, Network_Score,
			Unity_Score, Total, Avg, UDate, Flag);
		return string(buff);
	}
};

//���� ����. GU  - ���� // ���� �ʿ���� �÷� ������.
struct _UpdateGrade
{
	_Header header;
	int ClassNum;
	char ClassId[_CLASSID_SIZE_];
	int Seq;
	char SName[_NAME_SIZE_];
	int C_Score;
	int Cpp_Score;
	int Cshart_Score;
	int Network_Score;
	int Unity_Score;
	int Total;
	float Avg;
	char UDate[_DATE_SIZE_];
	char Flag;
	_UpdateGrade() {};
	int cont;
	_UpdateGrade(char cmd1, char cmd2, int  pakID, char* id,
		int ClassNum, char* ClassId, int Seq, char* SName, int C_Score, int Cpp_Score,
		int Cshart_Score, int Network_Score, int Unity_Score, int Total, float Avg,
		char* UDate, char Flag)
	{
		header.cmd1 = cmd1;
		header.cmd2 = cmd2;
		header.pakID = pakID;
		strcpy(header.id, id);
		this->ClassNum = ClassNum;
		strcpy(this->ClassId, ClassId);
		this->Seq = Seq;
		strcpy(this->SName, SName);
		this->C_Score = C_Score;
		this->Cpp_Score = Cpp_Score;
		this->Cshart_Score = Cshart_Score;
		this->Network_Score = Network_Score;
		this->Unity_Score = Unity_Score;
		this->Total = Total;
		this->Avg = Avg;
		strcpy(this->UDate, UDate);
		this->Flag = Flag;
		cont = 0;
	}

	//���ڽ��� �ʱ�ȭ �Ѵ�.
	void InitData()
	{
		memset(this, 0x00, sizeof(this));
	}
	//buff �� ������ ����ü�� ä���.
	void SetCopyBuff(char* data)
	{
		memcpy(this, data, sizeof(this));
	}
	string ToString()
	{
		char buff[1024];
		sprintf(buff, "%c%c key[%c] , id [%d] ����[%d]", header.cmd1, header.cmd2, header.pakID,
			ClassNum, ClassId, Seq, SName, C_Score, Cpp_Score, Cshart_Score, Network_Score,
			Unity_Score, Total, Avg, UDate, Flag);
		return string(buff);
	}
};

//���� ���. AA -- �¿� ����.
struct _AverageAll
{

};