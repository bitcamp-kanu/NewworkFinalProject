#pragma once
#include <string>
#include <stdio.h>
using namespace std;
//파일 입출력을 담당 하낟.
#define  _BUFFSIZE_ 1024
class WIFile
{
private:
	FILE* m_pfile;
	char m_buff[_BUFFSIZE_];
public:
	WIFile(void);
	virtual ~WIFile(void);
	
	bool Open(string fileName,string mode);
	int  Read(void *buffer ,int size,int cnt);
	int  Write(const void* buffer , int size,int count);
	bool ReadLine(string& str);
	bool WriteLine(string& str);
	bool IsEOF();
};

