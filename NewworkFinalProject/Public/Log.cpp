#include "Log.h"
#include "WIFile.h"
#include <afxwin.h>
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
void CLog::SetFilePath(string filePath)
{

}
void CLog::WriteLog(string& str,char* _fileName_, int lile)
{
	char buff[1024] = {0};
	sprintf(buff,_T("[%-20s][%d] %s"),(strrchr(_fileName_,'\\')),lile,str.c_str());
#ifdef _DEBUF_OUT_
	::OutputDebugString(buff);
#endif

#undef _FILE_WRITE_
#ifdef _FILE_WRITE_
	WIFile m_pKnFile;
	m_pKnFile.Open(m_strFileName,"a+");
	m_pKnFile.WriteLine(string(buff));
#endif
}

