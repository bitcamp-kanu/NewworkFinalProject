#pragma once
#include <iostream>
#include <string>
using namespace std;
//공통으로사용할 define 

//수신 buffer 사이즈 
#define _RECV_BUFFER_SIZE 2048
#define _ID_SIZE_ 20
#define _PASS_SIZE_ 20

//[LYJ 시작]
#define _CLASSID_SIZE_ 20
#define _NAME_SIZE_ 20
#define _DATE_SIZE_ 16
//[LYJ 끝]
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
	_Login() {};
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
		sprintf(buff, "%c%c key[%c] , id [%d] 순서[%d]", header.cmd1, header.cmd2, header.pakID, id, cont);
		return string(buff);
	}
};

//Gate AL 이영준
struct _Gate
{
	_Header header;
	char id[_ID_SIZE_];
	char pass[_PASS_SIZE_];
	_Gate() {};
	char SecretKey; //인증키.
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
		sprintf(buff, "%c%c key[%c] , id [%d] 순서[%d]", header.cmd1, header.cmd2, header.pakID, id, cont);
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

//학생 삭제. SD  - 영준 // 추후 필요없는 컬럼 빼야함.
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
		sprintf(buff, "%c%c key[%c] , id [%d] 순서[%d]", header.cmd1, header.cmd2, header.pakID,
			ClassNum, ClassId, Seq, SName, C_Score, Cpp_Score, Cshart_Score, Network_Score,
			Unity_Score, Total, Avg, UDate, Flag);
		return string(buff);
	}
};

//학생 수정. SU   - 영준 // 추후 필요없는 컬럼 빼야함.
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
		sprintf(buff, "%c%c key[%c] , id [%d] 순서[%d]", header.cmd1, header.cmd2, header.pakID,
			ClassNum, ClassId, Seq, SName, C_Score, Cpp_Score, Cshart_Score, Network_Score,
			Unity_Score, Total, Avg, UDate, Flag);
		return string(buff);
	}
};

//성적 수정. GU  - 영준 // 추후 필요없는 컬럼 빼야함.
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
		sprintf(buff, "%c%c key[%c] , id [%d] 순서[%d]", header.cmd1, header.cmd2, header.pakID,
			ClassNum, ClassId, Seq, SName, C_Score, Cpp_Score, Cshart_Score, Network_Score,
			Unity_Score, Total, Avg, UDate, Flag);
		return string(buff);
	}
};

//과목별 평균. AA -- 승욱 형님.
struct _AverageAll
{

};