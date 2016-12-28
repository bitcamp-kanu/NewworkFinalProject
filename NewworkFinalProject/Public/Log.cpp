#include "Log.h"
#include "WIFile.h"
CLog* CLog::m_plog = NULL;
CLog::CLog()
{
	m_strFileName = "Log.txt";
};

CLog::~CLog()
{
	if(CLog::m_plog != NULL)
	{
		delete CLog::m_plog ;
		CLog::m_plog = NULL;
	}
}

void CLog::WriteLog(string& str,char* _fileName_, int lile)
{
	char buff[1024] = {0};
	sprintf(buff,"[%-20s][%d] %s",(strrchr(_fileName_,'\\')),lile,str.c_str());
	WIFile m_pKnFile;
	m_pKnFile.Open(m_strFileName,"a+");
	m_pKnFile.WriteLine(string(buff));
}