#include "WIFile.h"
#include <iostream>
#include <string>

using namespace std;

WIFile::WIFile(void)
	:m_pfile (NULL)
{

}

WIFile::~WIFile(void)
{
	if(m_pfile != NULL)
	{
		fclose(m_pfile);
		m_pfile = NULL;
	}
}

bool WIFile::Open(string fileName,string mode)
{
	if(m_pfile != NULL)
	{
		return false; //이미 열려 있는 파일 입니다.,
	}
	m_pfile = fopen(fileName.c_str(),mode.c_str());

	if(m_pfile == NULL)
	{
		return false; //파일열기 실패.
	}
	return true;
}
int WIFile::Read(void* buffer ,int size,int count)
{
	int readCnt = 0;
	if(m_pfile != NULL)
	{
		readCnt = fread(buffer,size,count,m_pfile);
	}
	return readCnt ;
}
int WIFile::Write(const void* buffer , int size,int count)
{
	int wCnt = 0;
	if(m_pfile != NULL)
	{
		wCnt = fwrite(buffer,size,count,m_pfile);
	}
	return wCnt;
}
bool WIFile::ReadLine(string& pStr)
{
	fscanf(m_pfile,"%s",m_buff);
	pStr = string(m_buff);
	return true;
	return false;
}
bool WIFile::WriteLine(string& pStr)
{
	fprintf(m_pfile,"%s\n",pStr.c_str());
	return true;
}
bool WIFile::IsEOF()
{
	return (feof(m_pfile) != 0);
}