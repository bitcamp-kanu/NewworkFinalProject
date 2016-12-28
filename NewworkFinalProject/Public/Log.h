#pragma once
#include <iostream>
#include <string>
using namespace std;

class CLog
{
private:
	static CLog* m_plog;
	string m_strFileName;	
	CLog();
public:	
	~CLog();
	static CLog* Instance()
	{
		if(CLog::m_plog == NULL)
		{
			CLog::m_plog  = new CLog();
		}
		return CLog::m_plog;
	}
	void WriteLog(string& str,char* _fileName_, int lile);

};



